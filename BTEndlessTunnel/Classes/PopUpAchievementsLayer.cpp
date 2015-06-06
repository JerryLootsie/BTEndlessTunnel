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

#include <string.h>
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
        
        achievementEntries = new AchievementLine*;
        

        _addAchievementEntries(bgLeft, -3);

        _addAchievementEntries(bgRight, 3);

        
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

void PopUpAchievementsLayer::_addAchievementEntries(cocos2d::CCSprite* bgSprite, int rotationOffset) {
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint visibleOrigin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCPoint origin = ccp(visibleOrigin.x + visibleSize.width * 0.5f, visibleOrigin.y + visibleSize.height* 0.5f);

    for (int i = 0; i < 5; i++) {
        AchievementLine *achievementEntry = new AchievementLine();
        
        achievementEntries[i] = achievementEntry;
        
        

        
        
        float w = bgSprite->getContentSize().width;
        float h = bgSprite->getContentSize().height;
        CCPoint o = ccp(w * 0.5f, h * 0.5f);
        
        char buffer[50];
        sprintf(buffer, "Achievement %d",i);
        
        achievementEntry->_lblAchievement1 = CCLabelTTF::create(buffer, FONT_GAME, SIZE_RATE_END, CCSizeMake(w * 0.5f, h * 0.15f), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
        achievementEntry->_lblAchievement1->setPosition(ccp(0 + achievementEntry->_lblAchievement1->getContentSize().width,
                                                            h - (achievementEntry->_lblAchievement1->getContentSize().height * 1.1f * (i+1))));
        achievementEntry->_lblAchievement1->setColor(ccWHITE);
        achievementEntry->_lblAchievement1->setRotation(rotationOffset);
        bgSprite->addChild(achievementEntry->_lblAchievement1);
        
        
        achievementEntry->_spTrophy = CCSprite::create("achievement_icon.png");
        achievementEntry->_spTrophy->setPosition(ccp(0 + achievementEntry->_spTrophy->getContentSize().width * 1.5f,
                                                     h - (achievementEntry->_spTrophy->getContentSize().height * 2.0f)
                                                     - (achievementEntry->_lblAchievement1->getContentSize().height * 1.1f * i)));
        bgSprite->addChild(achievementEntry->_spTrophy);
        
        sprintf(buffer, "%d LP",(i*10 + 1));
        achievementEntry->_lblAchievementPoints1 = CCLabelTTF::create(buffer, FONT_GAME, SIZE_TUT_INST, CCSizeMake(w * 0.25f, h * 0.15f), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
        achievementEntry->_lblAchievementPoints1->setPosition(ccp(0 + achievementEntry->_lblAchievement1->getContentSize().width +
                                                                  achievementEntry->_lblAchievementPoints1->getContentSize().width,
                                                                  h - (achievementEntry->_spTrophy->getContentSize().height * 1.5f)
                                                                  - (achievementEntry->_lblAchievement1->getContentSize().height * 1.1f * i)));
        achievementEntry->_lblAchievementPoints1->setColor(ccWHITE);
        achievementEntry->_lblAchievementPoints1->setRotation(rotationOffset);
        bgSprite->addChild(achievementEntry->_lblAchievementPoints1);
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