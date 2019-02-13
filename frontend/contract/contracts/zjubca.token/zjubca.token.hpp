/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>

#include <string>

using namespace eosio;

namespace eosiosystem {
    class system_contract;
}

namespace zjubca {

    using std::string;

    class [[eosio::contract("zjubca.token")]] token : public contract {
    public:
        using contract::contract;

        [[eosio::action]]
        void create(name issuer,
                    asset maximum_supply);

        [[eosio::action]]
        void issue(name to, asset quantity, string memo);

        [[eosio::action]]
        void transfer(name from,
                      name to,
                      asset quantity,
                      string memo);

        [[eosio::action]]
        void retire(asset quantity, string memo);

        [[eosio::action]]
        void open(name owner, const symbol &symbol, name ram_payer);

        [[eosio::action]]
        void close(name owner, const symbol &symbol);

        static asset get_supply( name token_contract_account, symbol_code sym_code )
        {
            stats statstable( token_contract_account, sym_code.raw() );
            const auto& st = statstable.get( sym_code.raw() );
            return st.supply;
        }

        static asset get_balance( name token_contract_account, name owner, symbol_code sym_code )
        {
            accounts accountstable( token_contract_account, owner.value );
            const auto& ac = accountstable.get( sym_code.raw() );
            return ac.balance;
        }

    private:
        // @abi table accounts i64
        struct [[eosio::table]] account {
            asset balance;

            uint64_t primary_key() const { return balance.symbol.code().raw(); }
        };

        // @abi table stats i64
        // currency status
        struct [[eosio::table]] stat {
            asset supply;
            asset max_supply;
            name issuer;

            uint64_t primary_key() const { return supply.symbol.code().raw(); }
        };

        typedef multi_index<"accounts"_n, account> accounts;
        typedef multi_index<"stats"_n, stat> stats;

        void sub_balance(name owner, asset value);

        void add_balance(name owner, asset value);

    public:
        struct transfer_args {
            name from;
            name to;
            asset quantity;
            string memo;
        };
    };

} /// namespace zjubca
