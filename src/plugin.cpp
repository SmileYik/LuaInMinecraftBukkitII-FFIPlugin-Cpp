#include "plugin.h"
#include "bridge.h"
#include "ffi_init.h"
#include "jni.h"
#include <memory>
#include <vector>

void onPluginEnable(JNIEnv *jniEnv, _LuaBukkit* luaBukkit) {
    // TODO write your code
    JObject* obj = new JObject(*luaBukkit->log);
    obj->get("info")("阿巴阿巴");
    obj->get("info")("abc");
    obj->get("info")(jniEnv, "abc");
}

void onPluginDisable(JNIEnv *jniEnv) {
    // TODO clean your code
}

extern "C" void onPlayerJoin(JNIEnv *jniEnv, void* eventPtr) {
    JObject* obj = new JObject(*getLuaBukkit()->log);
    obj->get("info")("阿巴阿巴");
    JObject event(*((jobject *) eventPtr));
    std::shared_ptr<JObject> player = event.get("getPlayer")();
    player->get("sendMessage")("Hello, " + player->get("getName")()->toString() + 
                                        "!\n This message from a shared dynamic library!");
}