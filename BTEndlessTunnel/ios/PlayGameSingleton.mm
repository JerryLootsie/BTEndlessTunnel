//
//  ControllerSingleLeaderboard.m
//  GooglePlayGameServices
//
//  Created by NSS on 4/7/14.
//
//

#import "PlayGameSingleton.h"
//#import "AdMobBannerView.h"
#import "Globals.h"
//#import <FacebookSDK/FacebookSDK.h>
//#import "GCHelper.h"
#import "GameLayer.h"
#import <UIKit/UIKit.h>

#import "LootsieManager.h"

#import "cocos2d.h"

#define APP_ID 864587748 //id from iTunesConnect

using namespace cocos2d;

// A function for parsing URL parameters returned by the Feed Dialog.
NSDictionary* parseURLParams(NSString* query)
{
    NSArray *pairs = [query componentsSeparatedByString:@"&"];
    NSMutableDictionary *params = [[NSMutableDictionary alloc] init];
    for (NSString *pair in pairs) {
        NSArray *kv = [pair componentsSeparatedByString:@"="];
        NSString *val =
        [kv[1] stringByReplacingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
        params[kv[0]] = val;
    }
    return params;
}

#pragma mark - Declare Views
//AdMobBannerView* adMobBannerView = 0;

#pragma mark - Destructor and Constructor
PlayGameSingleton::~PlayGameSingleton()
{
    rootController = 0;
}

PlayGameSingleton::PlayGameSingleton()
{
}

#pragma mark - Singleton
PlayGameSingleton& PlayGameSingleton::sharedInstance()
{
    static PlayGameSingleton instance;
    return instance;
}

#pragma mark - Single Leaderboard
void PlayGameSingleton::showSingleLeaderboard(const char* leaderBoardID)
{    

}

void PlayGameSingleton::finishSingleLeaderboard()
{
    CCDirector::sharedDirector()->startAnimation();
}

#pragma mark - Leaderboards Picker
void PlayGameSingleton::showLeaderboards()
{
    

}

void PlayGameSingleton::finishLeaderboards()
{
    CCDirector::sharedDirector()->startAnimation();
}

#pragma mark - Submit score
void PlayGameSingleton::submitScore(long score, const char *leaderBoardID)
{
    
}

#pragma mark - Achievements
void PlayGameSingleton::showAchievements()
{
    std::cout << "PlayGameSingleton: showAchievments\n";
    
    LootsieManager::showAchievements();
}

void PlayGameSingleton::finishAchievements()
{
    CCDirector::sharedDirector()->startAnimation();
}

#pragma mark - Manage achievements
void PlayGameSingleton::revealAchievement(const char *achievementID)
{
    if(!isSignedIn())
        return;
}

void PlayGameSingleton::unlockAchievement(const char *achievementID)
{
    
    LootsieManager::achievementReached((char *)achievementID);
    
}

void PlayGameSingleton::incrementPercentageAchievement(float percentage, const char *achievementID)
{

}

void PlayGameSingleton::incrementAchievement(int numSteps, const char *achievementID)
{
    if(!isSignedIn())
        return;
}

#pragma mark - Login configuration
void PlayGameSingleton::trySilentAuthentication()
{
}

void PlayGameSingleton::authenticate()
{
}

bool PlayGameSingleton::isSignedIn()
{
    // CCLOG("user_data_id: %s", user_data_id.c_str());
    return user_data_id != "";
}

void PlayGameSingleton::signOut()
{
    if(isSignedIn())
    {

    }
}

#pragma mark - Advertisement
void PlayGameSingleton::initAd()
{

}


void PlayGameSingleton::showAd()
{
//    [adMobBannerView show];
}

void PlayGameSingleton::hideAd()
{

}

void PlayGameSingleton::rateApp()
{
    NSString *reviewURL = [NSString stringWithFormat:@"itms-apps://ax.itunes.apple.com/WebObjects/MZStore.woa/wa/viewContentsUserReviews?type=Purple+Software&id=%d", APP_ID];
    
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:reviewURL]];
    
}

void PlayGameSingleton::shareOnFacebook(long score, int level, int obstacles)
{
    
    ccLanguageType language = CCApplication::sharedApplication()->getCurrentLanguage();
    
    NSString* str_level = @"fácil";
    if(level == kGameLevelNormal)
        str_level = @"normal";
    else if(level == kGameLevelHard)
        str_level = @"difícil";
    
    if(language == kLanguageEnglish)
    {
       if(level == kGameLevelEasy)
           str_level = @"easy";
        else if(level == kGameLevelHard)
            str_level = @"hard";
    }
    
    NSString* linkToShare = @"https://itunes.apple.com/us/app/turbo-race/id864587748?ls=1&mt=8";
    
    NSString* name = @"Turbo Race";
    
    NSString* caption = @"Estoy jugando Turbo Race";
    if(language == kLanguageEnglish)
        caption = @"I am playing Turbo Race";
    
    NSString* picture = @"http://carlospinan.com/icon/turbo_race.png";
    
    NSString* str_format = @"He obtenido %ld puntos en modo %@ y he esquivado %d obstáculos.";
    if(language == kLanguageEnglish)
        str_format = @"I got %ld points in %@ mode and I avoided %d obstacles.";
    
    NSString* description = [NSString stringWithFormat:str_format, score, str_level, obstacles];
    
    NSURL* params_link = [NSURL URLWithString:linkToShare];
    NSURL* params_picture = [NSURL URLWithString:picture];
    

    
}

void PlayGameSingleton::getAchievements()
{
    std::cout << "PlayGameSingleton: getAchievements\n";
    LootsieManager::sharedInstance().getAchievements();
}

void PlayGameSingleton::getRewards()
{
    std::cout << "PlayGameSingleton: getRewards\n";
    LootsieManager::sharedInstance().getRewards();
}

void PlayGameSingleton::redeemReward(const char* emailStr, const char *rewardId)
{
    std::cout << "PlayGameSingleton: redeemReward\n";
    
    LootsieManager::sharedInstance().redeemReward((char *)emailStr, (char *)rewardId);
}


