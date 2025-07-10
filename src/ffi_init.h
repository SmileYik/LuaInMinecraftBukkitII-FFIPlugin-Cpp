#ifndef __FFI_INIT_H
#define __FFI_INIT_H

#include <jni.h>
#include "ffi_type.h"

#ifdef _WIN32
    #ifdef MY_LIBRARY_EXPORTS
        #define FFI_BRIDGE_API __declspec(dllexport)
    #else
        #define FFI_BRIDGE_API __declspec(dllimport)
    #endif
#else
    #define FFI_BRIDGE_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

FFI_BRIDGE_API
void onEnable(void *jniEnv, struct LuaBukkit luaBukkit);

FFI_BRIDGE_API
void onDisable(void *jniEnv);

#ifdef __cplusplus
}
#endif

_LuaBukkit* getLuaBukkit();

#endif // __FFI_INIT_H