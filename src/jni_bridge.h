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

// --- JNIEnv ---

extern
FFI_BRIDGE_API
JNIEnv* getCurrentJNIEnv();

extern
FFI_BRIDGE_API
void destroyJNIEnv();

void checkJNIException(JNIEnv* env);

// --- 整数类型转换 ---

FFI_BRIDGE_API
jobject toJavaByte(JNIEnv* env, int8_t value);

FFI_BRIDGE_API
jobject toJavaShort(JNIEnv* env, int16_t value);

FFI_BRIDGE_API
jobject toJavaInteger(JNIEnv* env, int32_t value);

FFI_BRIDGE_API
jobject toJavaLong(JNIEnv* env, int64_t value);

// --- 浮点类型转换 ---

FFI_BRIDGE_API
jobject toJavaFloat(JNIEnv* env, float value);

FFI_BRIDGE_API
jobject toJavaDouble(JNIEnv* env, double value);

// --- 布尔和字符类型转换 ---

FFI_BRIDGE_API
jobject toJavaBoolean(JNIEnv* env, bool value);

FFI_BRIDGE_API
jobject toJavaCharacter(JNIEnv* env, char16_t value);

FFI_BRIDGE_API
jstring toJavaString(JNIEnv* env, const char* str);

FFI_BRIDGE_API
std::string fromJavaString(JNIEnv* env, jstring jstr);

// --- 数组类型转换 ---

FFI_BRIDGE_API
jobject wrapperObjectListToJavaArray(JNIEnv* env, std::list<JObject> objs);

FFI_BRIDGE_API
jobject wrapperObjectVectorToJavaArray(JNIEnv* env, std::vector<JObject> objs);

FFI_BRIDGE_API
jobject jobjectListToJavaArray(JNIEnv* env, std::list<jobject> objs);

FFI_BRIDGE_API
jobject jobjectVectorToJavaArray(JNIEnv* env, std::vector<jobject> objs);

FFI_BRIDGE_API
jobject stringListToJavaArray(JNIEnv* env, std::list<std::string> objs, std::list<jobject>& localParamRefs);

FFI_BRIDGE_API
jobject stringVectorToJavaArray(JNIEnv* env, std::vector<std::string> objs, std::list<jobject>& localParamRefs);

FFI_BRIDGE_API
jobject cstringListToJavaArray(JNIEnv* env, std::list<const char *> objs, std::list<jobject>& localParamRefs);

FFI_BRIDGE_API
jobject cstringVectorToJavaArray(JNIEnv* env, std::vector<const char *> objs, std::list<jobject>& localParamRefs);

FFI_BRIDGE_API
jobject int8ListToJavaArray(JNIEnv* env, std::list<int8_t> objs);

FFI_BRIDGE_API
jobject int8VectorToJavaArray(JNIEnv* env, std::vector<int8_t> objs);

FFI_BRIDGE_API
jobject boolListToJavaArray(JNIEnv* env, std::list<bool> objs);

FFI_BRIDGE_API
jobject boolVectorToJavaArray(JNIEnv* env, std::vector<bool> objs);

FFI_BRIDGE_API
jobject charListToJavaArray(JNIEnv* env, std::list<char16_t> objs);

FFI_BRIDGE_API
jobject charVectorToJavaArray(JNIEnv* env, std::vector<char16_t> objs);

FFI_BRIDGE_API
jobject int16ListToJavaArray(JNIEnv* env, std::list<int16_t> objs);

FFI_BRIDGE_API
jobject int16VectorToJavaArray(JNIEnv* env, std::vector<int16_t> objs);

FFI_BRIDGE_API
jobject int32ListToJavaArray(JNIEnv* env, std::list<int32_t> objs);

FFI_BRIDGE_API
jobject int32VectorToJavaArray(JNIEnv* env, std::vector<int32_t> objs);

FFI_BRIDGE_API
jobject int64ListToJavaArray(JNIEnv* env, std::list<int64_t> objs);

FFI_BRIDGE_API
jobject int64VectorToJavaArray(JNIEnv* env, std::vector<int64_t> objs);

FFI_BRIDGE_API
jobject floatListToJavaArray(JNIEnv* env, std::list<float> objs);

FFI_BRIDGE_API
jobject floatVectorToJavaArray(JNIEnv* env, std::vector<float> objs);

FFI_BRIDGE_API
jobject doubleListToJavaArray(JNIEnv* env, std::list<double> objs);

FFI_BRIDGE_API
jobject doubleVectorToJavaArray(JNIEnv* env, std::vector<double> objs);

FFI_BRIDGE_API
std::string javaObject2String(JNIEnv* env, jobject obj);

FFI_BRIDGE_API
bool cppParams2JavaParams(
    JNIEnv* env, 
    std::list<std::any>& params, 
    const size_t paramCount, 
    const size_t base, 
    std::list<jobject>& localParamRefs, 
    jobjectArray& javaParams
);

FFI_BRIDGE_API
jobject javaCallMethod(JNIEnv* env, jobject instance, std::string methodName, std::list<std::any>& params);


#endif // __JNI_BRIDGE_H