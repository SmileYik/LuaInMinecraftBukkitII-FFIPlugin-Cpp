#include "ffi_init.h"
#include "ffi_type.h"
#include "plugin.h"

static _LuaBukkit _luaBukkit;

void onEnable(void *jniEnv, LuaBukkit luaBukkit) {
    _luaBukkit.env    = (jobject *) luaBukkit.env;
    _luaBukkit.helper = (jobject *) luaBukkit.helper;
    _luaBukkit.io     = (jobject *) luaBukkit.io;
    _luaBukkit.bukkit = (jobject *) luaBukkit.bukkit;
    _luaBukkit.plugin = (jobject *) luaBukkit.plugin;
    _luaBukkit.server = (jobject *) luaBukkit.server;
    _luaBukkit.log    = (jobject *) luaBukkit.log;
    _luaBukkit.out    = (jobject *) luaBukkit.out;

    onPluginEnable((JNIEnv *) jniEnv, &_luaBukkit);
}

void onDisable(void *jniEnv) {
    onPluginDisable((JNIEnv *) jniEnv);

    _luaBukkit.env    = nullptr;
    _luaBukkit.helper = nullptr;
    _luaBukkit.io     = nullptr;
    _luaBukkit.bukkit = nullptr;
    _luaBukkit.plugin = nullptr;
    _luaBukkit.server = nullptr;
    _luaBukkit.log    = nullptr;
    _luaBukkit.out    = nullptr;
}

_LuaBukkit* getLuaBukkit() {
    return &_luaBukkit;
}