#ifndef __BRIDGE_H
#define __BRIDGE_H

#include <jni.h>
#include <cstdint> 
#include <string>

/*
b: byte
s: short
i: int
j: long
f: float
d: double
z: boolean
c: char
t: string
o: jobject
*/

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