#include <jni.h>
#include <list>
#include <string>
#include <any>
#include "config.h"

#ifndef __BRIDGE_H
#define __BRIDGE_H

struct JObject;
struct JObjectProxy;

enum JNI_BRIDGE_API JObjectProxyType {
    Field,
    Method,
    Constructor
};

class JNI_BRIDGE_API JObject {
public:
    const jobject instance;
public:
    JObject(jobject object);
public:
    JObjectProxy get(const std::string& name);
    std::string toString();
    std::string toString(JNIEnv* env);
public:
    std::string operator+(std::string str);
    std::string operator+(JObject obj);
};

class JNI_BRIDGE_API JObjectProxy {
private:
    const jobject instance;
    const JObjectProxyType proxyType;
    std::string name;
public:
    JObjectProxy(jobject obj, JObjectProxyType pxyType, const std::string& calledName);

    template<typename... Args>
    JObject operator()(Args&&... args) const {
        std::list<std::any> params;
        (params.push_back(std::forward<Args>(args)), ...);
        return JObject(call(params));
    }
private:
    JObject call(std::list<std::any>& params) const;
};

#endif // __BRIDGE_H