#ifndef __ICOMMON_H__
#define __ICOMMON_H__
#include "common.h"

#define DECLSPEC_NOVTABLE __declspec(novtable)

#if !defined(__cplusplus) or defined(__INTERFACE_FORCE_C_STYLE)
    #define DECLARE_INTERFACE struct
#else

#endif

#endif//__ICOMMON_H__ GUARD