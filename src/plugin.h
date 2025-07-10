#ifndef __PLUGIN_H
#define __PLUGIN_H

#include "ffi_type.h"

void onPluginEnable(JNIEnv *jniEnv, _LuaBukkit* luaBukkit);

void onPluginDisable(JNIEnv *jniEnv);

#endif // __PLUGIN_H