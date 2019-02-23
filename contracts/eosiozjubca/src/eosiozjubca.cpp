/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include <eosiozjubca/eosiozjubca.hpp>

namespace eosio {

void token::create( name   issuer,
                    asset  maximum_supply)
{
    require_auth( _self );

    auto sym = maximum_supply.symbol;
    eosio_assert( sym.is_valid(), "invalid symbol name" );
    eosio_assert( maximum_supply.is_valid(), "invalid supply");
    eosio_assert( maximum_supply.amount > 0, "max-supply must be positive");

    stats statstable( _self, sym.code().raw() );
    auto existing = statstable.find( sym.code().raw() );
    eosio_assert( existing == statstable.end(), "token with symbol already exists" );

    statstable.emplace( _self, [&]( auto& s ) {
       s.supply.symbol           = maximum_supply.symbol;
       s.max_supply              = maximum_supply;
       s.issuer                  = issuer;

       s.frozen_amount           = maximum_supply * 90 / 100;    // freeze 90% tokens since foundation
       s.release_amount_pertime  = maximum_supply * 3 / 100;   // unfreeze 3% every release day
       s.released_times            = 0;
       s.next_release_day        = 1538236800;              // 2018/9/30 00:00:00
    });
}


void token::issue( name to, asset quantity, string memo )
{
    auto sym = quantity.symbol;
    eosio_assert( sym.is_valid(), "invalid symbol name" );
    eosio_assert( memo.size() <= 256, "memo has more than 256 bytes" );

    stats statstable( _self, sym.code().raw() );
    auto existing = statstable.find( sym.code().raw() );
    eosio_assert( existing != statstable.end(), "token with symbol does not exist, create token before issue" );
    const auto& st = *existing;

    require_auth( st.issuer );
    eosio_assert( quantity.is_valid(), "invalid quantity" );
    eosio_assert( quantity.amount > 0, "must issue positive quantity" );

    eosio_assert( quantity.symbol == st.supply.symbol, "symbol precision mismatch" );
    
    // ZJUBCA is founded on 2018/3/30 00:00:00 Unix time stamp: 1522339200
    // Release date is set on 3.30 and 9.30 
    uint64_t first_half = 3600 * 24 * 184; // first half: 3.30~9.30
    uint64_t second_half_c = 3600 * 24 * 181; // second half for common year: 9.30~3.30
    uint64_t second_half_l = 3600 * 24 * 182; // second half for leap year: 9.30~3.30

    // Freeze 90% token for 15 years, release 3% every release day.
    // update release date
    if(now() >= st.next_release_day && st.released_times <= 30){
       if(st.released_times < 30){
          if(st.released_times % 2 == 1){ // first half
             statstable.modify( st, same_payer, [&]( auto& s ) {
               s.released_times += 1;
               s.frozen_amount -= st.release_amount_pertime;
               s.next_release_day += first_half;
             });
          }
          else if(st.released_times % 8 == 2){ // second half for leap year
            statstable.modify( st, same_payer, [&]( auto& s ) {
               s.released_times += 1;
               s.frozen_amount -= st.release_amount_pertime;
               s.next_release_day += second_half_l;
             });
          }
          else { // second half for common year
            statstable.modify( st, same_payer, [&]( auto& s ) {
               s.released_times += 1;
               s.frozen_amount -= st.release_amount_pertime;
               s.next_release_day += second_half_c;
             });
          }
       }
       else{
          statstable.modify( st, same_payer, [&]( auto& s ) {
            s.next_release_day = -1;
          });
       }
    }

    eosio_assert( quantity.amount <= st.max_supply.amount - st.supply.amount - st.frozen_amount.amount, "quantity exceeds available supply");

    statstable.modify( st, same_payer, [&]( auto& s ) {
       s.supply += quantity;
    });

    add_balance( st.issuer, quantity, st.issuer );

    if( to != st.issuer ) {
      SEND_INLINE_ACTION( *this, transfer, { {st.issuer, "active"_n} },
                          { st.issuer, to, quantity, memo }
      );
    }
   
}

void token::retire( asset quantity, string memo )
{
    auto sym = quantity.symbol;
    eosio_assert( sym.is_valid(), "invalid symbol name" );
    eosio_assert( memo.size() <= 256, "memo has more than 256 bytes" );

    stats statstable( _self, sym.code().raw() );
    auto existing = statstable.find( sym.code().raw() );
    eosio_assert( existing != statstable.end(), "token with symbol does not exist" );
    const auto& st = *existing;

    require_auth( st.issuer );
    eosio_assert( quantity.is_valid(), "invalid quantity" );
    eosio_assert( quantity.amount > 0, "must retire positive quantity" );

    eosio_assert( quantity.symbol == st.supply.symbol, "symbol precision mismatch" );

    statstable.modify( st, same_payer, [&]( auto& s ) {
       s.supply -= quantity;
    });

    sub_balance( st.issuer, quantity, st.issuer );
}

void token::transfer( name    from,
                      name    to,
                      asset   quantity,
                      string  memo )
{
    eosio_assert( from != to, "cannot transfer to self" );
    require_auth( from );
    eosio_assert( is_account( to ), "to account does not exist");
    auto sym = quantity.symbol.code();
    stats statstable( _self, sym.raw() );
    const auto& st = statstable.get( sym.raw() );

    require_recipient( from );
    require_recipient( to );

    eosio_assert( quantity.is_valid(), "invalid quantity" );
    eosio_assert( quantity.amount > 0, "must transfer positive quantity" );
    eosio_assert( quantity.symbol == st.supply.symbol, "symbol precision mismatch" );
    eosio_assert( memo.size() <= 256, "memo has more than 256 bytes" );

    //auto payer = has_auth( to ) ? to : from;
    
    sub_balance( from, quantity, st.issuer );
    add_balance( to, quantity, st.issuer );
}

void token::sub_balance( name owner, asset value, name ram_payer ) {
   accounts from_acnts( _self, owner.value );

   const auto& from = from_acnts.get( value.symbol.code().raw(), "no balance object found" );
   eosio_assert( from.balance.amount >= value.amount, "overdrawn balance" );

   from_acnts.modify( from, ram_payer, [&]( auto& a ) {
         a.balance -= value;
      });
}

void token::add_balance( name owner, asset value, name ram_payer )
{
   accounts to_acnts( _self, owner.value );
   auto to = to_acnts.find( value.symbol.code().raw() );
   if( to == to_acnts.end() ) {
      to_acnts.emplace( ram_payer, [&]( auto& a ){
        a.balance = value;
      });
   } else {
      to_acnts.modify( to, same_payer, [&]( auto& a ) {
        a.balance += value;
      });
   }
}

void token::open( name owner, const symbol& symbol, name ram_payer )
{
   require_auth( ram_payer );

   auto sym_code_raw = symbol.code().raw();

   stats statstable( _self, sym_code_raw );
   const auto& st = statstable.get( sym_code_raw, "symbol does not exist" );
   eosio_assert( st.supply.symbol == symbol, "symbol precision mismatch" );

   accounts acnts( _self, owner.value );
   auto it = acnts.find( sym_code_raw );
   if( it == acnts.end() ) {
      acnts.emplace( ram_payer, [&]( auto& a ){
        a.balance = asset{0, symbol};
      });
   }
}

void token::close( name owner, const symbol& symbol )
{
   require_auth( owner );
   accounts acnts( _self, owner.value );
   auto it = acnts.find( symbol.code().raw() );
   eosio_assert( it != acnts.end(), "Balance row already deleted or never existed. Action won't have any effect." );
   eosio_assert( it->balance.amount == 0, "Cannot close because the balance is not zero." );
   acnts.erase( it );
}

} /// namespace eosio

EOSIO_DISPATCH( eosio::token, (create)(issue)(transfer)(open)(close)(retire) )
