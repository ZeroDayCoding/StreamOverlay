#include "interfaces/icommon.h"
#include <map>
#include <string>

__NAMESPACE_GUARD_BEGIN(ZDC)
__NAMESPACE_GUARD_BEGIN(StreamOverlay)
__NAMESPACE_GUARD_BEGIN(Interfaces)
static std::map<u64_t, const std::string> mapInterfaceUUIDs;
__EXTERN_C_GUARD_BEGIN

// Generates a quick, non-cryptographically secured, uuid to hopefully prevent collisions. 
//  https://stackoverflow.com/questions/13325125/lightweight-8-byte-hash-function-algorithm
// set 'mix' to some value other than zero if you want a tagged hash    
u64_t GenerateSimpleUUID(const char* strSource, u64_t mix = 0) {
    const unsigned long long mulp = 2654435789;
    mix ^= 104395301;
    while(*strSource)
        mix += (*strSource++ * mulp) ^ (mix >> 23);
    return mix ^ (mix << 37);
}

__TYPE_IUUID RegisterInterface(const char* strInterfaceIdentifier) {
    u64_t tag = 0;
    do {
        u64_t hash = GenerateSimpleUUID(strInterfaceIdentifier, tag);
        auto entry = mapInterfaceUUIDs.find(hash);
        if(entry == mapInterfaceUUIDs.end()) {
            auto insertor = mapInterfaceUUIDs.insert({hash, strInterfaceIdentifier});
            return (IUUID*)(&insertor.first->first);
        }
        tag++; // We will try to find a uuid that works, this function may take a moment to complete!
    } while(0 != tag); // Prevent infinite loop, we will fail at some point.
    // If we didn't find a non-colliding UUID, which is possible but unlikely, we will panic and abort.
    fprintf(stderr, "Attempted to generate a UUID for interface, \"%s\", but failed to create non-colliding uuid!", strInterfaceIdentifier);
    abort();
    exit(-1);
}

__EXTERN_C_GUARD_END
__NAMESPACE_GUARD_END
__NAMESPACE_GUARD_END
__NAMESPACE_GUARD_END