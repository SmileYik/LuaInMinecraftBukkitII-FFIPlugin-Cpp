#include "bridge.h"
#include "jni.h"
#include <cstdarg>

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