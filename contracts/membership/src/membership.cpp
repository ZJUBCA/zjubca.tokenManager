#include <membership/membership.hpp>

using namespace eosio;

void membership::enroll(string   student_name,
                        uint64_t student_id,
                        name     eosaccount)
{
    require_auth(eosaccount);
    
    auto new_kid = _members.find( student_id );
    if(new_kid == _members.end() ){
        _members.emplace( _self, [&]( auto& m ) {
            m.student_name  = student_name;
            m.student_id    = student_id;
            m.eosaccount   = eosaccount;
        });
    }

}

EOSIO_DISPATCH( membership, (enroll) )