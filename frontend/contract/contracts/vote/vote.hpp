#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>
#include <string>
using namespace std, eosio;

class[[eosio::contract("zjubca.vote")]] vote : public eosio::contract {
 public:
  using contract::contract;

  [[eosio::action]] void setVote(name voter, uint8_t attitude,
                                 uint64_t issueNum, asset deposit);

  [[eosio::action]] void withdraw(uint64_t issueNum);

 private:
  struct [[eosio::table]] issue {
    uint64_t number;
    name voter;
    uint8_t attitude;
    uint64_t value;
    uint64_t primary_key() const { return number; }
    uint64_t get_voter() const { return voter.value; }
  }

  typedef multi_index<
      "issues"_n, issue,
      indexed_by<"voter"_n, const_mem_fun<issue, uint64_t, &issue::get_voter>>>
      issue_index;
}