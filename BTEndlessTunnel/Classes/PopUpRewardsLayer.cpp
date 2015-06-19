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

#include "RewardDisplay.h"

using namespace cocos2d;
using namespace CocosDenshion;

static PopUpRewardsLayer *instance = NULL;


#pragma mark - Singleton
//PopUpRewardsLayer& PopUpRewardsLayer::sharedInstance()
//{
//    static PopUpRewardsLayer instance;
//    return instance;
//}

PopUpRewardsLayer* PopUpRewardsLayer::sharedInstance()
{
    if (instance == NULL) {
        instance = new PopUpRewardsLayer();
    }
    return instance;
}

void PopUpRewardsLayer::cleanupSharedInstance()
{
    instance = NULL;
}

PopUpRewardsLayer::PopUpRewardsLayer()
{
    
    std::cout << "PopUpRewardsLayer: PopUpRewardsLayer: " << std::endl;
    
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
    

    if (lootsieRewards.size() > 0) {
        //RewardDisplay *rewardDisplay = rewardDisplays[0];
        CCSprite *tempBg = CCSprite::create("reward_bg.png");
        
        int maxRewards = 5;
        //float displayRewards = 2;
        float displayRewards = winSize.width / tempBg->getContentSize().width;
        
        float horizOffset = 0;
        //float vertOffset = (winSize.height/2) - (tempBg->getContentSize().height * 0.5f);
        float vertOffset = (winSize.height/2) - (tempBg->getContentSize().height * 0.7f);
        float contentWidth = (tempBg->getContentSize().width * displayRewards);
        float contentHeight = tempBg->getContentSize().height * 1.2;
        
//        cocos2d::CCPoint vertices[4] = {ccp(horizOffset, vertOffset),
//            ccp(horizOffset, vertOffset + contentHeight),
//            ccp(horizOffset + contentWidth, vertOffset + contentHeight),
//            ccp(horizOffset + contentWidth, vertOffset)};
//        
//        CCDrawNode *polyNode = CCDrawNode::create();
//        ccColor4F color = (ccColor4F){1,0,0,1.f};
//        //    ccColor4F colorbg = (ccColor4F){0,0,0,1.0f};
//        ccColor4F colorfg = (ccColor4F){0,0,0,0.0f};
//        polyNode->drawPolygon(vertices, 4, colorfg, 5.0f, color);
//        addChild(polyNode);
        
        
        
        // create scrollview, scrollcontent

        
        // setup scroll container
        scrollContainer = CCLayer::create();
        scrollContainer->setAnchorPoint(CCPointZero);
        


        rewardDisplays.clear();
        
        //if (lootsieRewards.size() > 0) {
        //for (int i=0; i<lootsieRewards.size(); i++) {
        //for (int i=0; i<lootsieRewards.size() && (i<2); i++) {
        //maxRewards = lootsieRewards.size();
        for (int i=0; i<lootsieRewards.size() && (i<maxRewards); i++) {
        //for (int i=0; i<lootsieRewards.size(); i++) {
            BTLootsieReward *lootsieReward = NULL;
            lootsieReward = lootsieRewards[i];
            
            RewardDisplay *rewardDisplay = new RewardDisplay(scrollContainer, lootsieReward, i);
            rewardDisplays.push_back(rewardDisplay);
        }
        
        
        scrollContainer->setPosition(CCPointZero);
        CCSize csize = CCSizeMake(tempBg->getContentSize().width * maxRewards,
                                  contentHeight);
        
        scrollContainer->setContentSize(csize);
        
        //SETUP SCROLL VIEW
        CCSize viewsize = CCSizeMake(tempBg->getContentSize().width * displayRewards,
                                     contentHeight);
        scrollView = cocos2d::extension::CCScrollView::create(viewsize, scrollContainer);
        scrollView->setPosition(CCPoint(horizOffset, vertOffset));
        scrollView->setDirection(cocos2d::extension::kCCScrollViewDirectionHorizontal);
        scrollView->setContentOffset(ccp(0.f, 0.f), false);
        scrollView->setAnchorPoint(CCPointZero);
        
        addChild(scrollView);
    }
    
}


int PopUpRewardsLayer::createStringHash(std::string s) {
    
    int hash = 0;
    int offset = 'a' - 1;
    for(std::string::const_iterator it=s.begin(); it!=s.end(); ++it) {
        hash = hash << 1 | (*it - offset);
    }
    
    return hash;
}



void PopUpRewardsLayer::_onOptionPressed(CCObject *pSender)
{
    if(disable)
        return;
    
    CCMenuItem* item = (CCMenuItem*) pSender;
    SimpleAudioEngine::sharedEngine()->playEffect(SFX_BUTTON);
    
    switch (item->getTag()) {

        case kTagTOS:
            std::cout << "PopUpAchievementsLayer: kTagTOS\n";
            CCMessageBox("Terms Of Service", "terms");
            
            
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
            
            
            for (int i = 0; i<rewardDisplays.size(); i++) {
                std::cout << "PopUpAchievementsLayer: cleanup reward Display: " << i << std::endl;
                
                RewardDisplay *rewardDisplay = rewardDisplays[i];
                rewardDisplay->cleanup();
            }
            
            if (_homeLayer != NULL) {
                _homeLayer->_showLayer();
            } else {
                // running in game mode
                GameLayer::sharedInstance()->resumeGame();
            }
            
            //            scheduleOnce(schedule_selector(HomeLayer::_showLayer), 1.0 + 0.1f);
            
            //            SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
            //            CCScene* scene = HomeScene::scene(kGameModeHome);
            //            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
            
            break;
            
    }
}







