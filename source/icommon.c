#include "icommon.h"
#include <string.h>
#include <malloc.h>
#include <stdio.h>
__NAMESPACE_GUARD_BEGIN(StreamOverlay)
__NAMESPACE_GUARD_BEGIN(Interfaces)
__EXTERN_C_GUARD_BEGIN

ul32_t djb2HashUTF8(const unsigned char *str)
{
    ul32_t hash = 5481;
    int c;
    while ((c = *str++)) hash = ((hash << 5) + hash) ^ c;
    return hash;
}

typedef struct _Domain {
    char* strDomainName;
    DUUID oUUID;
} Domain;

typedef struct _DomainEntry {
    // A pointer to the next domain entry in our list of domain entries.
    struct _DomainEntry* pNext;
    // The domain object that this domain entry describes.
    Domain oDomain;
} DomainEntry;

typedef struct HashedDomainEntries {
    // The next hashed domain entry in our list of domain entries.
    struct _HashedDomainEntry* pNext;
    // The hash value for this list of domains.
    ul32_t nHash;
    // A pointer to the first registered domain entry in this chain of domains.
    DomainEntry* lpDomainEntries;
} HashedDomainEntries;

static HashedDomainEntries* lpStartDomainEntries = 0;

const DUUID* CreateDomain(const char* strDomainName, HashedDomainEntries* pHashedDomain, DomainEntry* pLastEntry) {
    DomainEntry* pDomainEntry = (DomainEntry*)malloc(sizeof(DomainEntry));
    if(!pDomainEntry) { errno = ENOMEM; return 0; }
    // Copy the domain name into our very own string, we don't want to lose access to it if caller free's it.
    size_t nNameSize = strlen(strDomainName) + 1;
    char* strName = (char*)malloc(nNameSize);
    if(!strName) { errno = ENOMEM; free(pDomainEntry); return 0; }
    memcpy(strName, strDomainName, nNameSize);
    pDomainEntry->oDomain.strDomainName = strName;
    // Here we memcpy over the UUID's address into the UUID itself.
    char* pUUID = (char*)&pDomainEntry->oDomain.oUUID.unknown;
    size_t addrUUID = (size_t)pUUID;
    memcpy(pUUID, &addrUUID, sizeof(size_t));
    // In the event of a 32bit system, we will fill the top 4 bytes with the hash of the domain name.
    __COMPILE_LINE_FOR_32BIT(memcpy(pUUID + 4, &pHashedDomain->nHash, sizeof(ul32_t)));
    // Insert our entry into the entry list.
    if(pLastEntry) {
        pDomainEntry->pNext = pLastEntry->pNext;
        pLastEntry->pNext = pDomainEntry;
    }
    else {
        pDomainEntry->pNext = pHashedDomain->lpDomainEntries;
        pHashedDomain->lpDomainEntries = pDomainEntry;
    }
    printf("Registered domain: \"%s\"\n", strDomainName);
    return &pDomainEntry->oDomain.oUUID;
}

const DUUID* RegisterInterfaceDomain(const char* strDomainName) {
    ul32_t nHash = djb2HashUTF8((const unsigned char*)strDomainName);
    HashedDomainEntries* pHashedDomainEntry = lpStartDomainEntries, *pLastHashedDomainEntry = 0;
    while(pHashedDomainEntry) {
        // Check for matching hash value.
        if(nHash == pHashedDomainEntry->nHash) {
            int nCMP;
            DomainEntry* pDomainEntry = pHashedDomainEntry->lpDomainEntries, *pLastDomainEntry = 0;
            while(pDomainEntry) {
                // Ensure we don't register the same domain name twice.
                nCMP = strcmp(strDomainName, pDomainEntry->oDomain.strDomainName);
                if(nCMP == 0) return 0;
                // Otherwise, check for alphabetical insertion.
                if(nCMP > 0) break;
                pLastDomainEntry = pDomainEntry;
                pDomainEntry = pDomainEntry->pNext;
            }
            // Create and return domain.
            return CreateDomain(strDomainName, pHashedDomainEntry, pLastDomainEntry);
        }
        // Hashes are placed in by lowest to highest, so we will insert a new hashed domain entry.
        if(nHash > pHashedDomainEntry->nHash) break;
        pLastHashedDomainEntry = pHashedDomainEntry;
        pHashedDomainEntry = pHashedDomainEntry->pNext;
    }
    // Attempt to create the new hashed domain entry.
    pHashedDomainEntry = (HashedDomainEntries*)malloc(sizeof(HashedDomainEntries));
    if(!pHashedDomainEntry) { errno = ENOMEM; return 0; }
    pHashedDomainEntry->nHash = nHash;
    pHashedDomainEntry->lpDomainEntries = 0;
    if(pLastHashedDomainEntry) {
        pHashedDomainEntry->pNext = pLastHashedDomainEntry->pNext;
        pLastHashedDomainEntry->pNext = pHashedDomainEntry;
    }
    else {
        pHashedDomainEntry->pNext = lpStartDomainEntries;
        lpStartDomainEntries = pHashedDomainEntry;
    }
    // Good, now we can try to insert into the list.
    return CreateDomain(strDomainName, pHashedDomainEntry, 0);
}

const IUUID* RegisterInterface(const char* strInterfaceName, const DUUID* uuidInterfaceDomain) {

}

__EXTERN_C_GUARD_END
__NAMESPACE_GUARD_END
__NAMESPACE_GUARD_END