#include <jni.h>
#include <string>
#include "frameBuffer.h"

extern "C" JNIEXPORT jstring

JNICALL
Java_com_seifer_lua_MainActivity_stringFromJNI(JNIEnv *env,jobject)
{
    //getFrameBuffer();
    std::string hello = getFrameBuffer();
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_seifer_lua_MainActivity_getBufferFromFrame(JNIEnv *env, jobject instance)
{
    std::string hello = getStringFromOtherFile();
    return env->NewStringUTF(hello.c_str());
}