//
//  PopUpRewardsLayer.cpp
//  BTEndlessTunnel
//
//  Created by Jerry Lootsie on 6/12/15.
//
//

#include "PopUpRewardsLayer.h"

#include <stdio.h>

#include "Constants.h"
#include "HomeScene.h"
#include "AppMacros.h"
#include "LocalStorageManager.h"
#include "Utils.h"
#include "PlayGameConstants.h"
#include "GameLayer.h"
#include "NativeUtils.h"
#include "SimpleAudioEngine.h"


using namespace cocos2d;
using namespace CocosDenshion;

PopUpRewardsLayer::PopUpRewardsLayer()
{
    
    if(initWithColor(ccc4BFromccc4F(ccc4f(0, 0, 0, 100.0f / 255.0f))))
    {
        disable = false;
        
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint visibleOrigin = CCDirector::sharedDirector()->getVisibleOrigin();
        CCPoint origin = ccp(visibleOrigin.x + visibleSize.width * 0.5f, visibleOrigin.y + visibleSize.height* 0.5f);
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        // title of layer
        _lblTitle = CCLabelTTF::create("Marketplace", FONT_GAME, SIZE_TUT_TITLE, CCSizeMake(visibleSize.width * 0.5f, visibleSize.height * 0.15f), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
        _lblTitle->setPosition(ccp(origin.x,  visibleOrigin.y + visibleSize.height* 0.92f));
        _lblTitle->setColor(ccWHITE);
        addChild(_lblTitle);
        
        
        
        
        // Home button
        CCMenuItemImage* itemHome = CCMenuItemImage::create("pause_home_off.png", "pause_home.png", this,
                                                            menu_selector(PopUpRewardsLayer::_onOptionPressed));
        itemHome->setTag(kTagGoHome);
        //itemHome->setPositionX(origin.x);
        itemHome->setPositionX(itemHome->getContentSize().width * 0.75f);
        //itemHome->setPositionY(origin.y);
        itemHome->setPositionY(winSize.height - (itemHome->getContentSize().height * 1.7f));
        itemHome->retain();
        std::cout << "PopUpRewardsLayer: itemHome: " << itemHome->getContentSize().width << "x" << itemHome->getContentSize().height << std::endl;
        
        // Menu
        _menu = CCMenu::create();
        _menu->setAnchorPoint(ccp(0, 0));
        _menu->setPosition(CCPointZero);
        _menu->addChild(itemHome);
        
       
        
        _menu->retain();
        addChild(_menu);

    }
}

void PopUpRewardsLayer::_setHomeLayer(HomeLayer *inputLayer) {
    
    this->_homeLayer = inputLayer;
    
}

void PopUpRewardsLayer::_setRewards(std::vector<BTLootsieReward*> inputLootsieRewards) {
    
    std::cout << "PopUpRewardsLayer: _setRewards: " << inputLootsieRewards.size() << std::endl;
    
    lootsieRewards = inputLootsieRewards;
    
    
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint visibleOrigin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCPoint origin = ccp(visibleOrigin.x + visibleSize.width * 0.5f, visibleOrigin.y + visibleSize.height* 0.5f);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    BTLootsieReward *lootsieReward = NULL;
    if (lootsieRewards.size() > 0) {
        lootsieReward = lootsieRewards[0];
        
        _createRewardGUI(lootsieReward);
    }
    

    
}

void PopUpRewardsLayer::_createRewardGUI(BTLootsieReward *lootsieReward) {
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint visibleOrigin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCPoint origin = ccp(visibleOrigin.x + visibleSize.width * 0.5f, visibleOrigin.y + visibleSize.height* 0.5f);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    // cover up the background behind the scrollable area
    CCSprite* rewardBg = CCSprite::create("reward_bg.png");
    rewardBg->setPosition(ccp((winSize.width/2),
                              visibleOrigin.y + visibleSize.height* 0.5f));
    rewardBg->retain();
    addChild(rewardBg);
    
    
    // title
    if (lootsieReward != NULL) {
        std::cout << "PopUpRewardsLayer: reward: " << lootsieReward->name << std::endl;
        cocos2d::CCLabelTTF *rewardTitle = CCLabelTTF::create(lootsieReward->name.c_str(), FONT_GAME, SIZE_RATE_APP, CCSizeMake(visibleSize.width * 0.5f, visibleSize.height * 0.035f), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
        //rewardTitle->setPosition(ccp(origin.x,  (winSize.height/2)));
        //rewardTitle->setPosition(ccp(0, 0));
        rewardTitle->setPosition(ccp((rewardBg->getContentSize().width/2), (rewardBg->getContentSize().height - (rewardTitle->getContentSize().height/2))));
        rewardTitle->setColor(ccWHITE);
        rewardBg->addChild(rewardTitle);
    }
    
    
    // tos button
    CCMenuItem *tosItem  = CCMenuItemImage::create("tos_btn_pristine.png", "tos_btn_hit.png", this, menu_selector(PopUpRewardsLayer::_onOptionPressed));
    tosItem->setTag(kTagTOS);
    //tosItem->setAnchorPoint(ccp(0, 0));
    tosItem->setAnchorPoint(ccp(0.5, 0.5));
    tosItem->setPosition(ccp((winSize.width/2) - (rewardBg->getContentSize().width/2) + (tosItem->getContentSize().width),
                             (winSize.height/2) - (rewardBg->getContentSize().height/2) + (tosItem->getContentSize().height*1.2)));
    //                                 visibleOrigin.y + visibleSize.height* 0.5f - (rewardBg->getContentSize().height/2) + (tosItem->getContentSize().height)));
    tosItem->retain();
    
    
    CCLabelTTF* tosLabel = CCLabelTTF::create("TOS", FONT_GAME, SIZE_RATE_APP);
    tosLabel->setAnchorPoint(ccp(0.5, 0.5));
    tosLabel->setPosition(ccp((tosItem->getContentSize().width/2), (tosItem->getContentSize().height/2)));
    tosLabel->setColor(ccBLACK);
    tosItem->addChild(tosLabel);
    
    
    
    // details button
    CCMenuItem *detailsItem  = CCMenuItemImage::create("details_btn_pristine.png", "details_btn_hit.png", this, menu_selector(PopUpRewardsLayer::_onOptionPressed));
    detailsItem->setTag(kTagDetails);
    //        detailsItem->setAnchorPoint(ccp(0, 0));
    detailsItem->setAnchorPoint(ccp(0.5, 0));
    detailsItem->setPosition(ccp((winSize.width/2) + (rewardBg->getContentSize().width/2) - (detailsItem->getContentSize().width),
                                 (winSize.height/2) - (rewardBg->getContentSize().height/2) + (detailsItem->getContentSize().height*1.2)));
    //                                 visibleOrigin.y + visibleSize.height* 0.5f - (rewardBg->getContentSize().height/2) + (detailsItem->getContentSize().height)));
    detailsItem->retain();
    
    
    CCLabelTTF* detailsLabel = CCLabelTTF::create("DETAILS", FONT_GAME, SIZE_RATE_APP);
    detailsLabel->setAnchorPoint(ccp(0.5, 0.5));
    detailsLabel->setPosition(ccp((detailsItem->getContentSize().width/2), (detailsItem->getContentSize().height/2)));
    detailsLabel->setColor(ccBLACK);
    detailsItem->addChild(detailsLabel);
    
    
    
    // redeem button
    CCMenuItem *redeemItem  = CCMenuItemImage::create("redeem_btn_small.png", "redeem_btn_small_off.png", this, menu_selector(PopUpRewardsLayer::_onOptionPressed));
    redeemItem->setTag(kTagRedeem);
    //        redeemItem->setAnchorPoint(ccp(0, 0));
    redeemItem->setAnchorPoint(ccp(0.5, 0));
    redeemItem->setPosition(ccp((winSize.width/2),
                                (winSize.height/2) - (rewardBg->getContentSize().height/2) - (detailsItem->getContentSize().height*.25)
                                ));
    
    redeemItem->retain();
    
    
    CCLabelTTF* redeemLabel = CCLabelTTF::create("REDEEM", FONT_GAME, SIZE_RATE_APP);
    redeemLabel->setAnchorPoint(ccp(0.5, 0.5));
    redeemLabel->setPosition(ccp((redeemItem->getContentSize().width/2), (redeemItem->getContentSize().height/2)));
    redeemLabel->setColor(ccBLACK);
    redeemItem->addChild(redeemLabel);
    
    // menu
    cocos2d::CCMenu* rewardMenu = CCMenu::create();
    rewardMenu->setAnchorPoint(ccp(0, 0));
    rewardMenu->setPosition(CCPointZero);
    
    rewardMenu->addChild(tosItem);
    rewardMenu->addChild(detailsItem);
    rewardMenu->addChild(redeemItem);
    
    addChild(rewardMenu);
    
}


void PopUpRewardsLayer::_onOptionPressed(CCObject *pSender)
{
    if(disable)
        return;
    
    CCMenuItem* item = (CCMenuItem*) pSender;
    SimpleAudioEngine::sharedEngine()->playEffect(SFX_BUTTON);
    
    switch (item->getTag()) {
//        case kTagPlayAgain:
//            NativeUtils::sendAnalytics("Game Over - Play Again");
//            //            CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_PLAY_AGAIN);
//            break;
            
//        case kTagSendScore:
//            NativeUtils::sendAnalytics("Game Over - Share Facebook");
//            NativeUtils::shareOnFacebook(_score, _level, _obstaclesAvoided);
//            break;
            
        case kTagTOS:
            std::cout << "PopUpAchievementsLayer: kTagTOS\n";
            
            break;
            
        case kTagDetails:
            std::cout << "PopUpAchievementsLayer: kTagDetails\n";
            
            break;
            
        case kTagRedeem:
            std::cout << "PopUpAchievementsLayer: kTagRedeem\n";
            
            break;
            
        case kTagGoHome:
            std::cout << "PopUpAchievementsLayer: kTagGoHome\n";
            
            NativeUtils::sendAnalytics("Game Over - Home Button");
            this->setVisible(false);
            
            _homeLayer->_showLayer();
            //            scheduleOnce(schedule_selector(HomeLayer::_showLayer), 1.0 + 0.1f);
            
            //            SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
            //            CCScene* scene = HomeScene::scene(kGameModeHome);
            //            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
            
            break;
            
    }
    
    
}



