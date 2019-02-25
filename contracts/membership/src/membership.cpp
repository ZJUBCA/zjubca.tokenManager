#include <membership/membership.hpp>

using namespace eosio;

void membership::enroll(string   studentname,
                        uint64_t student_id,
                        name     eosaccount,
                        asset    register_fee)
{
    // check authority
    require_auth(eosaccount);
    // check uniqueness of student id
    auto new_kid = _members.find( student_id );
    eosio_assert(new_kid == _members.end(), "Member with this id alreadty exists");
    // check uniqueness of eos account
    auto account_index = _members.get_index<"eosaccount"_n>();
    auto new_kid_account = account_index.find(eosaccount.value);
    eosio_assert(new_kid_account == account_index.end(), "Member with this account alreadty exists");
    // check uniqueness of student name
    auto name_index = _members.get_index<"studentname"_n>();
    auto new_kid_name = name_index.find(sha256(const_cast<char*>(studentname.c_str()), studentname.size() * sizeof(char)));
    eosio_assert(new_kid_name == name_index.end(), "Member with this name alreadty exists");
    // check register fee
    eosio_assert(register_fee.is_valid(), "Invalid token transfer...");
    eosio_assert(register_fee.amount == 10000 * 1e4 , "Wrong register fee! It is supposed to be 10000.0000 AAA");
    eosio_assert(register_fee.symbol == symbol("AAA", 4), "Wrong token symbol!");

    action(
        permission_level{ eosaccount,"active"_n },
        "zjubcatest11"_n, "transfer"_n,
        std::make_tuple(eosaccount, "zjubcatest11"_n, register_fee, std::string("register"))
    ).send();
    
    _members.emplace( _self, [&]( auto& m ) {
        m.studentname      = studentname;
        m.student_id        = student_id;
        m.eosaccount        = eosaccount;
        m.registration_date = now();
        m.expiration_date   = now() + 3600 * 24 * 183;
    });
}

void membership::renew( name eosaccount, asset renewal)
{
    // check authority
    require_auth(eosaccount);
    // check existence of eos account
    auto account_index = _members.get_index<"eosaccount"_n>();
    auto kid = account_index.find(eosaccount.value);
    eosio_assert(kid != account_index.end(), "Record doesn't exist");
    // check renewal
    eosio_assert(renewal.is_valid(), "Invalid token transfer...");
    eosio_assert(renewal.amount > 0, "Renewal must be positive" );
    eosio_assert(renewal.amount % (int64_t)(10000 * 1e4) == 0 , "Wrong renewal! It is supposed to be multiple of 10000.0000 AAA with 4 decimal digits");
    eosio_assert(renewal.symbol == symbol("AAA", 4), "Wrong token symbol!");

    action(
        permission_level{ eosaccount,"active"_n },
        "zjubcatest11"_n, "transfer"_n,
        std::make_tuple(eosaccount, "zjubcatest11"_n, renewal, std::string("register"))
    ).send();

    uint64_t durations = renewal.amount / (10000 * 1e4);
    account_index.modify( kid, same_payer, [&]( auto& m ) {
        m.expiration_date += 3600 * 24 * 183 * durations;
    });    
}

void membership::quit(name user)
{
    // check authority
    require_auth(user);
    // check uniqueness of eos account
    auto account_index = _members.get_index<"eosaccount"_n>();
    auto kid = account_index.find(user.value);
    eosio_assert(kid != account_index.end(), "Record doesn't exist");
    
    account_index.erase(kid);
}

EOSIO_DISPATCH( membership, (enroll)(quit)(renew))