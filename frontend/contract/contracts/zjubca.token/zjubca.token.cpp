/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include "zjubca.token.hpp"

namespace zjubca {

    void token::create(name issuer,
                       asset maximum_supply) {
        require_auth(_self);
        
        auto sym = maximum_supply.symbol;
        eosio_assert(sym.is_valid(), "invalid symbol name");
        eosio_assert(maximum_supply.is_valid(), "invalid supply");
        eosio_assert(maximum_supply.amount > 0, "max-supply must be positive");

        stats statstable(_self, sym.code().raw());
        auto existing = statstable.find(sym.code().raw());
        eosio_assert(existing == statstable.end(), "token with symbol already exists");

        statstable.emplace(_self, [&](auto &s) {
            s.supply.symbol = maximum_supply.symbol;
            s.max_supply = maximum_supply;
            s.issuer = issuer;
        });
    }


    void token::issue(name to, asset quantity, string memo) {
        auto sym = quantity.symbol;
        eosio_assert(sym.is_valid(), "invalid symbol name");
        eosio_assert(memo.size() <= 256, "memo has more than 256 bytes");

        auto sym_name = sym.code().raw();
        stats statstable(_self, sym_name);
        auto existing = statstable.find(sym_name);
        eosio_assert(existing != statstable.end(), "token with symbol does not exist, create token before issue");
        const auto &st = *existing;

        require_auth(st.issuer);
        eosio_assert(quantity.is_valid(), "invalid quantity");
        eosio_assert(quantity.amount > 0, "must issue positive quantity");

        eosio_assert(quantity.symbol == st.supply.symbol, "symbol precision mismatch");
        eosio_assert(quantity.amount <= st.max_supply.amount - st.supply.amount, "quantity exceeds available supply");

        statstable.modify(st, same_payer, [&](auto &s) {
            s.supply += quantity;
        });

        add_balance(st.issuer, quantity);

        if (to != st.issuer) {
            SEND_INLINE_ACTION(*this, transfer, {st.issuer, "active"_n}, {st.issuer, to, quantity, memo});
            eosio::print("issue successfully");
        }
    }

    void token::transfer(name from,
                         name to,
                         asset quantity,
                         string memo) {
        eosio_assert(from != to, "cannot transfer to self");
        require_auth(from);
        eosio_assert(is_account(to), "to account does not exist");
        auto sym = quantity.symbol.code().raw();
        stats statstable(_self, sym);
        const auto &st = statstable.get(sym);

        require_recipient(from);
        require_recipient(to);

        eosio_assert(quantity.is_valid(), "invalid quantity");
        eosio_assert(quantity.amount > 0, "must transfer positive quantity");
        eosio_assert(quantity.symbol == st.supply.symbol, "symbol precision mismatch");
        eosio_assert(memo.size() <= 256, "memo has more than 256 bytes");


        sub_balance(from, quantity);
        add_balance(to, quantity);
    }

    void token::retire(asset quantity, string memo) {
        auto sym = quantity.symbol;
        eosio_assert(sym.is_valid(), "invalid symbol name");
        eosio_assert(memo.size() <= 256, "memo has more than 256 bytes");

        stats statstable(_self, sym.code().raw());
        auto existing = statstable.find(sym.code().raw());
        eosio_assert(existing != statstable.end(), "token with symbol does not exist");
        const auto &st = *existing;

        require_auth(st.issuer);
        eosio_assert(quantity.is_valid(), "invalid quantity");
        eosio_assert(quantity.amount > 0, "must retire positive quantity");

        eosio_assert(quantity.symbol == st.supply.symbol, "symbol precision mismatch");

        statstable.modify(st, same_payer, [&](auto &s) {
            s.supply -= quantity;
        });

        sub_balance(st.issuer, quantity);
    }

    void token::open(name owner, const symbol &symbol, name ram_payer) {
        require_auth(ram_payer);

        auto sym_code_raw = symbol.code().raw();

        stats statstable(_self, sym_code_raw);
        const auto &st = statstable.get(sym_code_raw, "symbol does not exist");
        eosio_assert(st.supply.symbol == symbol, "symbol precision mismatch");

        accounts acnts(_self, owner.value);
        auto it = acnts.find(sym_code_raw);
        if (it == acnts.end()) {
            acnts.emplace(ram_payer, [&](auto &a) {
                a.balance = asset{0, symbol};
            });
        }
    }

    void token::close(name owner, const symbol &symbol) {
        require_auth(owner);
        accounts acnts(_self, owner.value);
        auto it = acnts.find(symbol.code().raw());
        eosio_assert(it != acnts.end(), "Balance row already deleted or never existed. Action won't have any effect.");
        eosio_assert(it->balance.amount == 0, "Cannot close because the balance is not zero.");
        acnts.erase(it);
    }

    void token::sub_balance(name owner, asset value) {
        accounts from_acnts(_self, owner.value);

        const auto &from = from_acnts.get(value.symbol.code().raw(), "no balance object found");
        eosio_assert(from.balance.amount >= value.amount, "overdrawn balance");


        if (from.balance.amount == value.amount) {
            from_acnts.erase(from);
        } else {
            from_acnts.modify(from, same_payer, [&](auto &a) {
                a.balance -= value;
            });
        }
    }

    void token::add_balance(name owner, asset value) {
        accounts to_acnts(_self, owner.value);
        auto to = to_acnts.find(value.symbol.code().raw());
        if (to == to_acnts.end()) {
            to_acnts.emplace(_self, [&](auto &a) {
                a.balance = value;
            });
        } else {
            to_acnts.modify(to, same_payer, [&](auto &a) {
                a.balance += value;
            });
        }
    }

} /// namespace zjubca

EOSIO_DISPATCH( zjubca::token, (create)(issue)(transfer))
