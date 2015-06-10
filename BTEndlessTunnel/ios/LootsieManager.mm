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
    
    // TODO: get these achievements to show up in Lootsie.h without restkit
    
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
                
                // copy this stuff to a cpp data structure
                BTLootsieAchievement *lootsieAchievment = new BTLootsieAchievement();
                lootsieAchievment->name = std::string([achievmentName UTF8String]);
                lootsieAchievment->description = std::string([achievementDescr UTF8String]);
                lootsieAchievment->lp = achievement.lp;
                lootsieAchievment->is_achieved = achievement.is_achieved;
                
                lootsieAchievments.push_back(lootsieAchievment);
            }
            
            
            //HomeLayer::_showPopUpAchievementsLayer();
            HomeLayer::sharedInstance()->_showPopUpAchievementsLayer(lootsieAchievments);
            
            //achievementIndex = 0;
        }
    };
    
    [[Lootsie sharedInstance] getUserAchievements:callback];
    
    
}