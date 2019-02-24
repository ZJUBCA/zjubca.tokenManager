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
    eosio_assert(new_kid == _members.end(), "member with this id alreadty exists");
    // check uniqueness of eos account
    auto account_index = _members.get_index<"eosaccount"_n>();
    auto new_kid_account = account_index.find(eosaccount.value);
    eosio_assert(new_kid_account == account_index.end(), "member with this account alreadty exists");
    // check register fee
    eosio_assert(register_fee.is_valid(), "Invalid token transfer...");
    eosio_assert(register_fee.amount == 10000 , "wrong register fee!");
    eosio_assert(register_fee.symbol == symbol("CCC", 4), "wrong token symbol!");

    action(
        permission_level{ eosaccount,"active"_n },
        "eosiozjubca"_n, "transfer"_n,
        std::make_tuple(eosaccount, "eosiozjubca"_n, register_fee, std::string("register"))
    ).send();
    
    _members.emplace( _self, [&]( auto& m ) {
        m.studentname      = studentname;
        m.student_id        = student_id;
        m.eosaccount        = eosaccount;
        m.registration_date = now();
        m.expiration_date   = now() + 3600 * 24 * 183;
    });
}

void membership::quit(name user)
{
    require_auth(user);
    auto account_index = _members.get_index<"eosaccount"_n>();
    auto kid = account_index.find(user.value);
    eosio_assert(kid != account_index.end(), "record doesn't exist");
    account_index.erase(kid);
}

EOSIO_DISPATCH( membership, (enroll)(quit))