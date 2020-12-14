#include <jni.h>
#include <stdlib.h>

#include "xposed-detector.h"

static int xposed_stat = NO_XPOSED;

jint getXposedStat(JNIEnv *env __unused, jclass clazz __unused) {
	return xposed_stat;
}

jint JNI_OnLoad(JavaVM *jvm, void *v __unused) {
	JNIEnv *env;
	jclass clazz;

	if ((*jvm)->GetEnv(jvm, (void **) &env, JNI_VERSION_1_6) != JNI_OK) {
		return JNI_ERR;
	}

	get_xposed_status(env, android_get_device_api_level());

	if ((clazz = (*env)->FindClass(env, "io/github/vvb2060/xposeddetector/MainActivity")) == NULL) {
		return JNI_ERR;
	}

	JNINativeMethod methods[] = {{"getXposedStat", "()I", getXposedStat}};

	if ((*env)->RegisterNatives(env, clazz, methods, 1) < 0) {
		return JNI_ERR;
	}

	return JNI_VERSION_1_6;
}
