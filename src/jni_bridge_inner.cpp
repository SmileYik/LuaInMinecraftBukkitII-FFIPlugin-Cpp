#include <jni.h>
#include "jni_bridge_data.h"
#include "jni_bridge_inner.h"
/*
 * Class:     org_eu_smileyik_luaInMinecraftBukkitII_jniBridge_JNIBridge
 * Method:    initJNIBridge
 * Signature: ()V
 */
JNIEXPORT jint JNICALL Java_org_eu_smileyik_luaInMinecraftBukkitII_jniBridge_JNIBridge_init(JNIEnv* env, jclass obj) {
    printf("initJNIENV\n");
    fflush(stdout);
    initJNIEnv(env);
    return 1;
}