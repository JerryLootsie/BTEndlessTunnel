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
#include "GameLayer.h"

#define  LOG_TAG    "JNIHelpers"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__)
#define  DEBUGLOG(...)  if (debugLevel > 0) __android_log_print(ANDROID_LOG_VERBOSE,LOG_TAG,__VA_ARGS__)

extern "C" {
  
/*
 * Class:     com_carlospinan_utils_NativeUtils
 * Method:    nativeAchievementReachedSuccess
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_carlospinan_utils_NativeUtils_nativeAchievementReachedSuccess
(JNIEnv *env, jclass testClass, jstring mesgStr) {
        
    // JNI_TRUE -> copy is made
    jboolean isCopy;
    const char *testMesg = env->GetStringUTFChars(mesgStr, &isCopy);
    
    LOGE("JNIHelpers: nativeAchievementReachedSuccess: %s", testMesg);
    
//    if (isCopy == JNI_TRUE) {
//        env->ReleaseStringUTFChars(mesgStr, testMesg);
//    }
    
}
    
    
/*
 * Class:     com_carlospinan_utils_NativeUtils
 * Method:    nativeAchievementReachedFailed
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_carlospinan_utils_NativeUtils_nativeAchievementReachedFailed
(JNIEnv *env, jclass testClass, jstring mesgStr) {
    
    // JNI_TRUE -> copy is made
    jboolean isCopy;
    const char *testMesg = env->GetStringUTFChars(mesgStr, &isCopy);
    
    LOGE("JNIHelpers: nativeAchievementReachedFailed: %s", testMesg);
    
}
    
/*
 * Class:     com_carlospinan_utils_NativeUtils
 * Method:    nativeAchievementReachedNotificationData
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_carlospinan_utils_NativeUtils_nativeAchievementReachedNotificationData
(JNIEnv *env, jclass testClass, jstring mesgStr) {
    
    // JNI_TRUE -> copy is made
    jboolean isCopy;
    const char *testMesg = env->GetStringUTFChars(mesgStr, &isCopy);
    
    LOGE("JNIHelpers: nativeAchievementReachedNotificationData: %s", testMesg);
    
    std::string jsonStr(testMesg);
    if (GameLayer::sharedInstance() != NULL) {
        GameLayer::sharedInstance()->showInAppNotification((char *)jsonStr.c_str());
    } else {
        LOGE("JNIHelpers: nativeAchievementReachedNotificationData: can't access GameLayer::sharedInstance!!!!");
    }
    
}
    
    
    
/*
 * Class:     com_carlospinan_utils_NativeUtils
 * Method:    nativeAchievementReachedIANClicked
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_carlospinan_utils_NativeUtils_nativeAchievementReachedIANClicked
(JNIEnv *env, jclass testClass, jstring mesgStr) {
    
    // JNI_TRUE -> copy is made
    jboolean isCopy;
    const char *testMesg = env->GetStringUTFChars(mesgStr, &isCopy);
    
    LOGE("JNIHelpers: nativeAchievementReachedIANClicked: %s", testMesg);

    //GameLayer::sharedInstance()->pauseGame();
    GameLayer::sharedInstance()->pauseGameAndShowRewards();
    
}
    
    
    
/*
 * Class:     com_carlospinan_utils_NativeUtils
 * Method:    nativeRedeemRewardResponse
 * Signature: (ZLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_carlospinan_utils_NativeUtils_nativeRedeemRewardResponse
(JNIEnv *env, jclass testClass, jboolean resultBool, jstring mesgStr)
{
    
    const char *testMesg = env->GetStringUTFChars(mesgStr, NULL);
    
    LOGE("JNIHelpers: nativeRedeemRewardResponse: %s", testMesg);
    // on success:
    // JNIHelpers: nativeRedeemRewardResponse: {"total_lp": 822, "reward_redemption_id": "25881", "lp": -28}
    
    bool resultSuccess = (bool)(resultBool == JNI_TRUE);
    if (resultSuccess) {
        cocos2d::CCMessageBox("Reward Redeemed Successfully", "Redeem Reward Success");
    } else {
        cocos2d::CCMessageBox(testMesg, "Redeem Reward Failure");
    }
    
}

    
/*
 * Class:     com_carlospinan_utils_NativeUtils
 * Method:    nativeGetRewards
 * Signature: (Ljava/lang/String;Ljava/util/ArrayList;)V
 */
JNIEXPORT void JNICALL Java_com_carlospinan_utils_NativeUtils_nativeGetRewards
(JNIEnv *env, jclass testClass, jstring testStr, jobject testObj)
{
    const char *testMesg = env->GetStringUTFChars(testStr, NULL);
    
    LOGE("JNIHelpers: nativeGetRewards: %s", testMesg);

    // retrieve the java.util.List interface class
    jclass cList = env->FindClass("java/util/ArrayList");
    
    // retrieve the size and the get method
    jmethodID mSize = env->GetMethodID(cList, "size", "()I");
    jmethodID mGet = env->GetMethodID(cList, "get", "(I)Ljava/lang/Object;");
 
    std::vector<BTLootsieReward*> lootsieRewards;
    
    int debugLevel = 1;
    
    // do methods exist on cList class?
    if ((testObj != NULL) && (mSize != NULL) && (mGet != NULL)) {

        // get the size of the list
        jint arraySize = env->CallIntMethod(testObj, mSize);
        LOGD("JNIHelpers: nativeGetRewards: Rewards: %d", arraySize);
        
        jclass cReward = env->FindClass("com/lootsie/sdk/model/Reward");
        
        // walk through and fill the vector
        for(jint i=0; i<arraySize; i++) {
            // GetStringUTFChars vs NewStringUTF?
            // To get a C-string (char*) from JNI string (jstring), invoke method const char* GetStringUTFChars(JNIEnv*, jstring, jboolean*).
            // To get a JNI string (jstring) from a C-string (char*), invoke method jstring NewStringUTF(JNIEnv*, char*).
            
            BTLootsieReward *btLootsieReward = new BTLootsieReward();
            
            jobject rewardObj = (jobject) env->CallObjectMethod(testObj, mGet, i);
            
            jfieldID fid = env->GetFieldID(cReward, "id", "Ljava/lang/String;");
            jstring jstrId = (jstring) env->GetObjectField(rewardObj, fid);
            //const char *strId = env->GetStringUTFChars(jstrId, JNI_FALSE);
            const char *strId = env->GetStringUTFChars(jstrId, NULL);
            DEBUGLOG("JNIHelpers: nativeGetRewards: Reward[%d] id: %s", i, strId);
            
            jfieldID fname = env->GetFieldID(cReward, "name", "Ljava/lang/String;");
            jstring jstrName = (jstring) env->GetObjectField(rewardObj, fname);
            //const char *strName = env->GetStringUTFChars(jstrName, JNI_FALSE);
            const char *strName = env->GetStringUTFChars(jstrName, NULL);
            DEBUGLOG("JNIHelpers: nativeGetRewards: Reward[%d] name: %s", i, strName);
            
            jfieldID fTextToShare = env->GetFieldID(cReward, "textToShare", "Ljava/lang/String;");
            jstring jstrTextToShare = (jstring) env->GetObjectField(rewardObj, fTextToShare);
            //const char *strTextToShare = env->GetStringUTFChars(jstrTextToShare, JNI_FALSE);
            const char *strTextToShare = env->GetStringUTFChars(jstrTextToShare, NULL);
            DEBUGLOG("JNIHelpers: nativeGetRewards: Reward[%d] textToShare: %s", i, strTextToShare);
            
            jfieldID ftos_text = env->GetFieldID(cReward, "tos_text", "Ljava/lang/String;");
            jstring jstr_tos_text = (jstring) env->GetObjectField(rewardObj, ftos_text);
            //const char *str_tos_text = env->GetStringUTFChars(jstr_tos_text, JNI_FALSE);
            const char *str_tos_text = env->GetStringUTFChars(jstr_tos_text, NULL);
            DEBUGLOG("JNIHelpers: nativeGetRewards: Reward[%d] tos_text: %s", i, str_tos_text);
            
            jfieldID fdescription = env->GetFieldID(cReward, "description", "Ljava/lang/String;");
            jstring jstrDescription = (jstring) env->GetObjectField(rewardObj, fdescription);
            //const char *strDescription = env->GetStringUTFChars(jstrDescription, JNI_FALSE);
            const char *strDescription = env->GetStringUTFChars(jstrDescription, NULL);
            DEBUGLOG("JNIHelpers: nativeGetRewards: Reward[%d] description: %s", i, strDescription);
            
            jfieldID fLP = env->GetFieldID(cReward, "lp", "I");
            jint jintLP = (jint) env->GetIntField(rewardObj, fLP);
            int intLP = (int) jintLP;
            DEBUGLOG("JNIHelpers: nativeGetRewards: Reward[%d] lp: %d", i, intLP);
      
            // cast a char* to a string:
//            btLootsieReward->reward_id = std::string(strId);
//            btLootsieReward->name = std::string(strName);
//            btLootsieReward->text_to_share = std::string(strTextToShare);
//            btLootsieReward->tos_text = std::string(str_tos_text);
//            btLootsieReward->reward_description = std::string(strDescription);

            // create a new string object for each field - to avoid memory issue on JVM JNI on Android 4.0 device
            std::string stdStrId(strId);
            btLootsieReward->reward_id = stdStrId;
            
            std::string stdStrName(strName);
            btLootsieReward->name = stdStrName;
            
            std::string stdStrTextToShare(strTextToShare);
            btLootsieReward->text_to_share = stdStrTextToShare;
            
            std::string stdStr_tos_text(str_tos_text);
            btLootsieReward->tos_text = stdStr_tos_text;
            
            std::string stdStrDescription(strDescription);
            btLootsieReward->reward_description = stdStrDescription;

            btLootsieReward->lp = intLP;
            
            

            
            // Icon class in icon field of cReward
            jclass cIcon = env->FindClass("com/lootsie/sdk/model/Icon");
            if (cIcon == NULL) {
                DEBUGLOG("JNIHelpers: nativeGetRewards: Icon class not found!");
            } else {
                //jfieldID fIcon = env->GetFieldID(cReward, "icon", "com/lootsie/sdk/model/Icon");
                jfieldID fIcon = env->GetFieldID(cReward, "icon", "Lcom/lootsie/sdk/model/Icon;");
                if (fIcon == NULL) {
                    DEBUGLOG("JNIHelpers: nativeGetRewards: Icon field not found!");
                } else {
                    jobject iconObj = (jobject) env->GetObjectField(rewardObj, fIcon);
                    if (iconObj == NULL) {
                        DEBUGLOG("JNIHelpers: nativeGetRewards: Icon ObjectField not found!");
                    } else {
                        DEBUGLOG("JNIHelpers: nativeGetRewards: iconObj");
                        
                        jfieldID fS = env->GetFieldID(cIcon, "S", "Ljava/lang/String;");
                        jstring jstrS = (jstring) env->GetObjectField(iconObj, fS);
                        //const char *strS = env->GetStringUTFChars(jstrS, JNI_FALSE);
                        const char *strS = env->GetStringUTFChars(jstrS, NULL);
                        DEBUGLOG("JNIHelpers: nativeGetRewards: Reward[%d] icon: S: %s", i, strS);
                        
                        jfieldID fM = env->GetFieldID(cIcon, "M", "Ljava/lang/String;");
                        jstring jstrM = (jstring) env->GetObjectField(iconObj, fM);
                        //const char *strM = env->GetStringUTFChars(jstrM, JNI_FALSE);
                        const char *strM = env->GetStringUTFChars(jstrM, NULL);
                        DEBUGLOG("JNIHelpers: nativeGetRewards: Reward[%d] icon: M: %s", i, strM);
                        
                        jfieldID fL = env->GetFieldID(cIcon, "L", "Ljava/lang/String;");
                        jstring jstrL = (jstring) env->GetObjectField(iconObj, fL);
                        //const char *strL = env->GetStringUTFChars(jstrL, JNI_FALSE);
                        const char *strL = env->GetStringUTFChars(jstrL, NULL);
                        DEBUGLOG("JNIHelpers: nativeGetRewards: Reward[%d] icon: L: %s", i, strL);

//                        btLootsieReward->imageURL_S = std::string(strS);
//                        btLootsieReward->imageURL_M = std::string(strM);
//                        btLootsieReward->imageURL_L = std::string(strL);

                        std::string stdStrS(strS);
                        btLootsieReward->imageURL_S = stdStrS;
                        std::string stdStrM(strM);
                        btLootsieReward->imageURL_M = stdStrM;
                        std::string stdStrL(strL);
                        btLootsieReward->imageURL_L = stdStrL;
                        
                    } // Icon Object
                } // Icon field
            } // Icon class
            
            
            DEBUGLOG("JNIHelpers: nativeGetRewards: insert into std::vector<BTLootsieReward*> ");
            lootsieRewards.insert(lootsieRewards.end(), btLootsieReward);
            
            //need to release this string when done with it in
            //order to avoid memory leak??
            //env->ReleaseStringUTFChars(jstrDescription, strDescription);
        }
        
    } else {
        LOGE("JNIHelpers: methods are missing!");
    }
    
    DEBUGLOG("JNIHelpers: nativeGetRewards: finished scanning rewards into lootsieRewards");
              
    if (HomeLayer::sharedInstance() != NULL) {
        HomeLayer::sharedInstance()->_showPopUpRewardsLayer(lootsieRewards);
    } else if (GameLayer::sharedInstance() != NULL) {
        GameLayer::sharedInstance()->_showPopUpRewardsLayer(lootsieRewards);
    } else {
        LOGD("JNIHelpers: nativeGetRewards: no layer to return lootsieRewards to!");
    }

    
}

    
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
    
    // do methods exist on cList class?
    if ((mSize != NULL) && (mGet != NULL) && (testObj != NULL)) {
        
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

void JniHelpers::jniCommonVoidCall(const char* methodName, const char* classPath, const char* arg0, const char *arg1) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    cocos2d::JniMethodInfo minfo;
    
    bool isHave = cocos2d::JniHelper::getStaticMethodInfo(minfo, classPath, methodName, "(Ljava/lang/String;Ljava/lang/String;)V");
    
    if (isHave)
    {
        jstring stringArg0 = minfo.env->NewStringUTF(arg0);
        jstring stringArg1 = minfo.env->NewStringUTF(arg1);
        
        //minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID, stringArg0);
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, stringArg0, stringArg1);
        
        minfo.env->DeleteLocalRef(stringArg0);
        minfo.env->DeleteLocalRef(stringArg1);
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