#include "plugin.h"
#include "bridge.h"
#include "jni.h"

void onPluginEnable(JNIEnv *jniEnv, _LuaBukkit* luaBukkit) {
    // TODO write your code
    JObject* obj = new JObject(*luaBukkit->log);
    obj->get("info")("阿巴阿巴");
    obj->get("info")("abc");
    obj->get("info")(jniEnv, "abc");
    jobject abc[] = {obj->instance};
    int def[] = {1, 2, 3};
    obj->get("info")(jniEnv, abc, def);
    obj->get("info")(obj->toString());
}

void onPluginDisable(JNIEnv *jniEnv) {
    // TODO clean your code
}