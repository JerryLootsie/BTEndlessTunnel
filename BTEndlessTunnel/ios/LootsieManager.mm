//
//  LootsieManager.mm
//  BTEndlessTunnel
//
//  Created by Jerry Lootsie on 4/23/15.
//
//

#include <stdio.h>
#include "LootsieManager.h"
//#include "LootsieEngine.h"
#include "Lootsie.h"

#include "HomeLayer.h"

#pragma mark - Singleton
LootsieManager& LootsieManager::sharedInstance()
{
    static LootsieManager instance;
    return instance;
}

void LootsieManager::achievementReached(char *achievementCharStr)
{
    //Objective C code calling.....
    NSString* achievementStr = [NSString stringWithFormat:@"%s" , achievementCharStr];
    NSLog(@"LootsieManager: achievementReached: %@", achievementStr);
    
    [[Lootsie sharedInstance] achievementReachedWithId:achievementStr];
    
}

void LootsieManager::showAchievements()
{
    
    [[Lootsie sharedInstance] showAchievementsPage];
    
}

void LootsieManager::getAchievements() {
    
    NSLog(@"LootsieManager: getUserAchievements");
    
    ServiceCallback callback = ^(BOOL success, id result, NSString* errorMessage, NSInteger statusCode) {
        if (errorMessage != nil) {
            NSLog(@"LootsieManager: getUserAchievements callback: %@", errorMessage);
            
            // parse result into an array of achievement names
            NSArray* achievements = result;
            
            lootsieAchievments.clear();
            
            //NSMutableArray *achievementNames = [NSMutableArray array];
            for (LootsieAchievement *achievement in achievements) {
                NSString *achievmentName = achievement.name;
                NSString *achievementDescr = achievement.description;
                NSString *achievementId = achievement.achievement_id;
                //[achievementNames addObject:achievementId];
                
                NSLog(@"LootsieManager: achievement: %@", achievementId);
                
                // copy this stuff from objective C to a cpp data structure
                BTLootsieAchievement *lootsieAchievment = new BTLootsieAchievement();
                lootsieAchievment->name = std::string([achievmentName UTF8String]);
                lootsieAchievment->description = std::string([achievementDescr UTF8String]);
                lootsieAchievment->lp = achievement.lp;
                lootsieAchievment->is_achieved = achievement.is_achieved;
                
                lootsieAchievments.push_back(lootsieAchievment);
            }
            
            HomeLayer::sharedInstance()->_showPopUpAchievementsLayer(lootsieAchievments);
        }
    };
    
    [[Lootsie sharedInstance] getUserAchievements:callback];
    
    
}

void LootsieManager::getRewards() {
    
    NSLog(@"LootsieManager: getRewards");
    
    ServiceCallback callback = ^(BOOL success, id result, NSString* errorMessage, NSInteger statusCode) {
        if (errorMessage != nil) {
            NSLog(@"LootsieManager: onGetRewards: %@", errorMessage);
            
            // parse result into an array of reward names
            NSArray* rewards = result;
            
            //NSMutableArray *rewardIds = [[NSMutableArray alloc] init];

            lootsieRewards.clear();
            
            for (LootsieReward *reward in rewards) {
                NSString *rewardDescr = reward.reward_description;
                NSString *rewardId = reward.reward_id;
                //[rewardIds addObject:rewardId];
                
                NSLog(@"LootsieManager: reward: %@ %@", rewardDescr, rewardId);
                
                // copy this stuff from objective C to a cpp data structure
                BTLootsieReward *lootsieReward = new BTLootsieReward();
                
                if (reward.brand_name) lootsieReward->brand_name = std::string([reward.brand_name UTF8String]);
                if (reward.reward_description) lootsieReward->reward_description = std::string([reward.reward_description UTF8String]);
                if (reward.reward_id) lootsieReward->reward_id = std::string([reward.reward_id UTF8String]);
                
                // engagements
                
                if (reward.image_urls != NULL) {
                    // image_urls
                    if (reward.image_urls.DETAIL) lootsieReward->imageURL_DETAIL = std::string([reward.image_urls.DETAIL UTF8String]);
                    if (reward.image_urls.L) lootsieReward->imageURL_L = std::string([reward.image_urls.L UTF8String]);
                    if (reward.image_urls.M) lootsieReward->imageURL_M = std::string([reward.image_urls.M UTF8String]);
                    if (reward.image_urls.S) lootsieReward->imageURL_S = std::string([reward.image_urls.S UTF8String]);
                    if (reward.image_urls.XL) lootsieReward->imageURL_XL = std::string([reward.image_urls.XL UTF8String]);
                }
                
                lootsieReward->is_limited_time = reward.is_limited_time;
                lootsieReward->is_new = reward.is_new;
                lootsieReward->lp = reward.lp;
                if (reward.name) lootsieReward->name = std::string([reward.name UTF8String]);
                lootsieReward->redemptions_remaining = reward.redemptions_remaining;
                
                if (reward.text_to_share) lootsieReward->text_to_share = std::string([reward.text_to_share UTF8String]);
                if (reward.tos_text) lootsieReward->tos_text = std::string([reward.tos_text UTF8String]);
                if (reward.tos_url) lootsieReward->tos_url = std::string([reward.tos_url UTF8String]);
                
                lootsieRewards.push_back(lootsieReward);
            }
            
            // send it back to homelayer or gamelayer
            if (HomeLayer::sharedInstance() != NULL) {
                HomeLayer::sharedInstance()->_showPopUpRewardsLayer(lootsieRewards);
            } else if (GameLayer::sharedInstance() != NULL) {
                GameLayer::sharedInstance()->_showPopUpRewardsLayer(lootsieRewards);
            } else {
                NSLog(@"LootsieManager: getRewards: no layer to return lootsieRewards to!");
            }
        }
    };
    
    [[Lootsie sharedInstance] getUserRewards:callback];
}

void LootsieManager::redeemReward(char *emailStr, char *rewardIdStr)
{
    NSLog(@"LootsieManager: redeemReward");
    
    //NSString *rewardIdNSStr = [NSString stringWithFormat:@"%ld", rewardId];
    NSString *rewardIdNSStr = [[NSString alloc] initWithCString:rewardIdStr encoding:NSASCIIStringEncoding];
    NSString *emailNSStr = [[NSString alloc] initWithCString:emailStr encoding:NSASCIIStringEncoding];
    
    ServiceCallback callback = ^(BOOL success, id result, NSString* errorMessage, NSInteger statusCode) {
        if (errorMessage != nil) {
            NSLog(@"LootsieManager: redeemReward: %@", errorMessage);
            
            char *messageStr = (char*) [errorMessage UTF8String];
            cocos2d::CCMessageBox(messageStr, "Message");
        }
    };
    
    [[Lootsie sharedInstance] redeemReward:rewardIdNSStr email:emailNSStr callback:callback];
    
}

