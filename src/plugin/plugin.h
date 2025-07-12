#ifndef __PLUGIN_H
#define __PLUGIN_H

#include "ffi_type.h"

void onPluginEnable(_LuaBukkit* luaBukkit);

void onPluginDisable();

extern "C" void onPlayerJoin(JNIEnv *jniEnv, void* eventPtr);

#endif // __PLUGIN_H