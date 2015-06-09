//
//  PopUpAchievementsLayer.h
//  BTEndlessTunnel
//
//  Created by Jerry Lootsie on 6/5/15.
//
//

#ifndef __BTEndlessTunnel__PopUpAchievementsLayer__
#define __BTEndlessTunnel__PopUpAchievementsLayer__

#include <vector>
#include "cocos2d.h"
#include "cocos-ext.h"
//#include "HomeLayer.h"

class HomeLayer;

//enum PopUpAchievementsButtons
//{
//    kTagPlayAgain = 0,
//    kTagGoHome = 1,
//    kTagSendScore = 2
//};

class AchievementLine {
    
public:
    cocos2d::CCSprite* _spTrophy;
    cocos2d::CCLabelTTF* _lblAchievement1;
    cocos2d::CCLabelTTF* _lblAchievementPoints1;
};


class PopUpAchievementsLayer : public cocos2d::CCLayerColor
{
public:
    PopUpAchievementsLayer();
//    void updateScore(int level, float score, int obstaclesAvoided);
    void _setHomeLayer(HomeLayer *inputLayer);
    
    cocos2d::extension::CCScrollView *scrollView;
    cocos2d::CCSprite *background1;
    cocos2d::CCSprite *background2;
    cocos2d::CCLayer *scrollContainer;
    
    
    
private:
    void _onOptionPressed(cocos2d::CCObject* pSender);
    void _finishHideLayer();
    
    void _createAchievementScreens();
//    void _addAchievementEntries(cocos2d::CCSprite* bgSprite, int rotationOffset);
    void _addAchievementEntries(cocos2d::CCNode* bgSprite, int rotationOffset);
    void _createScrollView();
    void _createScrollView2();
    void _createScrollView3();
    
private:
    const char* _leaderboardID;
    
    int _obstaclesAvoided;
    int _level;
    long _score;

    HomeLayer *_homeLayer;
    
    cocos2d::CCLabelTTF* _lblTitle;
    
    //AchievementLine *achievementEntries;
    AchievementLine **achievementEntries;

    
    //std::vector< std::vector< AchievementLine > > AchievementLineVector;

    
    
//    cocos2d::CCLabelTTF* _lblScore;
//    cocos2d::CCLabelTTF* _lblMaxScore;
//    cocos2d::CCSprite* spBadge;
    bool disable;
};
#endif /* defined(__BTEndlessTunnel__PopUpAchievementsLayer__) */
