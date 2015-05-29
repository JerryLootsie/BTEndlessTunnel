//
//  LootsieManager.h
//  BTEndlessTunnel
//
//  Created by Jerry Lootsie on 4/23/15.
//
//

#ifndef BTEndlessTunnel_LootsieManager_h
#define BTEndlessTunnel_LootsieManager_h

#include <stdio.h>
class LootsieManager
{
public:
    //We define a static method to call the function directly using the class_name
    static void achievementReached(char*);
    static void showAchievements();
};

#endif
