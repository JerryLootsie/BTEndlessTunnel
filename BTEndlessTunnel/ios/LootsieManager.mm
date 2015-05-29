//
//  LootsieManager.mm
//  BTEndlessTunnel
//
//  Created by Jerry Lootsie on 4/23/15.
//
//

#include <stdio.h>
#include "LootsieManager.h"
#include "Lootsie.h"
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