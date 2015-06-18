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
class RewardDisplay;

enum RewardButtons
{
    kTagTOS = 9,
    kTagDetails = 10,
    kTagRedeem = 11
};

class PopUpRewardsLayer : public cocos2d::CCLayerColor
{
public:
    //static PopUpRewardsLayer& sharedInstance();
    static PopUpRewardsLayer* sharedInstance();
    PopUpRewardsLayer();
    
    static void cleanupSharedInstance();
    
    void _setHomeLayer(HomeLayer *inputLayer);
    void _setRewards(std::vector<BTLootsieReward*> lootsieRewards);
    
    std::map<std::string, cocos2d::CCSprite*> urlToSpriteMap;
    std::vector<BTLootsieReward*> lootsieRewards;
    std::vector<RewardDisplay*> rewardDisplays;
private:
    void _onOptionPressed(cocos2d::CCObject* pSender);

    
    
    // link back to parent layer
    HomeLayer *_homeLayer;
    cocos2d::CCLabelTTF* _lblTitle;
    cocos2d::CCMenu* _menu;
    
    // scrollview, scrollcontainer for showing rewards
    cocos2d::extension::CCScrollView *scrollView;
    cocos2d::CCLayer *scrollContainer;
    
    //void _createRewardGUI(int rewardIndex, BTLootsieReward *lootsieReward);
    
    // keep a link to this
    //RewardDisplay *rewardDisplay;

    
    int createStringHash(std::string s);

    
    bool disable;    
};

#endif
