#include <eosiolib/eosio.hpp>
#include <string>

using namespace eosio;
using std::string;

class [[eosio::contract("membership")]] membership : public contract {
   public:
      using contract::contract;

      membership( name receiver, name code, datastream<const char*> ds ):contract(receiver, code, ds),  _members(receiver, code.value){}

      [[eosio::action]]
      void enroll(string   student_name,
                  uint64_t student_id,
                  name     eosaccount);

   private:
      struct [[eosio::table]] member {
         string   student_name;
         uint64_t student_id;
         name     eosaccount;

         uint64_t primary_key() const { return student_id; }
         uint64_t by_eosaccount() const { return eosaccount.value; }
      };

      typedef eosio::multi_index< "members"_n, member, eosio::indexed_by<"eosaccount"_n, eosio::const_mem_fun<member, uint64_t, &member::by_eosaccount>>> members;

      members _members;
};