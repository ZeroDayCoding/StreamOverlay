#include "icommon.h"
#include <stdio.h>

int main(int argc, const char** argv) {
    const DUUID* uuidDomainStreamOverlay = RegisterInterfaceDomain("StreamOverlay");
    if(!uuidDomainStreamOverlay) {
        printf("Failed to generate StreamOverlay domain!");
        return errno;
    }
    printf("DUUID: %p (%02X%02X%02X%02X-%02X%02X%02X%02X)\n", 
            (void*)uuidDomainStreamOverlay, 
            uuidDomainStreamOverlay->unknown[0], 
            uuidDomainStreamOverlay->unknown[1], 
            uuidDomainStreamOverlay->unknown[2], 
            uuidDomainStreamOverlay->unknown[3], 
            uuidDomainStreamOverlay->unknown[4], 
            uuidDomainStreamOverlay->unknown[5], 
            uuidDomainStreamOverlay->unknown[6], 
            uuidDomainStreamOverlay->unknown[7]);
    return 0;
}