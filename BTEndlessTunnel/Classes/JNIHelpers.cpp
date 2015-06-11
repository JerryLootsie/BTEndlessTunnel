//
//  JniHelpers.cpp
#include "JniHelpers.h"


#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

//void JniHelpers::jniCommonVoidCall(const char* methodName, const char* classPath, unsigned int level, unsigned long score, unsigned int obstacles)
//{
//#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    cocos2d::JniMethodInfo minfo;
//    
//    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "(IJI)V");
//    
//    if (isHave)
//	{
//        jlong scoreArg1    = score;
//        
//        minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID, level, scoreArg1, obstacles);
//        
//    }
//#endif
//}

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//extern "C" JNIEXPORT void JNICALL
//Java_com_carlospinan_utils_NativeUtils_nativeMono(JNIEnv * env,
//                                                   jclass,
//                                                   jstring testStr,
//                                                   jobject testObj
//                                                   )
#include <jni.h>
#include <android/log.h>

#include "HomeLayer.h"

#define  LOG_TAG    "JNIHelpers"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

extern "C" {
    
/*
 * Class:     com_carlospinan_utils_NativeUtils
 * Method:    nativeMono
 * Signature: (Ljava/lang/String;)V
 */
//JNIEXPORT void JNICALL Java_com_carlospinan_utils_NativeUtils_nativeMono
//(JNIEnv *, jclass, jstring);

JNIEXPORT void JNICALL
Java_com_carlospinan_utils_NativeUtils_nativeMono(JNIEnv * env,
                                                  jobject testObj,
                                                  jstring testStr
                                                  )
{
    const char *testMesg = env->GetStringUTFChars(testStr, NULL);
    
    // std::cout doesn't show up on Android
//    std::cout << "JNIHelpers: nativeMono \n";
//    std::cout << "testMesg: " << testMesg << "\n";
    
    LOGE("JNIHelpers: nativeMono");
    
    std::vector<BTLootsieAchievement*> lootsieAchievments;
    HomeLayer::sharedInstance()->_showPopUpAchievementsLayer(lootsieAchievments);
    
}
    
} // extern "C"
#endif

unsigned int JniHelpers::jniCommonIntCall(const char* methodName, const char* classPath, const char* arg0)
{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo minfo;

    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "(Ljava/lang/String;)I");
    
    if (isHave) 
	{
		jstring stringArg0 = minfo.env->NewStringUTF(arg0);

        jint ret = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID, stringArg0);

		minfo.env->DeleteLocalRef(stringArg0);

		return (unsigned int)ret;
    }
#endif
	return 0;
}

unsigned int JniHelpers::jniCommonIntCall(const char* methodName, const char* classPath, const char* arg0, bool looping) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo minfo;

    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "(Ljava/lang/String;Z)I");

    if (isHave) 
	{
		jstring stringArg0 = minfo.env->NewStringUTF(arg0);

        jint ret = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID, stringArg0, looping);

		minfo.env->DeleteLocalRef(stringArg0);

		return (unsigned int)ret;
    }
#endif

	return 0;
}

void JniHelpers::jniCommonVoidCall(const char* methodName, const char* classPath, const char* arg0) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo minfo;

    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo, classPath, methodName, "(Ljava/lang/String;)V");

    if (isHave) 
	{
		jstring stringArg0 = minfo.env->NewStringUTF(arg0);

        //minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID, stringArg0);
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, stringArg0);

		minfo.env->DeleteLocalRef(stringArg0);
    }
#endif
}

void JniHelpers::jniCommonVoidCall(const char* methodName, const char* classPath, const char* arg0, bool looping) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo minfo;

    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "(Ljava/lang/String;Z)V");

    if (isHave) 
	{
		jstring stringArg0 = minfo.env->NewStringUTF(arg0);

        minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID, stringArg0, looping);

		minfo.env->DeleteLocalRef(stringArg0);

    }
#endif

}

void JniHelpers::jniCommonVoidCall(const char* methodName, const char* classPath, const char* arg0, long score) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo minfo;

    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "(Ljava/lang/String;J)V");

    if (isHave) 
	{
		jstring stringArg0 = minfo.env->NewStringUTF(arg0);
        jlong scoreArg1    = score;

        //minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID, stringArg0, scoreArg1);
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, stringArg0, scoreArg1);

		minfo.env->DeleteLocalRef(stringArg0);

    }
#endif
}

void JniHelpers::jniCommonVoidCall(const char* methodName, const char* classPath, const char* arg0, int numSteps) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo minfo;

    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "(Ljava/lang/String;I)V");

    if (isHave) 
	{
		jstring stringArg0 = minfo.env->NewStringUTF(arg0);

        //minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID, stringArg0, numSteps);
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, stringArg0, numSteps);

		minfo.env->DeleteLocalRef(stringArg0);

    }
#endif
}

void JniHelpers::jniCommonVoidCall(const char* methodName, const char* classPath) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo minfo;
    
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "()V");
    
    if (isHave) 
	{
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
#endif
}

void JniHelpers::jniCommonVoidCall(const char* methodName, const char* classPath, unsigned int arg0) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo minfo;

    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "(I)V");

    if (isHave) 
	{
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, arg0);
    }
#endif
}

float JniHelpers::jniCommonFloatCall(const char* methodName, const char* classPath) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo minfo;
	
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "()F");
    
    if (isHave) 
	{
        jfloat ret = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID);
		return (float)ret;
    }
#endif
	
	return 0.0;
}

void JniHelpers::jniCommonVoidCall(const char* methodName, const char* classPath, float arg0){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo minfo;
	
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo, classPath, methodName, "(F)V");
    
    if (isHave) 
	{
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, arg0);
    }
#endif
}

bool JniHelpers::jniCommonBoolCall(const char* methodName, const char* classPath) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo minfo;

    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "()Z");

    if (isHave) 
	{
    	jboolean ret = minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID);
		return (bool)ret;
    }
#endif
    return false;
}

bool JniHelpers::jniCommonBoolCall(const char* methodName, const char* classPath, unsigned int arg0) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo minfo;
    
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo,classPath,methodName, "(I)Z");
    
    if (isHave) 
	{
    	jboolean ret = minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID, arg0);
		return (bool)ret;
    }
#endif
    return false;
}