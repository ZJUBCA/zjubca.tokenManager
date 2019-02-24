#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
// #include <eosiolib/crypto.h>

#include <string>

using namespace eosio;
using std::string;

class [[eosio::contract("membership")]] membership : public contract {
   public:
      using contract::contract;

      membership( name receiver, name code, datastream<const char*> ds ):contract(receiver, code, ds),  _members(receiver, code.value){}

      [[eosio::action]]
      void enroll(string   studentname,
                  uint64_t student_id,
                  name     eosaccount,
                  asset    register_fee);

      [[eosio::action]]
      void quit(name user);

      // [[eosio::action]]
      // void renew( uint64_t student_id,
      //             name     eosaccount,
      //             asset    renew_fee){}

   private:
      struct [[eosio::table]] member {
         string   studentname;
         uint64_t student_id;
         name     eosaccount;
         uint64_t registration_date;
         uint64_t expiration_date;

         uint64_t primary_key() const { return student_id; }
         uint64_t by_eosaccount() const { return eosaccount.value; }
         // eosio::checksum256 by_studentname() const { return sha256(const_cast<char*>(studentname.c_str()), studentname.size() * sizeof(char));}
      };

      typedef eosio::multi_index< "members"_n, member, 
      indexed_by<"eosaccount"_n, const_mem_fun<member, uint64_t, &member::by_eosaccount>>> members;
      // indexed_by<"studentname"_n, const_mem_fun<member, eosio::checksum256, &member::by_studentname>>> members;

      members _members;
};