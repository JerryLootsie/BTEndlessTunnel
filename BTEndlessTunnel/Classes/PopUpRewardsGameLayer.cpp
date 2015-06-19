//
//  PopUpRewardsGameLayer.cpp
//  BTEndlessTunnel
//
//  Created by Jerry Lootsie on 6/18/15.
//
//

#include "PopUpRewardsGameLayer.h"

static PopUpRewardsGameLayer *instance = NULL;

PopUpRewardsGameLayer* PopUpRewardsGameLayer::sharedInstance()
{
    if (instance == NULL) {
        instance = new PopUpRewardsGameLayer();
    }
    return instance;
}

void PopUpRewardsGameLayer::cleanupSharedInstance()
{
    instance = NULL;
}


//PopUpRewardsGameLayer::PopUpRewardsGameLayer()
//{
//    PopUpRewardsGameLayer::PopUpRewardsGameLayer();
//    //__super::PopUpRewardsGameLayer();
//}