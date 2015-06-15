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
#include "HttpClient.h"

#include "cocos2d.h"
#include "cocos-ext.h"

#include "BTLootsieReward.h"

class HomeLayer;

enum RewardButtons
{
    kTagTOS = 9,
    kTagDetails = 10,
    kTagRedeem = 11
};

class PopUpRewardsLayer : public cocos2d::CCLayerColor
{
public:
    PopUpRewardsLayer();
    
    void _setHomeLayer(HomeLayer *inputLayer);
    void _setRewards(std::vector<BTLootsieReward*> lootsieRewards);
    
    
private:
    void _onOptionPressed(cocos2d::CCObject* pSender);
    void _onOptionPressed_TOS(CCObject *pSender);
    void _onOptionPressed_Details(CCObject *pSender);
    
    // link back to parent layer
    HomeLayer *_homeLayer;
    cocos2d::CCLabelTTF* _lblTitle;
    cocos2d::CCMenu* _menu;
    
    
    std::vector<BTLootsieReward*> lootsieRewards;
    
    void _createRewardGUI(int rewardIndex, BTLootsieReward *lootsieReward);
    
    
    std::map<std::string, cocos2d::CCSprite*> urlToSpriteMap;
    
    int createStringHash(std::string s);
    void downLoadImage(char *imageURL, cocos2d::CCSprite* rewardBg);
    void onImageDownLoaded(cocos2d::extension::CCHttpClient* pSender, cocos2d::extension::CCHttpResponse* pResponse);
//    void onImageDownLoaded(cocos2d::extension::CCHttpClient* pSender, cocos2d::extension::CCHttpResponse* pResponse, cocos2d::CCSprite* rewardBg);

    
    bool disable;    
};

#endif
