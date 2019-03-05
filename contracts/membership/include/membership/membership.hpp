#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
// #include <eosiolib/crypto.h>

#include <string>
#include <vector>

using namespace eosio;
using namespace std;

class [[eosio::contract("membership")]] membership : public contract {
   public:
      using contract::contract;

      membership( name receiver, name code, datastream<const char*> ds ):contract(receiver, code, ds),  _members(receiver, code.value){}

      // [[eosio::action]]
      // void enroll(string   studentname,
      //             uint64_t student_id,
      //             name     eosaccount,
      //             asset    register_fee);

      // [[eosio::action]]
      // void renew( name     eosaccount,
      //             asset    renewal);

      [[eosio::action]]
      void transfer( name     from,
                     name     to,
                     asset    quantity,
                     string   memo);

      [[eosio::action]]
      void test(  name     from,
                  string   kid_id,
                  string   kid_name);

      [[eosio::action]]
      void quit(name user);

   private:
      void split(const string& s, char c, vector<string>& v);
      bool isNum(string str);

      struct [[eosio::table]] member {
         name     eosaccount;
         string   studentid;
         string   studentname;
         uint64_t registration_date;
         uint64_t expiration_date;

         uint64_t primary_key() const { return eosaccount.value; }
         eosio::checksum256 by_studentid() const { return sha256(const_cast<char*>(studentid.c_str()), studentid.size() * sizeof(char));}
         eosio::checksum256 by_studentname() const { return sha256(const_cast<char*>(studentname.c_str()), studentname.size() * sizeof(char));}
      };

      typedef eosio::multi_index< "member"_n, member, 
      indexed_by<"studentid"_n, const_mem_fun<member, eosio::checksum256, &member::by_studentid>>,
      indexed_by<"studentname"_n, const_mem_fun<member, eosio::checksum256, &member::by_studentname>>> members;

      members _members;
};