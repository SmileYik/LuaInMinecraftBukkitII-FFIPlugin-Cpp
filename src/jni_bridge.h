#ifndef __JNI_BRIDGE_H
#define __JNI_BRIDGE_H

#include <jni.h>
#include <cstdint>
#include <string>
#include <any>
#include <list>
#include <memory>
#include <vector>
#include "bridge.h"

void checkJNIException(JNIEnv* env);

// --- 整数类型转换 ---

jobject toJavaByte(JNIEnv* env, int8_t value);

jobject toJavaShort(JNIEnv* env, int16_t value);

jobject toJavaInteger(JNIEnv* env, int32_t value);

jobject toJavaLong(JNIEnv* env, int64_t value);

// --- 浮点类型转换 ---

jobject toJavaFloat(JNIEnv* env, float value);

jobject toJavaDouble(JNIEnv* env, double value);

// --- 布尔和字符类型转换 ---

jobject toJavaBoolean(JNIEnv* env, bool value);

jobject toJavaCharacter(JNIEnv* env, char16_t value);

jstring toJavaString(JNIEnv* env, const char* str);

std::string fromJavaString(JNIEnv* env, jstring jstr);

jobject toJavaArray(JNIEnv* env, std::list<JObject> objs);

jobject toJavaArray(JNIEnv* env, std::vector<JObject> objs);

jobject toJavaArray(JNIEnv* env, std::list<jobject> objs);

jobject toJavaArray(JNIEnv* env, std::vector<jobject> objs);

jobject toJavaArray(JNIEnv* env, std::list<std::string> objs, std::list<jobject>& localParamRefs);

jobject toJavaArray(JNIEnv* env, std::vector<std::string> objs, std::list<jobject>& localParamRefs);

jobject toJavaArray(JNIEnv* env, std::list<const char *> objs, std::list<jobject>& localParamRefs);

jobject toJavaArray(JNIEnv* env, std::vector<const char *> objs, std::list<jobject>& localParamRefs);

jobject toJavaArray(JNIEnv* env, std::list<int8_t> objs);

jobject toJavaArray(JNIEnv* env, std::vector<int8_t> objs);

jobject toJavaArray(JNIEnv* env, std::list<bool> objs);

jobject toJavaArray(JNIEnv* env, std::vector<bool> objs);

jobject toJavaArray(JNIEnv* env, std::list<char16_t> objs);

jobject toJavaArray(JNIEnv* env, std::vector<char16_t> objs);

jobject toJavaArray(JNIEnv* env, std::list<int16_t> objs);

jobject toJavaArray(JNIEnv* env, std::vector<int16_t> objs);

jobject toJavaArray(JNIEnv* env, std::list<int32_t> objs);

jobject toJavaArray(JNIEnv* env, std::vector<int32_t> objs);

jobject toJavaArray(JNIEnv* env, std::list<int64_t> objs);

jobject toJavaArray(JNIEnv* env, std::vector<int64_t> objs);

jobject toJavaArray(JNIEnv* env, std::list<float> objs);

jobject toJavaArray(JNIEnv* env, std::vector<float> objs);

jobject toJavaArray(JNIEnv* env, std::list<double> objs);

jobject toJavaArray(JNIEnv* env, std::vector<double> objs);

std::string javaObject2String(JNIEnv* env, jobject obj);

bool cppParams2JavaParams(
    JNIEnv* env, 
    std::list<std::any>& params, 
    const size_t paramCount, 
    const size_t base, 
    std::list<jobject>& localParamRefs, 
    jobjectArray& javaParams
);

std::shared_ptr<JObject> javaCallMethod(JNIEnv* env, jobject instance, std::string methodName, std::list<std::any>& params);


#endif // __JNI_BRIDGE_H