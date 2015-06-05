//
//  PopUpAchievementsLayer.h
//  BTEndlessTunnel
//
//  Created by Jerry Lootsie on 6/5/15.
//
//

#ifndef __BTEndlessTunnel__PopUpAchievementsLayer__
#define __BTEndlessTunnel__PopUpAchievementsLayer__

#include "cocos2d.h"
//#include "HomeLayer.h"

class HomeLayer;

//enum PopUpAchievementsButtons
//{
//    kTagPlayAgain = 0,
//    kTagGoHome = 1,
//    kTagSendScore = 2
//};

class PopUpAchievementsLayer : public cocos2d::CCLayerColor
{
public:
    PopUpAchievementsLayer();
//    void updateScore(int level, float score, int obstaclesAvoided);
    void _setHomeLayer(HomeLayer *inputLayer);
    
private:
    void _onOptionPressed(cocos2d::CCObject* pSender);
    void _finishHideLayer();
    

    
private:
    const char* _leaderboardID;
    
    int _obstaclesAvoided;
    int _level;
    long _score;

    HomeLayer *_homeLayer;
    
    
    cocos2d::CCLabelTTF* _lblTitle;
    
    cocos2d::CCLabelTTF* _lblScore;
    cocos2d::CCLabelTTF* _lblMaxScore;
    cocos2d::CCSprite* spBadge;
    bool disable;
};
#endif /* defined(__BTEndlessTunnel__PopUpAchievementsLayer__) */
