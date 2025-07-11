#ifndef __BRIDGE_H
#define __BRIDGE_H

#include <cstdint>
#include <jni.h>
#include <ffi_init.h>
#include <list>
#include <memory>
#include <string>
#include <any>


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
        std::list<std::any> params;
        (params.push_back(std::forward<Args>(args)), ...);
        return call(params);
    }
private:
    std::shared_ptr<JObject> call(std::list<std::any>& params) const;
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
public:
    std::string operator+(std::string str);
    std::string operator+(JObject obj);
};
#endif // __BRIDGE_H