//
//  PopUpRewardsGameLayer.h
//  BTEndlessTunnel
//
//  Created by Jerry Lootsie on 6/18/15.
//
//

#ifndef __BTEndlessTunnel__PopUpRewardsGameLayer__
#define __BTEndlessTunnel__PopUpRewardsGameLayer__

#include <stdio.h>
#include "PopupRewardsLayer.h"

class PopUpRewardsGameLayer : public PopUpRewardsLayer
{
public:
    static PopUpRewardsGameLayer* sharedInstance();
//    PopUpRewardsGameLayer();
    
    static void cleanupSharedInstance();    
};

#endif /* defined(__BTEndlessTunnel__PopUpRewardsGameLayer__) */
