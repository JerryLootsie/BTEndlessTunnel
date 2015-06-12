//
//  PopUpRewardsLayer.h
//  BTEndlessTunnel
//
//  Created by Jerry Lootsie on 6/12/15.
//
//

#ifndef BTEndlessTunnel_PopUpRewardsLayer_h
#define BTEndlessTunnel_PopUpRewardsLayer_h

#include <vector>
#include "cocos2d.h"
#include "cocos-ext.h"

class HomeLayer;

class PopUpRewardsLayer : public cocos2d::CCLayerColor
{
public:
    PopUpRewardsLayer();
    
    void _setHomeLayer(HomeLayer *inputLayer);
    
private:
    void _onOptionPressed(cocos2d::CCObject* pSender);
    
    // link back to parent layer
    HomeLayer *_homeLayer;

    
    bool disable;    
};

#endif
