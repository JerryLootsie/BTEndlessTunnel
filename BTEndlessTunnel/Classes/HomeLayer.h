//
//  HomeLayer.h
//  BTEndlessTunnel
//
//  Created by NSS on 4/1/14.
//
//

#ifndef __BTEndlessTunnel__HomeLayer__
#define __BTEndlessTunnel__HomeLayer__

#include "cocos2d.h"
#include "GameLayer.h"
#include "SettingsLayer.h"
#include "PopUpAchievementsLayer.h"
#include "PopUpRewardsLayer.h"

enum HomeButtons
{
    kTagEasyMode = 0,
    kTagNormalMode = 1,
    kTagHardMode = 2,
    kTagRateApp = 3,
    kTagLeaderboard = 4,
    kTagAchievements = 5,
    kTagSettings = 6,
    kTagHowToPlay = 7,
    kTagRewards = 8
};

class HomeLayer : public cocos2d::CCLayer
{
public:
    //static HomeLayer& sharedInstance();
    static HomeLayer* sharedInstance();
    
    HomeLayer(GameLayer* gameLayer, bool showAds = false);
    virtual ~HomeLayer();
    void onEnterTransitionDidFinish();
    
    void _showLayer();
    
    void _showPopUpAchievementsLayer(std::vector<BTLootsieAchievement*> lootsieAchievments);
    void _showPopUpRewardsLayer(std::vector<BTLootsieReward*> lootsieRewards);
    
private:
    static HomeLayer* instance;
    //static HomeLayer instance;
    
    cocos2d::CCSprite* tablero;
    cocos2d::CCSprite* logo;
    cocos2d::CCMenuItemImage* menuItemEasy;
    cocos2d::CCMenuItemImage* menuItemNormal;
    cocos2d::CCMenuItemImage* menuItemHard;
    cocos2d::CCMenuItemImage* menuItemAchievements;
//    cocos2d::CCMenuItemImage* menuItemLeaderboard;
    cocos2d::CCMenuItemImage* menuItemRewards;
    cocos2d::CCMenuItemImage* menuItemSettings;
    cocos2d::CCMenuItemLabel* menuRateApp;
    cocos2d::CCMenuItemLabel* menuHowToPlay;
    cocos2d::CCMenuItemToggle* menuSound;
    
private:
    void _onOptionPressed(cocos2d::CCObject* pSender);
    void _finishHideLayer();
    void _finishHideLayerDontStartGame();
    
    
    
    void _manageMusic(cocos2d::CCObject* pSender);
    
    void _hideToLeft();
    void _hideToRight();
    
    void _unhideFromLeft();
    void _unhideFromRight();
    
    void _enableButtons();
    void _disableButtons();
    
    void _manageHowToPlay();
    
private:
    bool _showAds;
    bool disable;
    GameLayer* _gameLayer;
    SettingsLayer* _settingsLayer;
    
//    PopUpLoseLayer* _popUpLoseLayer;
    PopUpAchievementsLayer* _popUpAchievementsLayer;
    PopUpRewardsLayer* _popUpRewardsLayer;
    
    cocos2d::CCMenu* menu;
};

#endif /* defined(__BTEndlessTunnel__HomeLayer__) */
