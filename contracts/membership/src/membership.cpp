#include <membership/membership.hpp>

using namespace eosio;

void membership::transfer(  name     from,
                            name     to,
                            asset    quantity,
                            string   memo)
{
    // lexer
    vector<string> info;
    split(memo, '$', info);
    eosio_assert(info.size() == 3, "wrong format! memo requires 3 tokens: action$name$id");
    string opcode = info[0].c_str();
    string kid_name = info[1].c_str();
    string kid_id = info[2].c_str();
    // check actions
    eosio_assert(opcode == "enroll" || opcode == "renew", "wrong opcode! currently supporting opcodes: enroll, renew");
    if(opcode == "enroll"){
        // check uniqueness of eos account
        auto new_kid = _members.find( from.value );
        eosio_assert(new_kid == _members.end(), "Member with this account alreadty exists");
        
        // check uniqueness of student id
        auto id_index = _members.get_index<"studentid"_n>();
        auto new_kid_id = id_index.find(sha256(const_cast<char*>(kid_id.c_str()), kid_id.size() * sizeof(char)));
        eosio_assert(new_kid_id == id_index.end(), "Member with this id alreadty exists");
        // check format of student id
        eosio_assert(isNum(kid_id), "id is supposed to be a number");
        eosio_assert(kid_id.size() == 10 || kid_id.size() == 8, "wrong digit number");
        if(kid_id.size() == 10){
            eosio_assert(kid_id[0] == '3' && kid_id[3] == '0' && kid_id[5] == '0', "wrong format for ZJU bachelor id");
        }
        else if(kid_id.size() == 8){
            eosio_assert(kid_id[0] == '2' || kid_id[0] == '1', "wrong format for ZJU ms/phd id");
        }
        // check uniqueness of student name
        auto name_index = _members.get_index<"studentname"_n>();
        auto new_kid_name = name_index.find(sha256(const_cast<char*>(kid_name.c_str()), kid_name.size() * sizeof(char)));
        eosio_assert(new_kid_name == name_index.end(), "Member with this name alreadty exists");
        // check register fee
        eosio_assert(quantity.is_valid(), "Invalid token transfer...");
        eosio_assert(quantity.amount == 10000 * 1e4 , "Wrong register fee! It is supposed to be 10000.0000 AAA");
        eosio_assert(quantity.symbol == symbol("AAA", 4), "Wrong token symbol!");

        _members.emplace( _self, [&]( auto& m ) {
            m.eosaccount        = from;
            m.studentid         = kid_id;
            m.studentname       = kid_name;            
            m.registration_date = now();
            m.expiration_date   = now() + 3600 * 24 * 183;
        });
    }
    else if(opcode == "renew"){
        // check existence of eos account
        auto kid = _members.find( from.value);
        eosio_assert(kid != _members.end(), "Record doesn't exist");
        // check renewal
        eosio_assert(quantity.is_valid(), "Invalid token transfer...");
        eosio_assert(quantity.amount > 0, "Renewal must be positive" );
        eosio_assert(quantity.amount % (int64_t)(10000 * 1e4) == 0 , "Wrong renewal! It is supposed to be multiple of 10000.0000 AAAwith 4      decimal digits");
        eosio_assert(quantity.symbol == symbol("AAA", 4), "Wrong token symbol!");               
           
        uint64_t durations = quantity.amount / (10000 * 1e4);
        _members.modify( kid, same_payer, [&]( auto& m ) {
            m.expiration_date += 3600 * 24 * 183 * durations;
        });
    }
}

void membership::droptable(){
    require_auth(_self);
    for(auto itr = _members.begin(); itr != _members.end();) {
        itr = _members.erase(itr);
    }
}

void membership::split(const string& s, char c, vector<string>& v) {
   string::size_type i = 0;
   string::size_type j = s.find(c);
 
   while (j != string::npos) {
      v.push_back(s.substr(i, j-i));
      i = ++j;
      j = s.find(c, j);
 
      if (j == string::npos)
         v.push_back(s.substr(i, s.length()));
   }
}

bool membership::isNum(string str)  
{  
    for(int i = 0; i < str.size(); i++){
        if(str[i] < '0' || str[i] > '9'){
            return false;
        }
    }
    return true;
}

extern "C" {
    void apply(uint64_t receiver, uint64_t code, uint64_t action) {
        if(code == receiver && action != name("transfer").value) {
            switch(action){
                case name("droptable").value: execute_action(name(receiver), name(code), &membership::droptable );
            }
        }
        else if(code == name("zjubcatest11").value && action == name("transfer").value) {
            execute_action(name(receiver), name("zjubcatest12"), &membership::transfer );
        }
    }
};

// EOSIO_ABI_CUSTOM(membership, (enroll)(quit)(renew))
