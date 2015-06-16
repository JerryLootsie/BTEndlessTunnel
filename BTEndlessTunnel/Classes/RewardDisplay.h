//
//  RewardDisplay.h
//  BTEndlessTunnel
//
//  Created by Jerry Lootsie on 6/16/15.
//
//

#ifndef BTEndlessTunnel_RewardDisplay_h
#define BTEndlessTunnel_RewardDisplay_h

#include <vector>
#include "HttpClient.h"

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCMenuItem.h"

#include "BTLootsieReward.h"

class RewardDisplay : public cocos2d::extension::CCEditBoxDelegate
{
public:
    //RewardDisplay(BTLootsieReward *lootsieReward);
    RewardDisplay(cocos2d::CCLayerColor *layer, BTLootsieReward *lootsieReward, int rewardIndex);
    
    cocos2d::CCLayerColor *layer;
    
    cocos2d::CCSprite *rewardBg;
    
    cocos2d::CCLabelTTF *rewardTitle;
    cocos2d::CCLabelTTF *rewardCost;
    
    cocos2d::CCMenuItem *tosItem;
    cocos2d::CCLabelTTF *tosLabel;
    
    cocos2d::CCMenuItem *detailsItem;
    cocos2d::CCLabelTTF *detailsLabel;
    
    cocos2d::CCMenuItem *redeemItem;
    cocos2d::CCLabelTTF *redeemLabel;
    
    cocos2d::CCMenu* rewardMenu;
    
    BTLootsieReward *lootsieReward;
    
    void editBoxEditingDidBegin(cocos2d::extension::CCEditBox *editBox);
    void editBoxEditingDidEnd(cocos2d::extension::CCEditBox *editBox);
    void editBoxTextChanged(cocos2d::extension::CCEditBox *editBox, std::string &text);
    void editBoxReturn(cocos2d::extension::CCEditBox *editBox);
    
private:
    
    int rewardIndex; // reference into parent PopUpRewardsLayer rewards
    
//    void downLoadImage(char *imageURL, cocos2d::CCSprite* rewardBg);
    void downLoadImage(char *imageURL, cocos2d::CCSprite *rewardBg, std::string imageFileStr);
    void onImageDownLoaded(cocos2d::extension::CCHttpClient* pSender, cocos2d::extension::CCHttpResponse* pResponse);
    
    void _onOptionPressed_TOS(cocos2d::CCObject *pSender);
    void _onOptionPressed_Details(cocos2d::CCObject *pSender);
    void _onOptionPressed_Redeem(cocos2d::CCObject *pSender);
    
};

#endif
