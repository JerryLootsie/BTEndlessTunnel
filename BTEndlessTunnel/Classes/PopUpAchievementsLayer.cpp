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
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
//        _createAchievementScreens();
        
//        _createScrollView();
        _createScrollView2();
        
        // Home button
        CCMenuItemImage* itemHome = CCMenuItemImage::create("pause_home_off.png", "pause_home.png", this,
                                                            menu_selector(PopUpAchievementsLayer::_onOptionPressed));
        itemHome->setTag(kTagGoHome);
        //itemHome->setPositionX(origin.x);
        itemHome->setPositionX(itemHome->getContentSize().width * 0.75f);
        //itemHome->setPositionY(origin.y);
        itemHome->setPositionY(winSize.height - (itemHome->getContentSize().height * 1.7f));

        std::cout << "PopUpAchievementsLayer: itemHome: " << itemHome->getContentSize().width << "x" << itemHome->getContentSize().height << std::endl;
        
        // Menu
        CCMenu* menu = CCMenu::create();
        menu->setAnchorPoint(ccp(0, 0));
        menu->setPosition(CCPointZero);
        menu->addChild(itemHome);
        addChild(menu);
        
        
    }
}

void PopUpAchievementsLayer::_createAchievementScreens() {
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint visibleOrigin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCPoint origin = ccp(visibleOrigin.x + visibleSize.width * 0.5f, visibleOrigin.y + visibleSize.height* 0.5f);
    
    std::cout << "PopUpAchievementsLayer: visibleOrigin: " << visibleOrigin.x << "," << visibleOrigin.y << std::endl;
    std::cout << "PopUpAchievementsLayer: origin: " << origin.x << "," << origin.y << std::endl;
    
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

void PopUpAchievementsLayer::_createScrollView() {
    
    //SETUP SCROLL CONTAINER
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    std::cout << "PopUpAchievementsLayer: visibleSize: " << visibleSize.width << "x" << visibleSize.height << std::endl;
    
    scrollContainer = CCLayer::create();
    scrollContainer->setAnchorPoint(CCPointZero);
    
    float containerOffset = 90.0f;
    float vertOffset = 35.0f; //30.0f; // 25.0f;
    
//    background1 = CCSprite::create("screen_bg.png");
    background1 = CCSprite::create("background_1.png");
    //        std::cout << "PopUpAchievementsLayer: background1-scale: " << winSize.width/background1->getContentSize().width << "\n";
    std::cout << "PopUpAchievementsLayer: background1-scale: " << background1->getScale() << "\n";
    //background1->setScale(winSize.width/background1->getContentSize().width);
//    background1->setScale(winSize.height/(background1->getContentSize().height * 2));
    //background1->setPosition(ccp(winSize.width/2 , winSize.height/2));
    background1->setPosition(ccp(0.f + (background1->getContentSize().width / 2),
                                 background1->getContentSize().height - vertOffset));
    scrollContainer->addChild(background1);
    std::cout << "PopUpAchievementsLayer: background1: " << background1->getContentSize().width << "x" << background1->getContentSize().height << std::endl;
    
//    background2 = CCSprite::create("screen_bg.png");
    background2 = CCSprite::create("background_1.png");
    //        std::cout << "PopUpAchievementsLayer: background2-scale: " << winSize.width/background2->getContentSize().width << "\n";
    //        background2->setScale(winSize.width/background2->getContentSize().width);
//    background1->setScale(winSize.height/(background2->getContentSize().height * 2));
    background2->setPosition(ccp(0.f + (background2->getContentSize().width / 2),
                                 (background1->getContentSize().height * 2) - vertOffset));
    scrollContainer->addChild(background2);
    std::cout << "PopUpAchievementsLayer: background2: " << background2->getContentSize().width << "x" << background2->getContentSize().height << std::endl;
    
    
    scrollContainer->setPosition(CCPointZero);
    CCSize csize = CCSizeMake(background1->getScale() * background1->getContentSize().width,
                              (background1->getScale() * background1->getContentSize().height*2) + containerOffset);
    scrollContainer->setContentSize(csize);
    //scrollContainer->setAnchorPoint(CCPointZero);
    
    std::cout << "PopUpAchievementsLayer: scrollContainer: " << csize.width << "x" << csize.height << std::endl;
    
    //SETUP SCROLL VIEW
    CCSize viewsize = CCSizeMake(background1->getContentSize().width,
                                 (background1->getScale() * background1->getContentSize().height*2) + containerOffset);

    
    //scrollView = cocos2d::extension::CCScrollView::create(winSize, scrollContainer);
    scrollView = cocos2d::extension::CCScrollView::create(viewsize, scrollContainer);
    scrollView->setPosition(CCPointZero);
    scrollView->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
    //scrollView->setContentOffset(ccp(0.f, background1->getContentSize().height*2), false);
    scrollView->setContentOffset(ccp(0.f, -background1->getContentSize().height), false);
    scrollView->setAnchorPoint(CCPointZero);
    
    
    // draw a red border around the scrollview
    cocos2d::CCPoint vertices[4] = {ccp(0.f, 0.f),
                            ccp(0.f, scrollView->getContentSize().height * background1->getScale()),
                            ccp(scrollView->getContentSize().width * background1->getScale(), scrollView->getContentSize().height * background1->getScale()),
                            ccp(scrollView->getContentSize().width * background1->getScale(), 0.f)};
    CCDrawNode *polyNode = CCDrawNode::create();
    ccColor4F color = (ccColor4F){1,0,0,1.f};
//    ccColor4F colorbg = (ccColor4F){0,0,0,1.0f};
    ccColor4F colorfg = (ccColor4F){0,0,0,0.0f};
    polyNode->drawPolygon(vertices, 4, colorfg, 5.0f, color);
    
    
    //scrollView->addChild(polyNode);
    addChild(polyNode);
    
    //        std::cout << "PopUpAchievementsLayer: scrollView: " << winSize.width << "x" << winSize.height << std::endl;
    std::cout << "PopUpAchievementsLayer: scrollView: " << viewsize.width << "x" << viewsize.height << std::endl;
    
    

    
    scrollContainer->retain();
    addChild(scrollView);
}

void PopUpAchievementsLayer::_createScrollView2() {
    
    //SETUP SCROLL CONTAINER
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    std::cout << "PopUpAchievementsLayer: visibleSize: " << visibleSize.width << "x" << visibleSize.height << std::endl;
    
    scrollContainer = CCLayer::create();
    scrollContainer->setAnchorPoint(CCPointZero);
    
    float contentVertOffset = 256.0f;
    
    float contentHeight = 512.0f; // 600.0f;
    float contentWidth = 512.0f; // 600.0f;
    
    float horizOffset = (winSize.width/2) - (contentWidth/2);
    float vertOffset = 128.0f; //30.0f; // 25.0f;
    
    

    background1 = CCSprite::create("checkermap_512x512.png");
    background1->setPosition(ccp(0.f + (background1->getContentSize().width / 2),
                                 background1->getContentSize().height - contentVertOffset));
    scrollContainer->addChild(background1);
    std::cout << "PopUpAchievementsLayer: background1: " << background1->getContentSize().width << "x" << background1->getContentSize().height << std::endl;
    
    
    background2 = CCSprite::create("checkermap_512x512.png");
    background2->setPosition(ccp(0.f + (background2->getContentSize().width / 2),
                                 (background1->getContentSize().height * 2) - contentVertOffset));
    scrollContainer->addChild(background2);
    std::cout << "PopUpAchievementsLayer: background2: " << background2->getContentSize().width << "x" << background2->getContentSize().height << std::endl;
    
    
    
    
    scrollContainer->setPosition(CCPointZero);
    CCSize csize = CCSizeMake(background1->getContentSize().width,
                              (background1->getContentSize().height * 2));

    scrollContainer->setContentSize(csize);
    
    std::cout << "PopUpAchievementsLayer: scrollContainer: " << csize.width << "x" << csize.height << std::endl;
    
    //SETUP SCROLL VIEW
    CCSize viewsize = CCSizeMake(contentWidth,
                                 contentHeight);
    scrollView = cocos2d::extension::CCScrollView::create(viewsize, scrollContainer);
    scrollView->setPosition(CCPoint(horizOffset, vertOffset));
    scrollView->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
    scrollView->setContentOffset(ccp(0.f, 0.f), false);
    scrollView->setAnchorPoint(CCPointZero);
    
    
    // draw a red border around the scrollview
    
//    cocos2d::CCPoint vertices[4] = {ccp(0.f, 0.f),
//        ccp(0.f, vertOffset),
//        ccp(vertOffset, vertOffset),
//        ccp(vertOffset, 0.f)};
    
    cocos2d::CCPoint vertices[4] = {ccp(horizOffset, vertOffset),
        ccp(horizOffset, vertOffset + contentHeight),
        ccp(horizOffset + contentWidth, vertOffset + contentHeight),
        ccp(horizOffset + contentWidth, vertOffset)};
    
    CCDrawNode *polyNode = CCDrawNode::create();
    ccColor4F color = (ccColor4F){1,0,0,1.f};
    //    ccColor4F colorbg = (ccColor4F){0,0,0,1.0f};
    ccColor4F colorfg = (ccColor4F){0,0,0,0.0f};
    polyNode->drawPolygon(vertices, 4, colorfg, 5.0f, color);
    addChild(polyNode);
    
    
    scrollContainer->retain();
    addChild(scrollView);
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