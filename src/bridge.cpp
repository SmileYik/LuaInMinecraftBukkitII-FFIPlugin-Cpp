#include "bridge.h"
#include "jni.h"
#include "jni_bridge.h"

JObjectProxy::JObjectProxy(jobject obj, 
                           JObjectProxyType pxyType, 
                           const std::string& calledName) : 
                           instance(obj),
                           proxyType(pxyType),
                           name(calledName) {
    
}

JObject::JObject(jobject obj) : instance(obj) {

}

JObjectProxy JObject::get(const std::string& name) {
    return JObjectProxy(instance, JObjectProxyType::Method, name);
}

std::string JObject::toString() {
    JNIEnv* env = getCurrentJNIEnv();
    std::string result = toString(env);
    destroyJNIEnv();
    return nullptr == env ? "" : result;
}

std::string JObject::toString(JNIEnv* env) {
    return javaObject2String(env, instance);
}

JObject JObjectProxy::call(std::list<std::any>& params) const {
    return javaCallMethod(nullptr, instance, name, params);
}

std::string JObject::operator+(std::string str) {
    return toString() + str;
}

std::string JObject::operator+(JObject obj) {
    JNIEnv* env = getCurrentJNIEnv();
    if (env == nullptr) return "";
    std::string ret = toString(env) + obj.toString(env);
    destroyJNIEnv();
    return ret;
}