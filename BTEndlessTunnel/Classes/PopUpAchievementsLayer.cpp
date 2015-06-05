//
//  PopUpAchievementsLayer.cpp
//  BTEndlessTunnel
//
//  Created by Jerry Lootsie on 6/5/15.
//
//

#include "PopUpAchievementsLayer.h"

//
//  PopUpAchievementsLayer.cpp
//  BTEndlessTunnel
//
//

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

PopUpAchievementsLayer::PopUpAchievementsLayer()
{
    
    if(initWithColor(ccc4BFromccc4F(ccc4f(0, 0, 0, 100.0f / 255.0f))))
    {
        _leaderboardID = "";
        
        _score = 0;
        disable = false;
        
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint visibleOrigin = CCDirector::sharedDirector()->getVisibleOrigin();
        CCPoint origin = ccp(visibleOrigin.x + visibleSize.width * 0.5f, visibleOrigin.y + visibleSize.height* 0.5f);
        
        // BGWhite
        //CCSprite* bg = CCSprite::create("gameover_screen.png");
        CCSprite* bgLeft = CCSprite::create("achievement_bg.png");
        CCPoint achievmentsGroupPointLeft = ccp(visibleOrigin.x + (visibleSize.width * 0.5f) - (bgLeft->getTextureRect().size.width * 0.5f),
                                                visibleOrigin.y + visibleSize.height* 0.5f);
        bgLeft->setPosition(achievmentsGroupPointLeft);
        addChild(bgLeft);
        
        CCSprite* bgRight = CCSprite::create("achievement_bg.png");
        //bgRight->setRotation(180.0f);
        bgRight->setFlipX(true);
        
        CCPoint achievmentsGroupPointRight = ccp(visibleOrigin.x + (visibleSize.width * 0.5f) + (bgRight->getTextureRect().size.width * 0.5f),
                                                visibleOrigin.y + visibleSize.height* 0.5f);
        bgRight->setPosition(achievmentsGroupPointRight);
        addChild(bgRight);
        
        _lblTitle = CCLabelTTF::create("Achievements", FONT_GAME, SIZE_TUT_TITLE, CCSizeMake(visibleSize.width * 0.5f, visibleSize.height * 0.15f), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
        _lblTitle->setPosition(ccp(origin.x,  visibleOrigin.y + visibleSize.height* 0.92f));
        _lblTitle->setColor(ccWHITE);
        addChild(_lblTitle);
        
        
        float w = bgLeft->getContentSize().width;
        float h = bgLeft->getContentSize().height;
        CCPoint o = ccp(w * 0.5f, h * 0.5f);
        
        // Badge and record
//        spBadge = CCSprite::create("bicho_0004.png");
//        spBadge->setPosition(ccp(o.x, o.y + spBadge->getContentSize().height * 0.5f));
//        bgLeft->addChild(spBadge, 10);
        
//        _lblScore = CCLabelTTF::create("", FONT_GAME, SIZE_RATE_END, CCSizeMake(w * 0.5f, h * 0.15f), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
//        _lblScore->setPosition(ccp(o.x + spBadge->getContentSize().width * 0.8f, o.y - spBadge->getContentSize().height * 0.1f));
//        _lblScore->setColor(ccWHITE);
//        _lblScore->setRotation(-3);
//        bgLeft->addChild(_lblScore);
        
//        _lblMaxScore = CCLabelTTF::create("", FONT_GAME, _lblScore->getFontSize(), CCSizeMake(w * 0.5f, h * 0.15f), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
//        _lblMaxScore->setPosition(ccp(_lblScore->getPositionX(), _lblScore->getPositionY() - spBadge->getContentSize().height * 0.28f));
//        _lblMaxScore->setColor(ccWHITE);
//        _lblMaxScore->setRotation(_lblScore->getRotation());
//        bgLeft->addChild(_lblMaxScore);
        
        // Send score button
//        CCMenuItemImage* itemScore = CCMenuItemImage::create("fb-icon.png", "fb-icon.png", this, menu_selector(PopUpAchievementsLayer::_onOptionPressed));
//        itemScore->setTag(kTagSendScore);
//        itemScore->setPositionX(o.x - itemScore->getContentSize().width * 1.5f);
//        itemScore->setPositionY(o.y - itemScore->getContentSize().height * 1.7f);
        
        // Home button
        CCMenuItemImage* itemHome = CCMenuItemImage::create("pause_home_off.png", "pause_home.png", this,
                                                            menu_selector(PopUpAchievementsLayer::_onOptionPressed));
        itemHome->setTag(kTagGoHome);
//        itemHome->setPositionX(visibleOrigin.x + itemHome->getContentSize().width * 1.5f);
//        itemHome->setPositionY(visibleOrigin.y + itemHome->getContentSize().height );
        itemHome->setPositionX(visibleOrigin.x);
        itemHome->setPositionY(visibleOrigin.y + visibleSize.height* 0.60f);

        
        // Play again button
//        CCMenuItemImage* itemPlayAgain = CCMenuItemImage::create("pause_replay_off.png", "pause_replay.png", this, menu_selector(PopUpAchievementsLayer::_onOptionPressed));
//        itemPlayAgain->setTag(kTagPlayAgain);
//        itemPlayAgain->setPositionX(itemHome->getPositionX() + itemScore->getContentSize().width * 1.5f);
//        itemPlayAgain->setPositionY(itemScore->getPositionY());
        
//        itemPlayAgain->setPositionY(itemPlayAgain->getPositionY() + itemScore->getContentSize().height * 0.2f);
//        itemHome->setPositionY(itemHome->getPositionY() + itemScore->getContentSize().height * 0.1f);
        
        // Menu
        CCMenu* menu = CCMenu::create();
        menu->setAnchorPoint(ccp(0, 0));
        menu->setPosition(CCPointZero);
        
        //        menu->addChild(itemScore);
        menu->addChild(itemHome);
//        menu->addChild(itemPlayAgain);
        
        bgLeft->addChild(menu);
        
        
    }
}

void PopUpAchievementsLayer::_setHomeLayer(HomeLayer *inputLayer) {
    
    this->_homeLayer = inputLayer;
    
}

void PopUpAchievementsLayer::_onOptionPressed(CCObject *pSender)
{
    if(disable)
        return;
    
    CCMenuItem* item = (CCMenuItem*) pSender;
    SimpleAudioEngine::sharedEngine()->playEffect(SFX_BUTTON);
    
    switch (item->getTag()) {
        case kTagPlayAgain:
            NativeUtils::sendAnalytics("Game Over - Play Again");
//            CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_PLAY_AGAIN);
            break;
            
        case kTagSendScore:
            NativeUtils::sendAnalytics("Game Over - Share Facebook");
            NativeUtils::shareOnFacebook(_score, _level, _obstaclesAvoided);
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