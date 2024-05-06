#define __INTERFACE_FORCE_C_STYLE
#include "interfaces/IString.h"
#include <memory>
#include <string.h>
#include <stdatomic.h>

__EXTERN_C_GUARD_BEGIN
__NAMESPACE_GUARD_BEGIN(ZDC)
__NAMESPACE_GUARD_BEGIN(StreamOverlay)
__NAMESPACE_GUARD_BEGIN(Interfaces)
EXTERN_INTERFACE_UUID(IBase);
DEFINE_INTERFACE_UUID(IString, RegisterInterface("IString"));
DEFINE_INTERFACE_UUID(IAsciiString, RegisterInterface("IAsciiString"));
DEFINE_INTERFACE_UUID(IUtf8String, RegisterInterface("IUtf8String"));
DEFINE_INTERFACE_UUID(IUtf16String, RegisterInterface("IUtf16String"));
DEFINE_INTERFACE_UUID(IUtf32String, RegisterInterface("IUtf32String"));

struct _UnknownString : public IString {
    // The number of references to this string interface.
    _Atomic(IRefCount_t) nRefs;
    // A pointer to a byte buffer that will store our string.
    void* pBuffer;
    // The capacity of the pBuffer that stores our string.
    size_t nCapacity;
};

IRefCount_t STDCALL IString_Reference(IThis pThis) {
    _UnknownString* _this = (_UnknownString*)pThis;
    return ++_this->nRefs;
}

IRefCount_t STDCALL IString_Release(IThis pThis) {
    _UnknownString* _this = (_UnknownString*)pThis;
    IRefCount_t refs = (--_this->nRefs);
    if(refs == 0) {
        if(_this->pBuffer)
            free(_this->pBuffer);
        free(_this);
    }
    return refs;
}

bool_t STDCALL IString_TryCastTo(IThis pThis, __TYPE_IUUID rUUID, void** ppInterface) {
    _UnknownString* _this = (_UnknownString*)pThis;
    if(rUUID == UUID_IBase || rUUID == UUID_IString) {
        _this->lpVFTable->Reference(_this);
        *ppInterface = pThis;
        return true;
    }
    else if(rUUID == UUID_IAsciiString)
        return _this->lpVFTable->ToAscii(_this, (IAsciiString**)ppInterface);
    else if(rUUID == UUID_IUtf8String)
        return _this->lpVFTable->ToUtf8(_this, (IUtf8String**)ppInterface);
    else if(rUUID == UUID_IUtf16String)
        return _this->lpVFTable->ToUtf16(_this, (IUtf16String**)ppInterface);
    else if(rUUID == UUID_IUtf32String)
        return _this->lpVFTable->ToUtf32(_this, (IUtf32String**)ppInterface);
    return false;
}

size_t STDCALL IString_Capacity(IThis pThis) {
    _UnknownString* _this = (_UnknownString*)pThis;
    return _this->nCapacity;
}

void STDCALL IString_Clear(IThis pThis) {
    _UnknownString* _this = (_UnknownString*)pThis;
}

static IString::VFTable vftable_IString {
    /* IBase */
    IString_TryCastTo,  // TryCastTo
    IString_Reference,  // Reference
    IString_Release,    // Release
    /* IString */
    nullptr,            // Length
    nullptr,            // Size
    IString_Capacity,   // Capacity
    IString_Clear,      // Clear
    nullptr, // Substring
    nullptr, // ToAscii
    nullptr, // ToUtf8
    nullptr, // ToUtf16
    nullptr, // ToUtf32
};

size_t STDCALL IAsciiString_Length(IThis pThis) {
    _UnknownString* _this = (_UnknownString*)pThis;
    if(!_this->pBuffer || !_this->nCapacity) return 0;
    size_t i = 0;
    char cVal;
    for(; i < _this->nCapacity; i++) {
        // Get the next character, and breakout if its a null terminator.
        cVal = ((char*)_this->pBuffer)[i];
        if(!cVal) break;
        // Check if we are an invalid Ascii character's goto next character if we aren't.
        if(!(cVal & 0x80)) continue;
        // Since we are in ascii we don't support any UTF-8, aka highest bit's being set.
        errno = EPROTONOSUPPORT;
        return 0;
    }
    return i;
}
#define IAsciiString_Size IAsciiString_Length

static IAsciiString::VFTable __generateIAsciiStringVFTable() {
    IAsciiString::VFTable vftable;
    memset(&vftable, 0, sizeof(IAsciiString::VFTable));
};
static IAsciiString::VFTable vftable_IAsciiString = __generateIAsciiStringVFTable();

__NAMESPACE_GUARD_END
__NAMESPACE_GUARD_END
__NAMESPACE_GUARD_END
__EXTERN_C_GUARD_END