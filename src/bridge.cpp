#include "bridge.h"
#include "ffi_init.h"
#include "jni.h"
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <memory>

void checkJNIException(JNIEnv* env) {
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear(); 
    }
}

// --- 整数类型转换 ---

jobject toJavaByte(JNIEnv* env, int8_t value) {
    jclass byteClass = env->FindClass("java/lang/Byte");
    if (!byteClass) {
        checkJNIException(env);
        return nullptr;
    }

    jmethodID constructor = env->GetMethodID(byteClass, "<init>", "(B)V");
    if (!constructor) {
        checkJNIException(env);
        env->DeleteLocalRef(byteClass);
        return nullptr;
    }

    jobject byteObj = env->NewObject(byteClass, constructor, value);
    checkJNIException(env);
    env->DeleteLocalRef(byteClass);
    return byteObj;
}

jobject toJavaShort(JNIEnv* env, int16_t value) {
    jclass shortClass = env->FindClass("java/lang/Short");
    if (!shortClass) {
        checkJNIException(env);
        return nullptr;
    }

    jmethodID constructor = env->GetMethodID(shortClass, "<init>", "(S)V");
    if (!constructor) {
        checkJNIException(env);
        env->DeleteLocalRef(shortClass);
        return nullptr;
    }

    jobject shortObj = env->NewObject(shortClass, constructor, value);
    checkJNIException(env);
    env->DeleteLocalRef(shortClass);
    return shortObj;
}

jobject toJavaInteger(JNIEnv* env, int32_t value) {
    jclass integerClass = env->FindClass("java/lang/Integer");
    if (!integerClass) {
        checkJNIException(env);
        return nullptr;
    }

    jmethodID constructor = env->GetMethodID(integerClass, "<init>", "(I)V");
    if (!constructor) {
        checkJNIException(env);
        env->DeleteLocalRef(integerClass);
        return nullptr;
    }

    jobject integerObj = env->NewObject(integerClass, constructor, value);
    checkJNIException(env);
    env->DeleteLocalRef(integerClass);
    return integerObj;
}

jobject toJavaLong(JNIEnv* env, int64_t value) {
    jclass longClass = env->FindClass("java/lang/Long");
    if (!longClass) {
        checkJNIException(env);
        return nullptr;
    }

    jmethodID constructor = env->GetMethodID(longClass, "<init>", "(J)V");
    if (!constructor) {
        checkJNIException(env);
        env->DeleteLocalRef(longClass);
        return nullptr;
    }

    jobject longObj = env->NewObject(longClass, constructor, value);
    checkJNIException(env);
    env->DeleteLocalRef(longClass);
    return longObj;
}

// --- 浮点类型转换 ---

jobject toJavaFloat(JNIEnv* env, float value) {
    jclass floatClass = env->FindClass("java/lang/Float");
    if (!floatClass) {
        checkJNIException(env);
        return nullptr;
    }

    jmethodID constructor = env->GetMethodID(floatClass, "<init>", "(F)V");
    if (!constructor) {
        checkJNIException(env);
        env->DeleteLocalRef(floatClass);
        return nullptr;
    }

    jobject floatObj = env->NewObject(floatClass, constructor, value);
    checkJNIException(env);
    env->DeleteLocalRef(floatClass);
    return floatObj;
}

jobject toJavaDouble(JNIEnv* env, double value) {
    jclass doubleClass = env->FindClass("java/lang/Double");
    if (!doubleClass) {
        checkJNIException(env);
        return nullptr;
    }

    jmethodID constructor = env->GetMethodID(doubleClass, "<init>", "(D)V");
    if (!constructor) {
        checkJNIException(env);
        env->DeleteLocalRef(doubleClass);
        return nullptr;
    }

    jobject doubleObj = env->NewObject(doubleClass, constructor, value);
    checkJNIException(env);
    env->DeleteLocalRef(doubleClass);
    return doubleObj;
}

// --- 布尔和字符类型转换 ---

jobject toJavaBoolean(JNIEnv* env, bool value) {
    jclass booleanClass = env->FindClass("java/lang/Boolean");
    if (!booleanClass) {
        checkJNIException(env);
        return nullptr;
    }

    jmethodID constructor = env->GetMethodID(booleanClass, "<init>", "(Z)V");
    if (!constructor) {
        checkJNIException(env);
        env->DeleteLocalRef(booleanClass);
        return nullptr;
    }

    jobject booleanObj = env->NewObject(booleanClass, constructor, value);
    checkJNIException(env);
    env->DeleteLocalRef(booleanClass);
    return booleanObj;
}

jobject toJavaCharacter(JNIEnv* env, char16_t value) {
    jclass characterClass = env->FindClass("java/lang/Character");
    if (!characterClass) {
        checkJNIException(env);
        return nullptr;
    }

    jmethodID constructor = env->GetMethodID(characterClass, "<init>", "(C)V");
    if (!constructor) {
        checkJNIException(env);
        env->DeleteLocalRef(characterClass);
        return nullptr;
    }

    jobject characterObj = env->NewObject(characterClass, constructor, value);
    checkJNIException(env);
    env->DeleteLocalRef(characterClass);
    return characterObj;
}

jstring toJavaString(JNIEnv* env, const char* str) {
    jstring javaString = env->NewStringUTF(str);
    checkJNIException(env);
    return javaString;
}

const char* fromJavaString(JNIEnv* env, jstring jstr) {
    if (!jstr) {
        return nullptr;
    }

    const char* utf_chars = env->GetStringUTFChars(jstr, nullptr);
    if (!utf_chars) {
        checkJNIException(env);
        return "";
    }

    env->ReleaseStringUTFChars(jstr, utf_chars);
    checkJNIException(env);

    return utf_chars;
}

jobject call(JNIEnv* env, jobject obj, const char* method, const char* paramsType, ...) {
    jclass objectClass = env->FindClass("java/lang/Object");
    if (!objectClass) {
        checkJNIException(env);
        return nullptr;
    }

    jclass nativeBridgeClass = env->FindClass("org/eu/smileyik/luaInMinecraftBukkitII/reflect/ReflectUtil");
    if (!nativeBridgeClass) {
        checkJNIException(env);
        env->DeleteLocalRef(objectClass);
        return nullptr;
    }

    jmethodID javaCallMethodID = env->GetStaticMethodID(
        nativeBridgeClass, "callMethod", "(Ljava/lang/Object;Ljava/lang/String;[Ljava/lang/Object;)Ljava/lang/Object;");
    if (!javaCallMethodID) {
        checkJNIException(env);
        env->DeleteLocalRef(objectClass);
        env->DeleteLocalRef(nativeBridgeClass);
        return nullptr;
    }
    
    size_t paramCount = paramsType ? std::strlen(paramsType) : 0;

    jobjectArray javaParamsArray = env->NewObjectArray(paramCount, objectClass, nullptr);
    if (!javaParamsArray) {
        checkJNIException(env);
        env->DeleteLocalRef(objectClass);
        env->DeleteLocalRef(nativeBridgeClass);
        return nullptr;
    }

    va_list args;
    va_start(args, paramsType);

    for (size_t i = 0; i < paramCount; ++i) {
        char typeChar = paramsType[i];
        jobject currentJavaParam = nullptr;

        switch (typeChar) {
            case 'b': // byte
                currentJavaParam = toJavaByte(env, va_arg(args, int)); // byte promotes to int in va_arg
                break;
            case 's': // short
                currentJavaParam = toJavaShort(env, va_arg(args, int)); // short promotes to int in va_arg
                break;
            case 'i': // int
                currentJavaParam = toJavaInteger(env, va_arg(args, int));
                break;
            case 'j': // long
                currentJavaParam = toJavaLong(env, va_arg(args, int64_t)); // long is int64_t
                break;
            case 'f': // float
                currentJavaParam = toJavaFloat(env, va_arg(args, double)); // float promotes to double in va_arg
                break;
            case 'd': // double
                currentJavaParam = toJavaDouble(env, va_arg(args, double));
                break;
            case 'z': // boolean
                currentJavaParam = toJavaBoolean(env, va_arg(args, int)); // bool promotes to int in va_arg
                break;
            case 'c': // char
                currentJavaParam = toJavaCharacter(env, va_arg(args, int)); // char promotes to int in va_arg
                break;
            case 't': // string (const char*)
                currentJavaParam = toJavaString(env, va_arg(args, const char*));
                break;
            case 'o':
                currentJavaParam = va_arg(args, jobject);
                break;
            default:
                env->ThrowNew(env->FindClass("java/lang/IllegalArgumentException"),
                              ("Unknown parameter type: " + std::string(1, typeChar)).c_str());
                va_end(args);
                env->DeleteLocalRef(objectClass);
                env->DeleteLocalRef(nativeBridgeClass);
                env->DeleteLocalRef(javaParamsArray);
                return nullptr;
        }

        if (!currentJavaParam && env->ExceptionCheck()) {
            va_end(args);
            env->DeleteLocalRef(objectClass);
            env->DeleteLocalRef(nativeBridgeClass);
            env->DeleteLocalRef(javaParamsArray);
            return nullptr;
        }
        
        env->SetObjectArrayElement(javaParamsArray, i, currentJavaParam);
        checkJNIException(env); 
        
        if (currentJavaParam) {
            env->DeleteLocalRef(currentJavaParam);
        }
    }

    va_end(args);

    jobject result = env->CallStaticObjectMethod(nativeBridgeClass, javaCallMethodID,
                                                  obj, toJavaString(env, method), javaParamsArray);
    checkJNIException(env);

    env->DeleteLocalRef(objectClass);
    env->DeleteLocalRef(nativeBridgeClass);
    env->DeleteLocalRef(javaParamsArray);

    return result;
}

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
    JNIEnv* env = getJNIEnv();
    std::string result = toString(env);
    destroyJNIEnv();
    return nullptr == env ? "" : result;
}

std::string JObject::toString(JNIEnv* env) {
    jclass objectClass = env->FindClass("java/lang/Object");
    if (!objectClass) {
        checkJNIException(env);
        return "";
    }
    jmethodID methodId = env->GetMethodID(objectClass, "toString", "()Ljava/lang/String;");
    jstring ret = (jstring) env->CallObjectMethod(instance, methodId);
    const char* str = fromJavaString(env, ret);
    std::string retStr = std::string(str);
    return retStr;
}

bool cParams2JavaParams(JNIEnv* env, const std::vector<std::any>& params, const size_t paramCount, const size_t base, std::vector<jobject>& localParamRefs, jobjectArray& javaParams) {
    jclass objectClass = env->FindClass("java/lang/Object");
    if (!objectClass) {
        checkJNIException(env);
        return false;
    }
    localParamRefs.push_back(objectClass);

    size_t idx = base;
    javaParams = env->NewObjectArray(paramCount - idx, objectClass, nullptr);
    localParamRefs.push_back(javaParams);
    while (idx < paramCount) {
        std::any param = params[idx];
        jobject javaParam = nullptr;
        
        try {
            javaParam = std::any_cast<jobject>(param);
        } catch (const std::bad_any_cast& e) {
            if (param.has_value()) {
                printf("--- '%s' '%d'---\n", param.type().name(), 1);
                fflush(stdout);
                if (param.type() == typeid(int8_t)) {
                    javaParam = toJavaByte(env, std::any_cast<int8_t>(param));
                } else if (param.type() == typeid(int16_t)) {
                    javaParam = toJavaShort(env, std::any_cast<int16_t>(param));
                } else if (param.type() == typeid(int32_t)) {
                    javaParam = toJavaInteger(env, std::any_cast<int32_t>(param));
                } else if (param.type() == typeid(int64_t)) {
                    javaParam = toJavaLong(env, std::any_cast<int64_t>(param));
                } else if (param.type() == typeid(bool)) {
                    javaParam = toJavaBoolean(env, std::any_cast<bool>(param));
                } else if (param.type() == typeid(char16_t)) {
                    javaParam = toJavaCharacter(env, std::any_cast<char16_t>(param));
                } else if (param.type() == typeid(float)) {
                    javaParam = toJavaFloat(env, std::any_cast<float>(param));
                } else if (param.type() == typeid(double)) {
                    javaParam = toJavaDouble(env, std::any_cast<double>(param));
                } else if (param.type() == typeid(std::string)) {
                    javaParam = toJavaString(env, std::any_cast<std::string>(param).c_str());
                } else if (param.type() == typeid(const char *)) {
                    javaParam = toJavaString(env, std::any_cast<const char *>(param));
                }

                if (nullptr != javaParam) {
                    localParamRefs.push_back(javaParam);
                }
            }
        }
        env->SetObjectArrayElement(javaParams, idx - base, javaParam);
        checkJNIException(env); 
        idx += 1;
    }
    return true;
}

std::shared_ptr<JObject> JObjectProxy::call(const std::vector<std::any>& params) const {
    JNIEnv* env = nullptr;
    size_t paramCount = params.size();
    size_t idx = 0;

    if (paramCount > 0) {
        std::any first = params[0];
        if (first.type() == typeid(JNIEnv*)) {
            env = std::any_cast<JNIEnv*>(first);
            idx = 1;
        }
    }
    if (nullptr == env) {
        env = getJNIEnv();
    }
    if (nullptr == env) {
        return nullptr;
    }

    jclass nativeBridgeClass = env->FindClass("org/eu/smileyik/luaInMinecraftBukkitII/reflect/ReflectUtil");
    if (!nativeBridgeClass) {
        checkJNIException(env);
        return nullptr;
    }
    jmethodID javaCallMethodID = env->GetStaticMethodID(
        nativeBridgeClass, "callMethod", "(Ljava/lang/Object;Ljava/lang/String;[Ljava/lang/Object;)Ljava/lang/Object;");
    if (!javaCallMethodID) {
        checkJNIException(env);
        env->DeleteLocalRef(nativeBridgeClass);
        return nullptr;
    }
    jobjectArray javaParams;
    std::vector<jobject> localParamRefs;
    localParamRefs.push_back(nativeBridgeClass);

    if (!cParams2JavaParams(env, params, paramCount, idx, localParamRefs, javaParams)) {
        for (auto begin = localParamRefs.begin(),
                    end = localParamRefs.end(); begin != end; begin += 1) {
            env->DeleteLocalRef(*begin);
        }
    }
    

    jobject result = env->CallStaticObjectMethod(nativeBridgeClass, javaCallMethodID,
                                                instance, toJavaString(env, name.c_str()), javaParams);
    checkJNIException(env);

    for (auto begin = localParamRefs.begin(),
                end = localParamRefs.end(); begin != end; begin += 1) {
        env->DeleteLocalRef(*begin);
    }
    destroyJNIEnv();
    return nullptr;
}