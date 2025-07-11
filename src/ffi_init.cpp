#include "ffi_init.h"
#include "ffi_type.h"
#include "jni.h"
#include "plugin.h"

static _LuaBukkit _luaBukkit;
static JavaVM* javaVM;

void onEnable(void *jniEnv, LuaBukkit luaBukkit) {
    _luaBukkit.env    = (jobject *) luaBukkit.env;
    _luaBukkit.helper = (jobject *) luaBukkit.helper;
    _luaBukkit.io     = (jobject *) luaBukkit.io;
    _luaBukkit.bukkit = (jobject *) luaBukkit.bukkit;
    _luaBukkit.plugin = (jobject *) luaBukkit.plugin;
    _luaBukkit.server = (jobject *) luaBukkit.server;
    _luaBukkit.log    = (jobject *) luaBukkit.log;
    _luaBukkit.out    = (jobject *) luaBukkit.out;


    if (JNI_OK != ((JNIEnv *) jniEnv)->GetJavaVM(&javaVM)) {
        javaVM = nullptr;
    }
    
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

JNIEnv* getJNIEnv() {
    if (nullptr == javaVM) {
        return nullptr;
    }
    JNIEnv* env;
    if (JNI_OK == javaVM->GetEnv((void**) &env, TARGET_JNI_VERSION)) {
        return env;
    } else if (JNI_OK == javaVM->AttachCurrentThread((void**) &env, nullptr)) {
        return env;
    }
    return nullptr;
}

void destroyJNIEnv() {
    if (nullptr != javaVM) {
        javaVM->DetachCurrentThread();
    }
}