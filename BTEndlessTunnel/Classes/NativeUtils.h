#ifndef __NATIVE_UTILS_H__
#define __NATIVE_UTILS_H__

/*
 Copyright (c) 2014 Carlos Eduardo Piñan Indacochea
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#include "cocos2d.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "JNIHelpers.h"
#endif

class NativeUtils
{
public:
	/*
	* Google play game services methods
	*/
	static bool isSignedIn();
	static void signIn();
	static void signOut();
	
    static void submitScore(const char* leaderboardID, long score);
	
    static void unlockAchievement(const char* achievementID);
	static void incrementAchievement(const char* achievementID, int numSteps);
    static void incrementPercentageAchievement(const char *achievementID, float percentage);
	
    static void showAchievements();
    static void getAchievements();
    
    static void getRewards();
    //static void redeemReward(std::string emailStr, long rewardId);
    //static void redeemReward(std::string emailStr, std::string rewardId);
    static void redeemReward(const char *emailStr, const char *rewardIdStr);
    
	static void showLeaderboards();
	static void showLeaderboard(const char* leaderboardID);
    
    static void initAd();
    static void showAd();
    static void hideAd();
    
    static void rateApp();
    
    static void showAdBuddiz();
    
    static void sendAnalytics(const char* screen);
    
    static void shareOnFacebook(long score, int level, int obstacles);
    
    static void killApp();
	
	/*
	* Ouya connection
	*/
	

};

#endif