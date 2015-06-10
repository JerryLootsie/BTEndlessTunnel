//
//  LootsieManager.h
//  BTEndlessTunnel
//
//  Created by Jerry Lootsie on 4/23/15.
//
//

#ifndef BTEndlessTunnel_LootsieManager_h
#define BTEndlessTunnel_LootsieManager_h

#include <vector.h>
#include <stdio.h>

#include "BTLootsieAchievement.h"

class LootsieManager
{
public:
    static LootsieManager& sharedInstance();
    
    //We define a static method to call the function directly using the class_name
    static void achievementReached(char*);
    static void showAchievements();
    void getAchievements();
    

    std::vector<BTLootsieAchievement*> lootsieAchievments;
};

#endif
