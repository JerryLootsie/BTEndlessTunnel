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
        CCMenu* menu = CCMenu::create();
        menu->setAnchorPoint(ccp(0, 0));
        menu->setPosition(CCPointZero);
        menu->addChild(itemHome);
        menu->retain();
        addChild(menu);

    }
}

void PopUpRewardsLayer::_setHomeLayer(HomeLayer *inputLayer) {
    
    this->_homeLayer = inputLayer;
    
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



