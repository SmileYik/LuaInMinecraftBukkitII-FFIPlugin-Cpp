#include "plugin.h"
#include "bridge.h"
#include "jni_bridge.h"
#include "ffi_init.h"
#include "jni.h"
#include <memory>
#include <vector>

void onPluginEnable(_LuaBukkit* luaBukkit) {
    // TODO write your code
    JObject* obj = new JObject(*luaBukkit->log);
    obj->get("info")("阿巴阿巴");
    obj->get("info")("abc");
    JNIEnv* jniEnv = getCurrentJNIEnv();
    obj->get("info")(jniEnv, "abc");
}

void onPluginDisable() {
    // TODO clean your code
}

void onPlayerJoin(JNIEnv *jniEnv, void* eventPtr) {
    JObject* obj = new JObject(*getLuaBukkit()->log);
    obj->get("info")("阿巴阿巴");
    JObject event(*((jobject *) eventPtr));
    JObject player = event.get("getPlayer")();
    player.get("sendMessage")("Hello, " + player.get("getName")().toString() + 
                                        "!\n This message from a shared dynamic library!");
}