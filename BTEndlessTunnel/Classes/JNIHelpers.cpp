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
#define  LOGD(...)  __android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__)

extern "C" {
    
/*
 * Class:     com_carlospinan_utils_NativeUtils
 * Method:    nativeMono
 * Signature: (Ljava/lang/String;)V
 */
//JNIEXPORT void JNICALL Java_com_carlospinan_utils_NativeUtils_nativeMono
//(JNIEnv *, jclass, jstring);

//JNIEXPORT void JNICALL
//Java_com_carlospinan_utils_NativeUtils_nativeMono(JNIEnv * env,
//                                                  jobject testObj,
//                                                  jstring testStr
//                                                  )

/*
 * Class:     com_carlospinan_utils_NativeUtils
 * Method:    nativeMono
 * Signature: (Ljava/lang/String;Ljava/util/ArrayList;)V
 */
JNIEXPORT void JNICALL Java_com_carlospinan_utils_NativeUtils_nativeMono
(JNIEnv *env, jclass testClass, jstring testStr, jobject testObj)
{
    const char *testMesg = env->GetStringUTFChars(testStr, NULL);
    
    // std::cout doesn't show up on Android
//    std::cout << "JNIHelpers: nativeMono \n";
//    std::cout << "testMesg: " << testMesg << "\n";
    
    LOGE("JNIHelpers: nativeMono");
    
    // convert ArrayList<Achievement> from testObj

    // retrieve the java.util.List interface class
    jclass cList = env->FindClass("java/util/ArrayList");
    
    // retrieve the size and the get method
    jmethodID mSize = env->GetMethodID(cList, "size", "()I");
    jmethodID mGet = env->GetMethodID(cList, "get", "(I)Ljava/lang/Object;");
    
    
    std::vector<BTLootsieAchievement*> lootsieAchievments;
    
    
    if ((mSize != NULL) && (mGet != NULL)) {
        
        // get the size of the list
        jint arraySize = env->CallIntMethod(testObj, mSize);
        //__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "JNIHelpers: nativeMono: Achievements: %d", arraySize);
        LOGD("JNIHelpers: nativeMono: Achievements: %d", arraySize);
        
//        std::ostringstream os;
//        os << "JNIHelpers: nativeMono: Achievements: " << arraySize;
//        std::string mesgStr = os.str();
//        const char *charStr = mesgStr.c_str();
//        jstring jstrBuf = env->NewStringUTF(charStr);
        
        
        //std::vector<std::string> sVector;
        
        jclass cAchievement = env->FindClass("com/lootsie/sdk/model/Achievement");
        
        // walk through and fill the vector
        for(jint i=0; i<arraySize; i++) {
            jobject achievementObj = (jobject) env->CallObjectMethod(testObj, mGet, i);
 
            jfieldID fid = env->GetFieldID(cAchievement, "id", "Ljava/lang/String;");
            jstring jstrId = (jstring) env->GetObjectField(achievementObj, fid);
            const char *strId = env->GetStringUTFChars(jstrId, JNI_FALSE);
            LOGD("JNIHelpers: nativeMono: Achievement[%d] id: %s", i, strId);
            
            jfieldID fname = env->GetFieldID(cAchievement, "name", "Ljava/lang/String;");
            jstring jstrName = (jstring) env->GetObjectField(achievementObj, fname);
            const char *strName = env->GetStringUTFChars(jstrName, JNI_FALSE);
            LOGD("JNIHelpers: nativeMono: Achievement[%d] name: %s", i, strName);
            
            jfieldID fdescription = env->GetFieldID(cAchievement, "description", "Ljava/lang/String;");
            jstring jstrDescription = (jstring) env->GetObjectField(achievementObj, fdescription);
            const char *strDescription = env->GetStringUTFChars(jstrDescription, JNI_FALSE);
            LOGD("JNIHelpers: nativeMono: Achievement[%d] description: %s", i, strDescription);
            
            jfieldID fdate = env->GetFieldID(cAchievement, "date", "Ljava/lang/String;");
            jstring jstrDate = (jstring) env->GetObjectField(achievementObj, fdate);
            const char *strDate = NULL;
            if (jstrDate != NULL) {
                strDate = env->GetStringUTFChars(jstrDate, NULL);
            }
            LOGD("JNIHelpers: nativeMono: Achievement[%d] date: %s", i, strDate);
            
            jfieldID fLP = env->GetFieldID(cAchievement, "lp", "I");
            jint jintLP = (jint) env->GetIntField(achievementObj, fLP);
            int intLP = (int) jintLP;
            LOGD("JNIHelpers: nativeMono: Achievement[%d] lp: %d", i, intLP);
            
//            jstring strObj = (jstring)env->CallObjectMethod(jList, mGet, i);
//            const char * chr = env->GetStringUTFChars(strObj, JNI_FALSE);
//            sVector.insert(sVector.end(), chr);
//            env->ReleaseStringUTFChars(strObj, chr);
            
            BTLootsieAchievement *btLootsieAchievement = new BTLootsieAchievement();
            btLootsieAchievement->id = std::string(strId);
            btLootsieAchievement->name = std::string(strName);
//            btLootsieAchievement->description = std::string(strDescription);
//            btLootsieAchievement->date = std::string(strDate);
            btLootsieAchievement->lp = intLP;

            
//            btLootsieAchievement->id = strId;
//            btLootsieAchievement->name = strName;
//            btLootsieAchievement->description = strDescription;
//            btLootsieAchievement->date = strDate;
//            btLootsieAchievement->lp = intLP;
            
//            //lootsieAchievments.push_back(btLootsieAchievement);
            lootsieAchievments.insert(lootsieAchievments.end(), btLootsieAchievement);
            
        }
        
        
    } else {
        LOGE("JNIHelpers: methods are missing!");
    }
    
    
    

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