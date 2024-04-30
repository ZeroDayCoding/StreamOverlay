#ifndef __PLATFORM_H__
#define __PLATFORM_H__

//====================================
//| Windows Platform Utility Defines |
//====================================
#ifdef _WIN32
    #define __ATTRIBUTE__(name) __declspec(name)
    #define DECLSPEC_NOVTABLE __ATTRIBUTE__(novtable)
    #define STDCALL __stdcall
    #define __COMPILE_FOR_WINDOWS(...) __VA_ARGS__
    #ifdef _WIN64
        #define PLATFORM "Windows 64bit"
        #define __COMPILE_FOR_WINDOWS_32BIT(...)
        #define __COMPILE_FOR_WINDOWS_64BIT(...) __VA_ARGS__
        #define __COMPILE_FOR_32BIT(...)
        #define __COMPILE_FOR_64BIT(...) __VA_ARGS__
    #else
        #define PLATFORM "Windows 32bit"
        #define __COMPILE_FOR_WINDOWS_32BIT(...) __VA_ARGS__
        #define __COMPILE_FOR_WINDOWS_64BIT(...)
        #define __COMPILE_FOR_32BIT(...) __VA_ARGS__
        #define __COMPILE_FOR_64BIT(...) 
    #endif
#else
    #define __COMPILE_FOR_WINDOWS(...)
    #define __COMPILE_FOR_WINDOWS_32BIT(...)
    #define __COMPILE_FOR_WINDOWS_64BIT(...)
#endif

#define __COMPILE_LINE_FOR_WINDOWS(line) __COMPILE_FOR_WINDOWS(line,;)
#define __COMPILE_ENUM_FOR_WINDOWS(line) __COMPILE_FOR_WINDOWS(line,,)
#define __COMPILE_LINE_FOR_WINDOWS_32BIT(line) __COMPILE_FOR_WINDOWS_32BIT(line,;)
#define __COMPILE_ENUM_FOR_WINDOWS_32BIT(line) __COMPILE_FOR_WINDOWS_32BIT(line,,)
#define __COMPILE_LINE_FOR_WINDOWS_64BIT(line) __COMPILE_FOR_WINDOWS_64BIT(line,;)
#define __COMPILE_ENUM_FOR_WINDOWS_64BIT(line) __COMPILE_FOR_WINDOWS_64BIT(line,,)

//====================================
//|  Linux Platform Utility Defines  |
//====================================
#ifdef __linux__
    #define __ATTRIBUTE__(name) __attribute__((name))
    #define DECLSPEC_NOVTABLE // <= Microsoft specific __declspec, cant be used.
    #define STDCALL __ATTRIBUTE__(__stdcall__)
    #define __COMPILE_FOR_LINUX(...) __VA_ARGS__
    #ifdef __x86_64__
        #define PLATFORM "Linux 64bit"
        #define __COMPILE_FOR_LINUX_32BIT(...)
        #define __COMPILE_FOR_LINUX_64BIT(...) __VA_ARGS__
        #define __COMPILE_FOR_32BIT(...) 
        #define __COMPILE_FOR_64BIT(...) __VA_ARGS__
    #else
        #define PLATFORM "Linux 32bit"
        #define __COMPILE_FOR_LINUX_32BIT(...) __VA_ARGS__
        #define __COMPILE_FOR_LINUX_64BIT(...)
        #define __COMPILE_FOR_32BIT(...) __VA_ARGS__
        #define __COMPILE_FOR_64BIT(...) 
    #endif
#else
    #define __COMPILE_FOR_LINUX(...)
    #define __COMPILE_FOR_LINUX_32BIT(...)
    #define __COMPILE_FOR_LINUX_64BIT(...)
#endif

#define __COMPILE_LINE_FOR_LINUX(line) __COMPILE_FOR_LINUX(line;)
#define __COMPILE_ENUM_FOR_LINUX(line) __COMPILE_FOR_LINUX(line,)
#define __COMPILE_LINE_FOR_LINUX_32BIT(line) __COMPILE_FOR_LINUX_32BIT(line;)
#define __COMPILE_ENUM_FOR_LINUX_32BIT(line) __COMPILE_FOR_LINUX_32BIT(line,)
#define __COMPILE_LINE_FOR_LINUX_64BIT(line) __COMPILE_FOR_LINUX_64BIT(line;)
#define __COMPILE_ENUM_FOR_LINUX_64BIT(line) __COMPILE_FOR_LINUX_64BIT(line,)


#define __COMPILE_LINE_FOR_32BIT(line) __COMPILE_FOR_32BIT(line;)
#define __COMPILE_ENUM_FOR_32BIT(line) __COMPILE_FOR_32BIT(line,)
#define __COMPILE_LINE_FOR_64BIT(line) __COMPILE_FOR_64BIT(line;)
#define __COMPILE_ENUM_FOR_64BIT(line) __COMPILE_FOR_64BIT(line,)

#endif//__PLATFORM_H__ GUARD