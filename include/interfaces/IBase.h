#ifndef __IBASE_H__
#define __IBASE_H__
#include "interfaces/ICommon.h"

__NAMESPACE_GUARD_BEGIN(ZDC)
__NAMESPACE_GUARD_BEGIN(StreamOverlay)
__NAMESPACE_GUARD_BEGIN(Interfaces)
__EXTERN_C_GUARD_BEGIN

/**
 * @brief A reference count for a particular interface.
 * @note When implementing a custom interface you must use _atomic_fetch_add and __atomic_fetch_sub, using __ATOMIC_ACQ_REL, to modify the internal reference counter.
 */
typedef u32_t IRefCount_t;

DECLARE_INTERFACE IBase
{
public:
    DECLARE_INTERFACE_VFTABLE
    /**
     * @brief Tries to cast the current interface to another of a specific uuid type.
     * @note This function will fail with the return value false if the interface doesn't support the requested interface.
     * @param rUUID A non-null pointer to the IUUID object that describes this interface.
     * @param ppInterface A non-null pointer to an interface object pointer, must be descendant of IBase.
     * @returns True if this interface was successfully casted to the given interface, otherwise False.
     */
    DECLARE_INTERFACE_VFUNCTION(TryCast, bool_t)(IThis_ __TYPE_IUUID rUUID, void** ppInterface) PURE;
    /**
     * @brief Tells the interface that a new reference has been made to it. This will increase the reference counter by one.
     * @returns The new reference count to this interface object.
     */
    DECLARE_INTERFACE_VFUNCTION(Reference, IRefCount_t)(IThis) PURE;
    /**
     * @brief Tells the interface that a reference has been released from it. This will decrease the reference counter by one, and may perform garbage collection.
     * @note After calling this function you, the caller, must null out the pointer used to call this function.
     * @note Act under the assumption that by calling this function the underlying object has been destroyed and freed from memory upon return.
     * @returns The new reference count to this interface object.
     */
    DECLARE_INTERFACE_VFUNCTION(Release, IRefCount_t)(IThis) PURE;
    DELCARE_INTERFACE_VFTABLE_END
};


__EXTERN_C_GUARD_END
__NAMESPACE_GUARD_END
__NAMESPACE_GUARD_END
__NAMESPACE_GUARD_END
#endif//__IBASE_H__ GUARD