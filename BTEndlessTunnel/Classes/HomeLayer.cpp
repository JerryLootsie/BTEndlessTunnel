//
//  HomeLayer.cpp
//  BTEndlessTunnel
//
//  Created by NSS on 4/1/14.
//
//

#include "HomeLayer.h"
#include "NativeUtils.h"
#include "Constants.h"
#include "SimpleAudioEngine.h"
#include "PlayGameConstants.h"
#include "LocalStorageManager.h"
#include "PopupLoseLayer.h"

#define HIDE_TIME 0.4f

using namespace cocos2d;
using namespace CocosDenshion;

static int counter_ads = 0;

// Allocating and initializing HomeLayer
// static data member.  The pointer is being
// allocated - not the object inself.
HomeLayer *HomeLayer::instance = 0;

void HomeLayer::onEnterTransitionDidFinish()
{
    if(_showAds)
    {
        if(counter_ads == 0)
            NativeUtils::showAdBuddiz();
        counter_ads++;
        
        if(counter_ads >= COUNT_ADS)
            counter_ads = 0;
    }
}

HomeLayer::HomeLayer(GameLayer* gameLayer, bool showAds) : _gameLayer(gameLayer)
{
    
    _showAds = false;
    _showAds = showAds;
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(HomeLayer::_enableButtons), NOTIFICATION_ENABLE_BUTTONS, NULL);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(HomeLayer::_manageHowToPlay), NOTIFICATION_HOW_TO_PLAY, NULL);
    
    disable = false;
        
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint visibleOrigin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    // Tablero Izq.
    tablero = CCSprite::create("tablero_title.png");
    tablero->setAnchorPoint(CCPointZero);
    tablero->setPositionX(visibleOrigin.x);
    tablero->setPositionY(visibleOrigin.y);
    addChild(tablero);
    
    // Crear logo
    logo = CCSprite::create("logo.png");
    logo->setPositionX(-logo->getContentSize().width * 1.2f);
    logo->setPositionY(visibleOrigin.y + visibleSize.height * 0.55f);
    
    CCPoint finalPos = ccp(visibleOrigin.x + visibleSize.width * 0.65f, logo->getPositionY());
    CCMoveTo* move1 = CCMoveTo::create(0.9f, finalPos);
    
    logo->runAction(CCSequence::create(CCDelayTime::create(0.25f), move1, NULL));
    
    addChild(logo , -1);
    
    // Achievements
    menuItemAchievements = CCMenuItemImage::create("achievement_off.png", "achievement.png", this, menu_selector(HomeLayer::_onOptionPressed));
    menuItemAchievements->setTag(kTagAchievements);
    menuItemAchievements->setPositionX(visibleOrigin.x + menuItemAchievements->getContentSize().width * 0.8f);
    menuItemAchievements->setPositionY(visibleOrigin.y + menuItemAchievements->getContentSize().height * 0.75f);
    
    // Leaderboards
    menuItemLeaderboard = CCMenuItemImage::create("chart_off.png", "chart.png", this, menu_selector(HomeLayer::_onOptionPressed));
    menuItemLeaderboard->setTag(kTagLeaderboard);
    menuItemLeaderboard->setPositionX(menuItemAchievements->getPositionX() + menuItemAchievements->getContentSize().width * 1.2f);
    menuItemLeaderboard->setPositionY(menuItemAchievements->getPositionY());
    
    float scale = 1.05f;
    float time_dt = 1.3f;
    
    // Hard Mode
    menuItemHard = CCMenuItemImage::create("hard_off.png", "hard.png", this, menu_selector(HomeLayer::_onOptionPressed));
    menuItemHard->setTag(kTagHardMode);
    menuItemHard->setAnchorPoint(ccp(0, 0));
    menuItemHard->setPositionX(menuItemAchievements->getPositionX() - menuItemAchievements->getContentSize().width * 0.5f);
    menuItemHard->setPositionY(menuItemAchievements->getPositionY() + menuItemAchievements->getContentSize().height * 0.75f);
    menuItemHard->setRotation(-3);
    menuItemHard->runAction(CCRepeatForever::create(CCSequence::create(CCDelayTime::create(2 * time_dt), CCScaleTo::create(0.5f * time_dt, scale), CCScaleTo::create(0.5f * time_dt, 1.0f), CCDelayTime::create(0), NULL)));
    
    float dtHeight = 1.35f;
    if(visibleSize.height >= 768)
        dtHeight = 1.7f;
    
    // Normal Mode
    menuItemNormal = CCMenuItemImage::create("medium_off.png", "medium.png", this, menu_selector(HomeLayer::_onOptionPressed));
    menuItemNormal->setTag(kTagNormalMode);
    menuItemNormal->setAnchorPoint(ccp(0, 0));
    menuItemNormal->setPositionX(menuItemHard->getPositionX());
    menuItemNormal->setPositionY(menuItemHard->getPositionY() + menuItemAchievements->getContentSize().height * dtHeight);
    menuItemNormal->setRotation(-2);
    menuItemNormal->runAction(CCRepeatForever::create(CCSequence::create(CCDelayTime::create(1 * time_dt), CCScaleTo::create(0.5f * time_dt, scale), CCScaleTo::create(0.5f * time_dt, 1.0f), CCDelayTime::create(1 * time_dt), NULL)));
    
    // Easy Mode
    menuItemEasy = CCMenuItemImage::create("easy_off.png", "easy.png", this, menu_selector(HomeLayer::_onOptionPressed));
    menuItemEasy->setTag(kTagEasyMode);
    menuItemEasy->setAnchorPoint(ccp(0, 0));
    menuItemEasy->setPositionX(menuItemNormal->getPositionX());
    menuItemEasy->setPositionY(menuItemNormal->getPositionY() + menuItemAchievements->getContentSize().height * dtHeight);
    menuItemEasy->setRotation(-2);
    menuItemEasy->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(0.5f * time_dt, scale), CCScaleTo::create(0.5f * time_dt, 1.0f), CCDelayTime::create(2 * time_dt), NULL)));
    
    // Settings
    menuItemSettings = CCMenuItemImage::create("ajustes_off.png", "ajustes.png", this, menu_selector(HomeLayer::_onOptionPressed));
    menuItemSettings->setTag(kTagSettings);
    menuItemSettings->setPosition(ccp(visibleSize.width - menuItemSettings->getContentSize().width * 0.8f, visibleOrigin.y + menuItemSettings->getContentSize().height * 0.7f));
    
    // Rate App
    CCLabelTTF* lblRateApp = CCLabelTTF::create("Rate this App!", FONT_GAME, SIZE_RATE_APP);
    lblRateApp->setColor(ccWHITE);
    
    menuRateApp = CCMenuItemLabel::create(lblRateApp, this, menu_selector(HomeLayer::_onOptionPressed));
    menuRateApp->setTag(kTagRateApp);
    menuRateApp->setPositionX(visibleOrigin.x + visibleSize.width * 0.75f);
    menuRateApp->setPositionY(visibleOrigin.y + menuRateApp->getContentSize().height * 2.2f);
    menuRateApp->runAction(CCRepeatForever::create(CCSequence::create(CCRotateTo::create(0.5f, -2), CCRotateTo::create(0.5f, 2), NULL)));
    
    // How to Player
    CCLabelTTF* lblHowToPlay = CCLabelTTF::create("How to Play", FONT_GAME, SIZE_RATE_APP);
    lblHowToPlay->setColor(ccWHITE);
    
    menuHowToPlay = CCMenuItemLabel::create(lblHowToPlay, this, menu_selector(HomeLayer::_onOptionPressed));
    menuHowToPlay->setTag(kTagHowToPlay);
    menuHowToPlay->setPositionX(menuRateApp->getPositionX() - menuHowToPlay->getContentSize().width * 1.3f);
    menuHowToPlay->setPositionY(menuRateApp->getPositionY());
    menuHowToPlay->runAction(CCRepeatForever::create(CCSequence::create(CCRotateTo::create(0.5f, -2), CCRotateTo::create(0.5f, 2), NULL)));
    
    if(LocalStorageManager::showTutorial())
        menuHowToPlay->setVisible(false);
    
    // Sound management
    CCMenuItemImage* menuSoundOn = CCMenuItemImage::create("sound_on_off.png", "sound_on.png", NULL, NULL);
    CCMenuItemImage* menuSoundOff = CCMenuItemImage::create("sound_off_off.png", "sound_off.png", NULL, NULL);
    
    menuSound = CCMenuItemToggle::createWithTarget(this, menu_selector(HomeLayer::_manageMusic), menuSoundOn, menuSoundOff, NULL);
    menuSound->setPositionX(menuItemLeaderboard->getPositionX() + menuItemAchievements->getContentSize().width * 1.2f);
    menuSound->setPositionY(menuItemLeaderboard->getPositionY());
    
    if(LocalStorageManager::isMute())
        menuSound->setSelectedIndex(1);
    
    // Menu
    menu = CCMenu::create();
    menu->setPosition(CCPointZero);
    menu->addChild(menuItemEasy);
    menu->addChild(menuItemNormal);
    menu->addChild(menuItemHard);
    menu->addChild(menuItemLeaderboard);
    menu->addChild(menuItemAchievements);
    menu->addChild(menuItemSettings);
    menu->addChild(menuSound);
    menu->addChild(menuRateApp);
    menu->addChild(menuHowToPlay);
    
    addChild(menu);
    
    _settingsLayer = new SettingsLayer();
    _settingsLayer->autorelease();
    _settingsLayer->setVisible(false);
    addChild(_settingsLayer, 9999);
    
    // testing popuploselayer
//    _popUpLoseLayer = new PopUpLoseLayer();
//    //_popUpLoseLayer->setPosition(ccp(0, -WIN_SIZE.height));
//    _popUpLoseLayer->setPositionY(0);
//    _popUpLoseLayer->setVisible(false);
//    _popUpLoseLayer->autorelease();
//    addChild(_popUpLoseLayer, 10000);
    
    // testing _popUpAchievementsLayer
    _popUpAchievementsLayer = new PopUpAchievementsLayer();
    _popUpAchievementsLayer->setPositionY(0);
    _popUpAchievementsLayer->setVisible(false);
    _popUpAchievementsLayer->autorelease();
    _popUpAchievementsLayer->_setHomeLayer(this);
    addChild(_popUpAchievementsLayer, 10000);
    
    NativeUtils::showAd();
    
    HomeLayer::instance = this;
}

#pragma mark - Singleton
//HomeLayer& HomeLayer::sharedInstance()
HomeLayer* HomeLayer::sharedInstance()
{
    return instance;
}

void HomeLayer::_manageMusic(cocos2d::CCObject* pSender)
{
    if(disable || _settingsLayer->isVisible())
        return;
    
    SimpleAudioEngine::sharedEngine()->playEffect(SFX_BUTTON);
    
    bool state = LocalStorageManager::isMute();
    LocalStorageManager::setMute(!state);
}

HomeLayer::~HomeLayer()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NOTIFICATION_ENABLE_BUTTONS);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NOTIFICATION_HOW_TO_PLAY);
}

void HomeLayer::_onOptionPressed(CCObject *pSender)
{
    if(disable || _settingsLayer->isVisible())
        return;
    
    SimpleAudioEngine::sharedEngine()->playEffect(SFX_BUTTON);
    
    CCMenuItem* item = (CCMenuItem*) pSender;
    bool runGame = false;
    
    switch (item->getTag()) {
            
        case kTagHowToPlay:
            std::cout << "HomeLayer: show HowToPlay\n";
            NativeUtils::sendAnalytics("How to Play");
            LocalStorageManager::isTutorialOn(true);
            runGame = true;
            _gameLayer->configureGame(kGameLevelEasy);
            break;
        
        case kTagEasyMode:
            runGame = true;
            std::cout << "HomeLayer: show Easy Mode\n";
            NativeUtils::sendAnalytics("Easy Mode");
            _gameLayer->configureGame(kGameLevelEasy);
            break;
            
        case kTagNormalMode:
            runGame = true;
            std::cout << "HomeLayer: show Normal Mode\n";
            NativeUtils::sendAnalytics("Normal Mode");
            _gameLayer->configureGame(kGameLevelNormal);
            break;
            
        case kTagHardMode:
            runGame = true;
            std::cout << "HomeLayer: show Hard Mode\n";
            NativeUtils::sendAnalytics("Hard Mode");
            _gameLayer->configureGame(kGameLevelHard);
            break;
            
        case kTagSettings:
            _disableButtons();
            std::cout << "HomeLayer: show Settings\n";
            NativeUtils::sendAnalytics("Settings");
            _settingsLayer->setVisible(true);
            break;
            
        case kTagLeaderboard:
            std::cout << "HomeLayer: show Leaderboards\n";
            NativeUtils::sendAnalytics("Show Leaderboards");
            NativeUtils::showLeaderboards();
            break;
            
        case kTagAchievements:
            std::cout << "HomeLayer: show achievments\n";
            
            //NativeUtils::showAchievements();
            NativeUtils::getAchievements();
            
            // this can also happen in AppController.mm in init callback
            
            // classes/layers/HomeLayer.cpp (kTagAchievements) ->
            // classes/helpers/ NativeUtils::getAchievements() ->
            // PlayGameSingleton::sharedInstance().getAchievements() ->
            // LootsieManager::getAchievements(); ->
            // HomeLayer::sharedInstance()->_showPopUpAchievementsLayer

            //_showPopUpAchievementsLayer();

            
            break;
            
        case kTagRateApp:
            std::cout << "HomeLayer: show Rate App\n";
            NativeUtils::sendAnalytics("Rate App");
            NativeUtils::rateApp();
            break;
            
        default:
            break;
    }
    
    if(runGame)
    {
        _disableButtons();
        NativeUtils::hideAd();
        disable = true;
        _hideToLeft();
        _hideToRight();
        scheduleOnce(schedule_selector(HomeLayer::_finishHideLayer), HIDE_TIME + 0.1f);
    }
    
}

void HomeLayer::_showPopUpAchievementsLayer(std::vector<BTLootsieAchievement*> lootsieAchievments)
{
    std::cout << "HomeLayer: _showPopUpAchievementsLayer: " << lootsieAchievments.size() << std::endl;
    
    // normally setting runGame to true => will kick off finish and hide layer
    _disableButtons();
    disable = true;
    _hideToLeft();
    _hideToRight();
    
    scheduleOnce(schedule_selector(HomeLayer::_finishHideLayerDontStartGame), HIDE_TIME + 0.1f);
    
    _popUpAchievementsLayer->_setAchievments(lootsieAchievments);
    _popUpAchievementsLayer->setVisible(true);
    
}

void HomeLayer::_hideToLeft()
{
    CCMoveBy* move = CCMoveBy::create(HIDE_TIME, ccp(-WIN_SIZE.width * 0.8f, 0));
    tablero->runAction((CCAction*) move->copy()->autorelease());
    menuItemEasy->runAction((CCAction*) move->copy()->autorelease());
    menuItemNormal->runAction((CCAction*) move->copy()->autorelease());
    menuItemHard->runAction((CCAction*) move->copy()->autorelease());
    menuItemAchievements->runAction((CCAction*) move->copy()->autorelease());
    menuItemLeaderboard->runAction((CCAction*) move->copy()->autorelease());
    menuSound->runAction((CCAction*) move->copy()->autorelease());
}

void HomeLayer::_unhideFromLeft()
{
    CCMoveBy* move = CCMoveBy::create(HIDE_TIME, ccp(+WIN_SIZE.width * 0.8f, 0));
    tablero->runAction((CCAction*) move->copy()->autorelease());
    menuItemEasy->runAction((CCAction*) move->copy()->autorelease());
    menuItemNormal->runAction((CCAction*) move->copy()->autorelease());
    menuItemHard->runAction((CCAction*) move->copy()->autorelease());
    menuItemAchievements->runAction((CCAction*) move->copy()->autorelease());
    menuItemLeaderboard->runAction((CCAction*) move->copy()->autorelease());
    menuSound->runAction((CCAction*) move->copy()->autorelease());
}


void HomeLayer::_hideToRight()
{
    CCMoveBy* move = CCMoveBy::create(HIDE_TIME, ccp(WIN_SIZE.width * 0.8f, 0));
    menuItemSettings->runAction((CCAction*) move->copy()->autorelease());
    menuRateApp->runAction((CCAction*) move->copy()->autorelease());
    menuHowToPlay->runAction((CCAction*) move->copy()->autorelease());
    logo->runAction((CCAction*) move->copy()->autorelease());
}

void HomeLayer::_unhideFromRight()
{
    CCMoveBy* move = CCMoveBy::create(HIDE_TIME, ccp(-WIN_SIZE.width * 0.8f, 0));
    menuItemSettings->runAction((CCAction*) move->copy()->autorelease());
    menuRateApp->runAction((CCAction*) move->copy()->autorelease());
    menuHowToPlay->runAction((CCAction*) move->copy()->autorelease());
    logo->runAction((CCAction*) move->copy()->autorelease());
}

void HomeLayer::_finishHideLayer()
{
    this->setVisible(false);
    _gameLayer->playGame();
    this->removeFromParent();    
}

void HomeLayer::_finishHideLayerDontStartGame()
{
//    this->setVisible(false);
//    this->removeFromParent();
}

void HomeLayer::_showLayer() {
    std::cout << "HomeLayer: _showLayer\n";
    
    _enableButtons();
    disable = false;
    _unhideFromLeft();
    _unhideFromRight();
    
    this->setVisible(true);
}


void HomeLayer::_enableButtons()
{
    CCObject* object;
    CCARRAY_FOREACH(menu->getChildren(), object)
    {
        CCMenuItem* item = (CCMenuItem*) object;
        item->setEnabled(true);
    }
}

void HomeLayer::_disableButtons()
{
    CCObject* object;
    CCARRAY_FOREACH(menu->getChildren(), object)
    {
        CCMenuItem* item = (CCMenuItem*) object;
        item->setEnabled(false);
    }
}

void HomeLayer::_manageHowToPlay()
{
    bool state = !LocalStorageManager::showTutorial();
    menuHowToPlay->setVisible(state);
}
