#ifndef __CONFIG_H
#define __CONFIG_H

#ifdef _WIN32
    #define FFI_BRIDGE_API __declspec(dllexport)
    // #ifdef MY_LIBRARY_EXPORTS
    //     #define FFI_BRIDGE_API __declspec(dllexport)
    // #else
    //     #define FFI_BRIDGE_API __declspec(dllimport)
    // #endif
#else
    #define FFI_BRIDGE_API extern
#endif

#endif // __CONFIG_H