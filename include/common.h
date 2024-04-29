#ifndef __COMMON_H__
#define __COMMON_H__
#include "platform.h"

// Define a macro for our extern "C" guard.
#ifdef __cplusplus
#define __EXTERN_C_GUARD_BEGIN extern "C" {
#define __EXTERN_C_GUARD_END }
#define __NAMESPACE_GUARD_BEGIN(ns) namespace ns {
#define __NAMESPACE_GUARD_END }
#else
#define __EXTERN_C_GUARD_BEGIN
#define __EXTERN_C_GUARD_END
#define __NAMESPACE_GUARD_BEGIN(ns)
#define __NAMESPACE_GUARD_END
#endif

// Define our typedef 
__NAMESPACE_GUARD_BEGIN(StreamOverlay)
__EXTERN_C_GUARD_BEGIN

typedef char        s8_t;
typedef short       s16_t;
typedef int         s32_t;
typedef long        sl32_t;
typedef long long   s64_t;

typedef unsigned char        u8_t;
typedef unsigned short       u16_t;
typedef unsigned int         u32_t;
typedef unsigned long        ul32_t;
typedef unsigned long long   u64_t;

typedef void* vptr_t;

__EXTERN_C_GUARD_END
__NAMESPACE_GUARD_END
#endif//__COMMON_H__ GUARD