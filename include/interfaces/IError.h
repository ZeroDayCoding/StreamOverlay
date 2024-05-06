#ifndef __IERROR_H__
#define __IERROR_H__
#include "interfaces/IBase.h"

__NAMESPACE_GUARD_BEGIN(ZDC)
__NAMESPACE_GUARD_BEGIN(StreamOverlay)
__NAMESPACE_GUARD_BEGIN(Interfaces)
__EXTERN_C_GUARD_BEGIN

DECLARE_INTERFACE IError
INTERFACE_INHERITS_FROM(IBase)
{
public:
    DECLARE_INTERFACE_VFTABLE_(IBase)
    /**
     * @brief Gets the error identifier, a UTF-8 compatible string.
     * @note The error string only exists as long as you have the IError.
     * @returns A UTF-8 compatible string that identifies the error.
    */
    DECLARE_INTERFACE_VFUNCTION(GetErrorIdentifier,const char*)(IThis) PURE;

    DECLARE_INTERFACE_VFUNCTION(GetErrorMessage,u32_t)(IThis_ char* pBuffer, size_t nBufferSize) PURE;

    DELCARE_INTERFACE_VFTABLE_END
};


__EXTERN_C_GUARD_END
__NAMESPACE_GUARD_END
__NAMESPACE_GUARD_END
__NAMESPACE_GUARD_END
#endif//__IERROR_H__ GUARD