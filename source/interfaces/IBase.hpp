#define __INTERFACE_FORCE_C_STYLE
#include "interfaces/IBase.h"
#include <stdatomic.h>

__NAMESPACE_GUARD_BEGIN(ZDC)
__NAMESPACE_GUARD_BEGIN(StreamOverlay)
__NAMESPACE_GUARD_BEGIN(Interfaces)

struct IBaseInternal {
    // The number of references to this interface.
    _Atomic(IRefCount_t) nRefs;
};
extern IBase::VFTable* vftable_IBase;

__NAMESPACE_GUARD_END
__NAMESPACE_GUARD_END
__NAMESPACE_GUARD_END