#ifndef __BRIDGE_H
#define __BRIDGE_H

#include <jni.h>
#include <ffi_init.h>
#include <cstdint> 
#include <memory>
#include <string>
#include <any>
#include <vector>


class JObject;
class JObjectProxy;
enum JObjectProxyType {
    Field,
    Method,
    Constructor
};

class JObjectProxy {
private:
    const jobject instance;
    const JObjectProxyType proxyType;
    std::string name;
public:
    JObjectProxy(jobject obj, JObjectProxyType pxyType, const std::string& calledName);

    template<typename... Args>
    std::shared_ptr<JObject> operator()(Args&&... args) const {
        std::vector<std::any> params;
        (params.push_back(std::forward<Args>(args)), ...);
        return call(params);
    }
private:
    std::shared_ptr<JObject> call(const std::vector<std::any>& params) const;
};

class JObject {
public:
    const jobject instance;
public:
    JObject(jobject object);
public:
    JObjectProxy get(const std::string& name);
    std::string toString();
    std::string toString(JNIEnv* env);
};

jobject toJavaByte(JNIEnv* env, int8_t value);
jobject toJavaShort(JNIEnv* env, int16_t value);
jobject toJavaInteger(JNIEnv* env, int32_t value);
jobject toJavaLong(JNIEnv* env, int64_t value);
jobject toJavaFloat(JNIEnv* env, float value);
jobject toJavaDouble(JNIEnv* env, double value);
jobject toJavaBoolean(JNIEnv* env, bool value);
jobject toJavaCharacter(JNIEnv* env, char16_t value);
const char* fromJavaString(JNIEnv* env, jstring jstr);
jstring toJavaString(JNIEnv* env, const char* str);
jobject call(JNIEnv* env, jobject obj, const char* method, const char* paramsType, ...);
#endif // __BRIDGE_H