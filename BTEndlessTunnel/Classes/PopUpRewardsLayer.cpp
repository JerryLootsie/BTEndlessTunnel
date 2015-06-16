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
        
        _createRewardGUI(0, lootsieReward);
    }
    

    
}

void PopUpRewardsLayer::_createRewardGUI(int rewardIndex, BTLootsieReward *lootsieReward) {
    
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
        
        
        
        // reward title
        cocos2d::CCLabelTTF *rewardTitle = CCLabelTTF::create(lootsieReward->name.c_str(), FONT_GAME, SIZE_RATE_APP, CCSizeMake(visibleSize.width * 0.5f, visibleSize.height * 0.035f), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
        //rewardTitle->setPosition(ccp(origin.x,  (winSize.height/2)));
        //rewardTitle->setPosition(ccp(0, 0));
        rewardTitle->setPosition(ccp((rewardBg->getContentSize().width/2), (rewardBg->getContentSize().height - (rewardTitle->getContentSize().height/2))));
        rewardTitle->setColor(ccWHITE);
        rewardBg->addChild(rewardTitle);

        
        // reward cost string
        std::ostringstream os;
        os << "Cost: " << lootsieReward->lp << "LP";
        std::string mesgStr = os.str();
        const char *rewardCostStr = mesgStr.c_str();
        
        // reward cost label
        cocos2d::CCLabelTTF *rewardCost = CCLabelTTF::create(rewardCostStr, FONT_GAME, SIZE_RATE_APP, CCSizeMake(visibleSize.width * 0.5f, visibleSize.height * 0.035f), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
        rewardCost->setPosition(ccp((rewardBg->getContentSize().width/2), (rewardBg->getContentSize().height * 0.5f)
                                    - (rewardCost->getContentSize().height) ));
        rewardCost->setColor(ccWHITE);
        rewardBg->addChild(rewardCost);
        
        

        if (lootsieReward->imageURL_M.size() > 0) {
            urlToSpriteMap[lootsieReward->imageURL_M] = rewardBg;
            
            downLoadImage((char *)lootsieReward->imageURL_M.c_str(), rewardBg);
        }
        
    }
    
    
    
    // tos button
    CCMenuItem *tosItem  = CCMenuItemImage::create("tos_btn_pristine.png", "tos_btn_hit.png", this, menu_selector(PopUpRewardsLayer::_onOptionPressed_TOS));
    //int rewardIdHash = createStringHash(lootsieReward->reward_id);
    tosItem->setTag(rewardIndex);
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
    CCMenuItem *detailsItem  = CCMenuItemImage::create("details_btn_pristine.png", "details_btn_hit.png", this, menu_selector(PopUpRewardsLayer::_onOptionPressed_Details));
    detailsItem->setTag(rewardIndex);
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
    CCMenuItem *redeemItem  = CCMenuItemImage::create("redeem_btn_small.png", "redeem_btn_small_off.png", this, menu_selector(PopUpRewardsLayer::_onOptionPressed_Redeem));
    redeemItem->setTag(rewardIndex);
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

int PopUpRewardsLayer::createStringHash(std::string s) {
    
    int hash = 0;
    int offset = 'a' - 1;
    for(std::string::const_iterator it=s.begin(); it!=s.end(); ++it) {
        hash = hash << 1 | (*it - offset);
    }
    
    return hash;
}


void PopUpRewardsLayer::downLoadImage(char *imageURL, cocos2d::CCSprite *rewardBg)
{
    //download->setString("downloading.....");
    std::cout << "PopUpRewardsLayer: downLoadImage: " << imageURL << std::endl;
    
    std::string strImage = "img.png";
    cocos2d::extension::CCHttpRequest* request = new cocos2d::extension::CCHttpRequest();
    request->setUrl(imageURL);
    //request->setUrl(URL);
    request->setRequestType(cocos2d::extension::CCHttpRequest::kHttpGet);
    request->setResponseCallback(this, httpresponse_selector(PopUpRewardsLayer::onImageDownLoaded));
    
    // save sprite in hashmap, and reference it later using the tag string
    request->setTag(strImage.c_str());
    
    urlToSpriteMap[strImage] = rewardBg;
    
    cocos2d::extension::CCHttpClient::getInstance()->send(request);
    request->release();
}


void PopUpRewardsLayer::onImageDownLoaded(cocos2d::extension::CCHttpClient* pSender,
                                          cocos2d::extension::CCHttpResponse* pResponse)
{
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    cocos2d::extension::CCHttpResponse* response = pResponse;
    
    if (!response)
    {
        CCLog("No Response");
        return;
    }
    int statusCode = response->getResponseCode();
    
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    CCLog("response code: %d", statusCode);
    
    if (!response->isSucceed())
    {
        CCLog("response failed");
        CCLog("error buffer: %s", response->getErrorBuffer());
        CCMessageBox("error in downloaded", "Image");
        return;
    }
    std::vector<char>*buffer = response->getResponseData();
    
    CCImage * img=new CCImage();
    img->initWithImageData(&(buffer->front()), buffer->size());
    
    //CCMessageBox("Image downloaded", "Image");
    
    // Save image file to device.
    std::string writablePath = CCFileUtils::sharedFileUtils()->getWritablePath();
    writablePath.append(response->getHttpRequest()->getTag());
    img->saveToFile(writablePath.c_str());
    
    // get bg sprite to draw sprite on top of
    if (urlToSpriteMap.find(response->getHttpRequest()->getTag()) != urlToSpriteMap.end()) {
        std::cout << "map contains key URL!\n";

        CCSprite *rewardBg = urlToSpriteMap[response->getHttpRequest()->getTag()];
        
        //Now create Sprite from downloaded image
        CCSprite* pSprite = CCSprite::create(writablePath.c_str());
        float scale = (rewardBg->getContentSize().width * 0.8f)/ pSprite->getContentSize().width;
        pSprite->setScale(scale);
        pSprite->setPosition(ccp(rewardBg->getContentSize().width/2, rewardBg->getContentSize().height * 0.70f));
        rewardBg->cocos2d::CCNode::addChild(pSprite);
        
    } else {
    
        //Now create Sprite from downloaded image
        CCSprite* pSprite = CCSprite::create(writablePath.c_str());
        pSprite->setPosition(ccp(winSize.width/2,winSize.height/2));
        addChild(pSprite);
    }
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
            
            _homeLayer->_showLayer();
            //            scheduleOnce(schedule_selector(HomeLayer::_showLayer), 1.0 + 0.1f);
            
            //            SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
            //            CCScene* scene = HomeScene::scene(kGameModeHome);
            //            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
            
            break;
            
    }
}

void PopUpRewardsLayer::_onOptionPressed_TOS(CCObject *pSender)
{
    if(disable)
        return;
    
    CCMenuItem* item = (CCMenuItem*) pSender;
    SimpleAudioEngine::sharedEngine()->playEffect(SFX_BUTTON);
    
    // tag contains a lookup to reward id in rewards set
    int rewardIndex = item->getTag();
    
    BTLootsieReward *lootsieReward = NULL;
    lootsieReward = lootsieRewards[rewardIndex];
            
    std::cout << "PopUpAchievementsLayer: kTagTOS\n";
    CCMessageBox(lootsieReward->tos_text.c_str(), "Terms Of Service");
    
            
}

void PopUpRewardsLayer::_onOptionPressed_Details(CCObject *pSender)
{
    if(disable)
        return;
    
    CCMenuItem* item = (CCMenuItem*) pSender;
    SimpleAudioEngine::sharedEngine()->playEffect(SFX_BUTTON);
    
    // tag contains a lookup to reward id in rewards set
    int rewardIndex = item->getTag();
    
    BTLootsieReward *lootsieReward = NULL;
    lootsieReward = lootsieRewards[rewardIndex];
    
    std::cout << "PopUpAchievementsLayer: kTagDetails\n";
    CCMessageBox(lootsieReward->reward_description.c_str(), "Details");
    
    
}

void PopUpRewardsLayer::_onOptionPressed_Redeem(CCObject *pSender)
{
    if(disable)
        return;
    
    CCMenuItem* item = (CCMenuItem*) pSender;
    SimpleAudioEngine::sharedEngine()->playEffect(SFX_BUTTON);
    
    // tag contains a lookup to reward id in rewards set
    int rewardIndex = item->getTag();
    
    BTLootsieReward *lootsieReward = NULL;
    lootsieReward = lootsieRewards[rewardIndex];
    
    std::cout << "PopUpAchievementsLayer: redeem\n";
    //CCMessageBox(lootsieReward->reward_description.c_str(), "Redeem");
    
    
    // get bg sprite to draw sprite on top of
    if (urlToSpriteMap.find(lootsieReward->imageURL_M) != urlToSpriteMap.end()) {
        std::cout << "map contains key URL!\n";
        
        CCSprite *rewardBg = urlToSpriteMap[lootsieReward->imageURL_M];
        
        // CCScale9Sprite
        cocos2d::extension::CCEditBox *_editEmail = cocos2d::extension::CCEditBox::create(CCSize(rewardBg->getContentSize().width,
                                                                                               rewardBg->getContentSize().height * .20f),
                                                                                          cocos2d::extension::CCScale9Sprite::create("tos_btn_hit.png"));

        _editEmail->setPosition(ccp(rewardBg->getContentSize().width/2,
                                    rewardBg->getContentSize().height/2));
        _editEmail->setPlaceHolder("Email:");
        _editEmail->setFontSize(SIZE_RATE_APP);
        _editEmail->setFontColor(ccWHITE);
        _editEmail->setMaxLength(80);
        
        _editEmail->setDelegate(this);
        rewardBg->addChild(_editEmail);
        
        
    } else {
        std::cout << "map missing key URL!\n";

    }
    

}

void PopUpRewardsLayer::editBoxEditingDidBegin(cocos2d::extension::CCEditBox *editBox) {
}

void PopUpRewardsLayer::editBoxEditingDidEnd(cocos2d::extension::CCEditBox *editBox) {
    std::cout << "editBoxEditingDidEnd: " << editBox->getText() << std::endl;
}

void PopUpRewardsLayer::editBoxTextChanged(cocos2d::extension::CCEditBox *editBox, std::string &text) {
    
}

void PopUpRewardsLayer::editBoxReturn(cocos2d::extension::CCEditBox *editBox) {
    std::cout << "editBoxReturn: " << editBox->getText() << std::endl;
    
    editBox->setVisible(false);
    
//    editBox->onExit();
    //editBox->onExit();
    //editBox->removeFromParent();
    
//    editBox->getParent()->removeChild(editBox);
}



