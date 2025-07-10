#include "plugin.h"
#include "bridge.h"

void onPluginEnable(JNIEnv *jniEnv, _LuaBukkit* luaBukkit) {
    // TODO write your code
    call(jniEnv, *luaBukkit->log, "info", "t", "Hello ffi plugin!");
}

void onPluginDisable(JNIEnv *jniEnv) {
    // TODO clean your code
}