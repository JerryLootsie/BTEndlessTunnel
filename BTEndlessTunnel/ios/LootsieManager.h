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

class LootsieAchievement
{
public:
    std::string name = "";
    bool is_achieved = false;
    std::string description = "";
    int lp = 0;
    
};

class LootsieManager
{
public:
    static LootsieManager& sharedInstance();
    
    //We define a static method to call the function directly using the class_name
    static void achievementReached(char*);
    static void showAchievements();
    void getAchievements();
    

    std::vector<LootsieAchievement*> lootsieAchievments;
};

#endif
