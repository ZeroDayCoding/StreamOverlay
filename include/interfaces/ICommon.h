#ifndef __ICOMMON_H__
#define __ICOMMON_H__
#include "./common.h"

// C Style Implementation vs C++ Style Implementation Macros.
#if !defined(__cplusplus) || defined(__INTERFACE_FORCE_C_STYLE)
    #define FORWARD_DECLARE_INTERFACE(name) struct name;
    // Declares a C style interface using a struct.
    #define DECLARE_INTERFACE struct
    // Declares a C style VFTable (Virtual Function Table), does nothing in c++ style.
    #define DECLARE_INTERFACE_VFTABLE struct VFTable {
    // Declares a C style VFTable (Virtual Function Table) that inherits from a baseclass, does nothing in c++ style.
    #define DECLARE_INTERFACE_VFTABLE_(baseclass) struct VFTable : public baseclass::VFTable {
    // Declares the end of a C style VFTable (Virtual Function Table), does nothing in c++ style.
    #define DELCARE_INTERFACE_VFTABLE_END } *lpVFTable;
    // Informs the interface, when in the c++ style, that the interface will inherit from baseclass.
    #define INTERFACE_INHERITS_FROM(baseclass)
    // In C style this is the objects lpVFTable pointer.
    #define INTERFACE_GET_VFTABLE(obj) obj->lpVFTable
    // Declares a C style virtual function, note must be STDCALL otherwise will fail.
    #define DECLARE_INTERFACE_VFUNCTION(name, ret) ret(STDCALL * name)
    // In C style, the compiler needs us to explicitly note this down.
    #define IThis void*
    // In C style, the compiler needs us to explicitly note this down.
    #define IThis_ void*,
    // In C style, the compiler needs us to explicitly note this down.
    #define IThisPassthrough(obj) (IThis)obj,
#else
    #define FORWARD_DECLARE_INTERFACE(name) class name;
    // Declares a C++ style Interface, uses novtable to inform the caller that our interface will 
    // have no attached vftable to begin with.
    #define DECLARE_INTERFACE class DECLSPEC_NOVTABLE
    // Declares a C style VFTable (Virtual Function Table), does nothing in c++ style.
    #define DECLARE_INTERFACE_VFTABLE
    // Declares a C style VFTable (Virtual Function Table) that inherits from a baseclass, does nothing in c++ style.
    #define DECLARE_INTERFACE_VFTABLE_(baseclass)
    // Declares the end of a C style VFTable (Virtual Function Table), does nothing in c++ style.
    #define DELCARE_INTERFACE_VFTABLE_END
    // Informs the interface, when in the c++ style, that the interface will inherit from baseclass.
    #define INTERFACE_INHERITS_FROM(baseclass) : public baseclass
    // In C++ style this is just the object itself.
    #define INTERFACE_GET_VFTABLE(obj) obj
    // Declares a C++ style virtual function, note must be STDCALL otherwise will fail.
    #define DECLARE_INTERFACE_VFUNCTION(name, ret) virtual ret STDCALL name
    // In C++ style, this macros get implied by the compiler.
    #define IThis
    // In C++ style, this macros get implied by the compiler.
    #define IThis_
    // In C++ style, this macros get implied by the compiler.
    #define IThisPassthrough(obj)
#endif

// Pure implementation, translates to nothing to see/do here.
#define PURE =0

// Fetches the given interfaces function from its VFTable (Virtual Function Table). 
#define IPtrFetch(ptr, fnName) INTERFACE_GET_VFTABLE(obj)->fnName
// Calls the interfaces function, passes along the object in ptr form with the potential arguments.
// NOTE: This macro will use "ptr" argument twice, meaning if you pass a function to this in the
//       "ptr" argument then the function will be called twice!!
#define IPtrCall(ptr, fnName, ...) IPtrFetch(obj)(IThisPassthrough(obj) __VA_ARGS__)
// Turns the given object into a pointer and simply passes everything along to IPtrCall.
#define IObjCall(obj, fnName, ...) IPtrCall(&obj, fnName, __VA_ARGS__)

__NAMESPACE_GUARD_BEGIN(ZDC)
__NAMESPACE_GUARD_BEGIN(StreamOverlay)
__NAMESPACE_GUARD_BEGIN(Interfaces)
__EXTERN_C_GUARD_BEGIN

/**
 * A 64-bit unique univeral identifier for an interface or domain.
 * NOTE: A _UUID is by definition the address of the _UUID itself, 
 * in 32 bit mode the top 4 bytes are defined as the hash 32bit 
 * hash of the interface/domain name respectively.
 */
typedef struct _UUID { u8_t unknown[8]; } IUUID;


#ifdef __cplusplus
#define __TYPE_IUUID const ZDC::StreamOverlay::Interfaces::IUUID*
#else
#define __TYPE_IUUID const IUUID*
#endif

#define DEFINE_INTERFACE_UUID(interface, value) __TYPE_IUUID const UUID_##interface {value}; 
#define EXTERN_INTERFACE_UUID(interface) extern __TYPE_IUUID const UUID_##interface;

/**
 * @brief Registers an interface's name to a univerally unique identifier.
 * @returns A pointer to the interfaces newly created UUID.
*/
__TYPE_IUUID RegisterInterface(const char* strInterfaceIdentifier);

__EXTERN_C_GUARD_END
__NAMESPACE_GUARD_END
__NAMESPACE_GUARD_END
__NAMESPACE_GUARD_END

#endif//__ICOMMON_H__ GUARD