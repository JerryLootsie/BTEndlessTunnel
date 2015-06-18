//
//  RewardDisplay.cpp
//  BTEndlessTunnel
//
//  Created by Jerry Lootsie on 6/16/15.
//
//

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

//RewardDisplay::RewardDisplay(cocos2d::CCLayerColor *inputLayer, BTLootsieReward *inputLootsieReward, int inputRewardIndex)
RewardDisplay::RewardDisplay(cocos2d::CCLayer *inputLayer, BTLootsieReward *inputLootsieReward, int inputRewardIndex)
{
    std::cout << "RewardDisplay: " << inputRewardIndex << std::endl;
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint visibleOrigin = CCDirector::sharedDirector()->getVisibleOrigin();
//    CCPoint origin = ccp(visibleOrigin.x + visibleSize.width * 0.5f, visibleOrigin.y + visibleSize.height* 0.5f);
//    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    rewardIndex = inputRewardIndex;
    
    layer = inputLayer;
    lootsieReward = inputLootsieReward;
    
    // cover up the background behind the scrollable area
    rewardBg = CCSprite::create("reward_bg.png");
//    rewardBg->setPosition(ccp((rewardBg->getContentSize().width * 0.5f) + (rewardBg->getContentSize().width * rewardIndex),
//                              rewardBg->getContentSize().height* 0.5f));
    rewardBg->setPosition(ccp((rewardBg->getContentSize().width * 0.5f) + (rewardBg->getContentSize().width * rewardIndex),
                              rewardBg->getContentSize().height* 0.7f));
    rewardBg->retain();

    rewardImage = NULL;
    
    // title
    if (lootsieReward != NULL) {
        std::cout << "PopUpRewardsLayer: reward: " << lootsieReward->name << std::endl;
        
        //float textHeightMultiplier = 0.035f;
        float textHeightMultiplier = 0.05f;
        
        // reward title
        rewardTitle = CCLabelTTF::create(lootsieReward->name.c_str(), FONT_GAME, SIZE_RATE_APP,
                                         CCSizeMake(visibleSize.width * 0.5f, visibleSize.height * textHeightMultiplier),
                                         kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
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
        rewardCost = CCLabelTTF::create(rewardCostStr, FONT_GAME, SIZE_RATE_APP,
                                        CCSizeMake(visibleSize.width * 0.5f, visibleSize.height * textHeightMultiplier),
                                        kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
        rewardCost->setPosition(ccp((rewardBg->getContentSize().width/2), (rewardBg->getContentSize().height * 0.5f)
                                                   - (rewardCost->getContentSize().height) ));
        rewardCost->setColor(ccWHITE);
        rewardBg->addChild(rewardCost);
        
        
        
        if (lootsieReward->imageURL_M.size() > 0) {
            PopUpRewardsLayer::sharedInstance()->urlToSpriteMap[lootsieReward->imageURL_M] = rewardBg;
            
            
            // reward cost string
            std::ostringstream os;
            os << "image_" << rewardIndex << ".png";
            std::string imageStr = os.str();
            const char *imageCharStr = imageStr.c_str();
            
            downLoadImage((char *)lootsieReward->imageURL_M.c_str(), rewardBg, imageCharStr);
        }
        
    }
    
    
    
    // tos button
    tosItem = cocos2d::CCMenuItemImage::create("tos_btn_pristine.png", "tos_btn_hit.png", layer, menu_selector(RewardDisplay::_onOptionPressed_TOS));
    //int rewardIdHash = createStringHash(lootsieReward->reward_id);
    tosItem->setTag(rewardIndex);
    //tosItem->setAnchorPoint(ccp(0, 0));
    tosItem->setAnchorPoint(ccp(0.5, 0.5));
//    tosItem->setPosition(ccp((rewardBg->getContentSize().width/2) + (tosItem->getContentSize().width),
//                            (tosItem->getContentSize().height*1.2)));
    tosItem->setPosition(ccp((rewardBg->getContentSize().width/2) - (tosItem->getContentSize().width),
                             (tosItem->getContentSize().height*1.2)));

    
    tosItem->retain();
    
    
    tosLabel = CCLabelTTF::create("TOS", FONT_GAME, SIZE_RATE_APP);
    tosLabel->setAnchorPoint(ccp(0.5, 0.5));
    tosLabel->setPosition(ccp((tosItem->getContentSize().width/2), (tosItem->getContentSize().height/2)));
    tosLabel->setColor(ccBLACK);
    tosItem->addChild(tosLabel);
    
    
    
    // details button
    detailsItem  = CCMenuItemImage::create("details_btn_pristine.png", "details_btn_hit.png", layer, menu_selector(RewardDisplay::_onOptionPressed_Details));
    detailsItem->setTag(rewardIndex);
    //        detailsItem->setAnchorPoint(ccp(0, 0));
    detailsItem->setAnchorPoint(ccp(0.5, 0));
//    detailsItem->setPosition(ccp((rewardBg->getContentSize().width/2) - (detailsItem->getContentSize().width),
//                                 (detailsItem->getContentSize().height*1.2)));
    detailsItem->setPosition(ccp((rewardBg->getContentSize().width/2) + (detailsItem->getContentSize().width),
                                 (detailsItem->getContentSize().height*1.2)));
    detailsItem->retain();
    
    
    detailsLabel = CCLabelTTF::create("DETAILS", FONT_GAME, SIZE_RATE_APP);
    detailsLabel->setAnchorPoint(ccp(0.5, 0.5));
    detailsLabel->setPosition(ccp((detailsItem->getContentSize().width/2), (detailsItem->getContentSize().height/2)));
    detailsLabel->setColor(ccBLACK);
    detailsItem->addChild(detailsLabel);
    
    
    
    // redeem button
    redeemItem = CCMenuItemImage::create("redeem_btn_small.png", "redeem_btn_small_off.png", layer, menu_selector(RewardDisplay::_onOptionPressed_Redeem));
    redeemItem->setTag(rewardIndex);
    redeemItem->setAnchorPoint(ccp(0, 0));
    redeemItem->setPosition(ccp((rewardBg->getContentSize().width/2) - (redeemItem->getContentSize().width/2),
                                (detailsItem->getContentSize().height* -0.25f)
                                ));
    
    redeemItem->retain();
    
    
    redeemLabel = CCLabelTTF::create("REDEEM", FONT_GAME, SIZE_RATE_APP);
    redeemLabel->setAnchorPoint(ccp(0.5, 0.5));
    redeemLabel->setPosition(ccp((redeemItem->getContentSize().width/2), (redeemItem->getContentSize().height/2)));
    redeemLabel->setColor(ccBLACK);
    redeemItem->addChild(redeemLabel);
    
    // menu
    rewardMenu = CCMenu::create();
    rewardMenu->setAnchorPoint(ccp(0, 0));
    rewardMenu->setPosition(CCPointZero);
    
    rewardMenu->addChild(tosItem);
    rewardMenu->addChild(detailsItem);
    rewardMenu->addChild(redeemItem);
    
//    layer->addChild(rewardMenu);
    rewardBg->addChild(rewardMenu);
    layer->addChild(rewardBg);
    
    
}

void RewardDisplay::cleanup() {
    if (rewardImage != NULL) {
        rewardImage->removeFromParentAndCleanup(false);
    }
    
    rewardTitle->removeFromParentAndCleanup(true);
    rewardCost->removeFromParentAndCleanup(true);
    
    tosLabel->removeFromParentAndCleanup(true);
    tosItem->removeFromParentAndCleanup(true);
    
    detailsLabel->removeFromParentAndCleanup(true);
    detailsItem->removeFromParentAndCleanup(true);
    
    redeemLabel->removeFromParentAndCleanup(true);
    redeemItem->removeFromParentAndCleanup(true);
    
    rewardMenu->removeFromParentAndCleanup(true);
    rewardBg->removeFromParentAndCleanup(true);
    
}

void RewardDisplay::downLoadImage(char *imageURL, cocos2d::CCSprite *rewardBg, std::string strImage)
{
    //download->setString("downloading.....");
    std::cout << "RewardDisplay: downLoadImage: " << imageURL << std::endl;
    
//    std::string strImage = "img.png";
    cocos2d::extension::CCHttpRequest* request = new cocos2d::extension::CCHttpRequest();
    request->setUrl(imageURL);
    //request->setUrl(URL);
    request->setRequestType(cocos2d::extension::CCHttpRequest::kHttpGet);
    request->setResponseCallback(layer, httpresponse_selector(RewardDisplay::onImageDownLoaded));
    
    // save sprite in hashmap, and reference it later using the tag string
    request->setTag(strImage.c_str());
    
    PopUpRewardsLayer::sharedInstance()->urlToSpriteMap[strImage] = rewardBg;
    
    cocos2d::extension::CCHttpClient::getInstance()->send(request);
    request->release();
}


void RewardDisplay::onImageDownLoaded(cocos2d::extension::CCHttpClient* pSender,
                                          cocos2d::extension::CCHttpResponse* pResponse)
{
//    CCSize winSize=CCDirector::sharedDirector()->getWinSize();
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
    CCLog("status: %s", statusString);
    
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
    std::cout << "onImageDownLoaded: response tag: " << response->getHttpRequest()->getTag() << std::endl;
    if (PopUpRewardsLayer::sharedInstance()->urlToSpriteMap.find(response->getHttpRequest()->getTag()) != PopUpRewardsLayer::sharedInstance()->urlToSpriteMap.end()) {
        //std::cout << "onImageDownLoaded: map contains key URL!\n";
        
        CCSprite *rewardBg = PopUpRewardsLayer::sharedInstance()->urlToSpriteMap[response->getHttpRequest()->getTag()];
        
        //Now create Sprite from downloaded image
        rewardImage = CCSprite::create(writablePath.c_str());
        
//        std::cout << "onImageDownLoaded: rewardImage: " << rewardImage->getContentSize().width << "x" << rewardImage->getContentSize().height << std::endl;
//        std::cout << "onImageDownLoaded: rewardBg: " << rewardBg->getContentSize().width << "x" << rewardBg->getContentSize().height << std::endl;

        // calculate scale to make reward image fit
        float scale = 1.0f;
        float scaleWidth = (rewardBg->getContentSize().width * 0.8f)/ rewardImage->getContentSize().width;
        float scaleHeight = (rewardBg->getContentSize().height * 0.43f)/ rewardImage->getContentSize().height;
        scale = MIN(scaleWidth, scaleHeight);
        rewardImage->setScale(scale);
        
        rewardImage->setPosition(ccp(rewardBg->getContentSize().width/2, rewardBg->getContentSize().height * 0.70f));
        rewardBg->cocos2d::CCNode::addChild(rewardImage);
        
    } else {
        std::cout << "onImageDownLoaded: map can't find background sprite to place downloaded image!" << std::endl;
        //Now create Sprite from downloaded image
//        CCSprite* pSprite = CCSprite::create(writablePath.c_str());
//        pSprite->setPosition(ccp(winSize.width/2,winSize.height/2));
//        addChild(pSprite);
    }
}



void RewardDisplay::_onOptionPressed_TOS(CCObject *pSender)
{
//    if(disable)
//        return;
    
    CCMenuItem* item = (CCMenuItem*) pSender;
    SimpleAudioEngine::sharedEngine()->playEffect(SFX_BUTTON);
    
    // tag contains a lookup to reward id in rewards set
    int rewardIndex = item->getTag();
    lootsieReward = PopUpRewardsLayer::sharedInstance()->lootsieRewards[rewardIndex];
    
    std::cout << "RewardDisplay: TOS\n";
    CCMessageBox(lootsieReward->tos_text.c_str(), "Terms Of Service");
    
    
}

void RewardDisplay::_onOptionPressed_Details(CCObject *pSender)
{
//    if(disable)
//        return;
    
    CCMenuItem* item = (CCMenuItem*) pSender;
    SimpleAudioEngine::sharedEngine()->playEffect(SFX_BUTTON);
    
    // tag contains a lookup to reward id in rewards set
    int rewardIndex = item->getTag();
    lootsieReward = PopUpRewardsLayer::sharedInstance()->lootsieRewards[rewardIndex];
    
    std::cout << "RewardDisplay: Details\n";
    CCMessageBox(lootsieReward->reward_description.c_str(), "Details");
    
    
}

void RewardDisplay::_onOptionPressed_Redeem(CCObject *pSender)
{
//    if(disable)
//        return;
    
    CCMenuItem* item = (CCMenuItem*) pSender;
    SimpleAudioEngine::sharedEngine()->playEffect(SFX_BUTTON);
    
    // tag contains a lookup to reward id in rewards set
    int rewardIndex = item->getTag();
    lootsieReward = PopUpRewardsLayer::sharedInstance()->lootsieRewards[rewardIndex];
    
    std::cout << "RewardDisplay: redeem\n";
    //CCMessageBox(lootsieReward->reward_description.c_str(), "Redeem");
    
    
    // get bg sprite to draw sprite on top of
    if (PopUpRewardsLayer::sharedInstance()->urlToSpriteMap.find(lootsieReward->imageURL_M) != PopUpRewardsLayer::sharedInstance()->urlToSpriteMap.end()) {
        std::cout << "map contains key URL!\n";
        
        CCSprite *rewardBg = PopUpRewardsLayer::sharedInstance()->urlToSpriteMap[lootsieReward->imageURL_M];
        
        // hide other buttons
        RewardDisplay *rewardDisplay = PopUpRewardsLayer::sharedInstance()->rewardDisplays[rewardIndex];
        rewardDisplay->tosItem->setVisible(false);
        rewardDisplay->detailsItem->setVisible(false);
        rewardDisplay->redeemItem->setVisible(false);
        
        
        RewardDisplay *localRewardDisplay = PopUpRewardsLayer::sharedInstance()->rewardDisplays[rewardIndex];
        
        // CCScale9Sprite
        _editEmail = cocos2d::extension::CCEditBox::create(CCSize(rewardBg->getContentSize().width,
                                                                  rewardBg->getContentSize().height * .20f),
                                                            cocos2d::extension::CCScale9Sprite::create("tos_btn_hit.png"));
        
        _editEmail->setPosition(ccp(rewardBg->getContentSize().width/2,
                                    rewardBg->getContentSize().height * 0.40));
        _editEmail->setPlaceHolder("Email:");
        _editEmail->setFontSize(SIZE_RATE_APP);
        _editEmail->setFontColor(ccBLACK);
        _editEmail->setMaxLength(80);
        _editEmail->setInputMode(cocos2d::extension::kEditBoxInputModeEmailAddr);
        _editEmail->setReturnType(cocos2d::extension::kKeyboardReturnTypeDone);
        _editEmail->setTag(rewardIndex);
        
        
        _editEmail->setDelegate(localRewardDisplay);
        rewardBg->addChild(_editEmail);
        
        localRewardDisplay->_editEmail = _editEmail;
        
        // redeem button
        sendRewardItem = CCMenuItemImage::create("redeem_btn_small.png", "redeem_btn_small_off.png", layer, menu_selector(RewardDisplay::_onOptionPressed_Submit));
        sendRewardItem->setTag(rewardIndex);
        sendRewardItem->setAnchorPoint(ccp(0, 0));
        sendRewardItem->setPosition(ccp((rewardBg->getContentSize().width/2) - (sendRewardItem->getContentSize().width/2),
                                    (sendRewardItem->getContentSize().height* -0.25f)
                                    ));
        
        sendRewardLabel = CCLabelTTF::create("Send Reward", FONT_GAME, SIZE_RATE_APP);
        sendRewardLabel->setAnchorPoint(ccp(0.5, 0.5));
        sendRewardLabel->setPosition(ccp((sendRewardItem->getContentSize().width/2), (sendRewardItem->getContentSize().height/2)));
        sendRewardLabel->setColor(ccBLACK);
        sendRewardItem->addChild(sendRewardLabel);
        
        localRewardDisplay->sendRewardItem = sendRewardItem;
        localRewardDisplay->sendRewardLabel = sendRewardLabel;
        
        
        // can't access local instance of this stuff because of lame menu strucure referencing static stuff in cocos2d
        //rewardMenu->addChild(sendRewardItem);
        localRewardDisplay->rewardMenu->addChild(sendRewardItem);
        
    } else {
        std::cout << "RewardDisplay: redeem: map missing key URL!\n";
        
    }
    
    
}



void RewardDisplay::_onOptionPressed_Submit(CCObject *pSender)
{
    //    if(disable)
    //        return;
    
    CCMenuItem* item = (CCMenuItem*) pSender;
    SimpleAudioEngine::sharedEngine()->playEffect(SFX_BUTTON);
    
    // tag contains a lookup to reward id in rewards set
    int rewardIndex = item->getTag();
    
    std::cout << "RewardDisplay: Submit rewardIndex: " << rewardIndex << "\n";
    
    // show other buttons
    RewardDisplay *rewardDisplay = PopUpRewardsLayer::sharedInstance()->rewardDisplays[rewardIndex];
    rewardDisplay->tosItem->setVisible(true);
    rewardDisplay->detailsItem->setVisible(true);
    rewardDisplay->redeemItem->setVisible(true);

    // hide submit buttons
    rewardDisplay->_editEmail->setVisible(false);
    rewardDisplay->sendRewardItem->setVisible(false);
    
    
    BTLootsieReward *btLootsieReward = PopUpRewardsLayer::sharedInstance()->lootsieRewards[rewardIndex];
    //long rewardId = std::atol(btLootsieReward->reward_id.c_str());
    //std::cout << "redeem reward:" << rewardId << std::endl;
    std::string rewardIdStr = btLootsieReward->reward_id;
    std::cout << "redeem reward:" << rewardIdStr << std::endl;
    
    std::string emailStr = rewardDisplay->_editEmail->getText();
    
    if (isValidEmailAddress(emailStr.c_str())) {
        NativeUtils::redeemReward(emailStr.c_str(), rewardIdStr.c_str());
    } else {
        CCMessageBox("Invalid Email Address!", "Email Address Check");
    }
    
}


# pragma - editbox

void RewardDisplay::editBoxEditingDidBegin(cocos2d::extension::CCEditBox *editBox) {
}

void RewardDisplay::editBoxEditingDidEnd(cocos2d::extension::CCEditBox *editBox) {
    std::cout << "editBoxEditingDidEnd: " << editBox->getText() << std::endl;
}

void RewardDisplay::editBoxTextChanged(cocos2d::extension::CCEditBox *editBox, std::string &text) {
    
}

void RewardDisplay::editBoxReturn(cocos2d::extension::CCEditBox *editBox) {
    std::cout << "editBoxReturn: " << editBox->getText() << std::endl;
    
    // hide submit buttons
    editBox->setVisible(false);
    
    
    std::string emailStr = editBox->getText();
    
    // show other buttons
    rewardIndex = editBox->getTag();
    
    RewardDisplay *rewardDisplay = PopUpRewardsLayer::sharedInstance()->rewardDisplays[rewardIndex];
    rewardDisplay->tosItem->setVisible(true);
    rewardDisplay->detailsItem->setVisible(true);
    rewardDisplay->redeemItem->setVisible(true);
    
    // hide submit buttons
    rewardDisplay->_editEmail->setVisible(false);
    rewardDisplay->sendRewardItem->setVisible(false);
    
    BTLootsieReward *btLootsieReward = PopUpRewardsLayer::sharedInstance()->lootsieRewards[rewardIndex];
    //long rewardId = std::atol(btLootsieReward->reward_id.c_str());
    //std::cout << "redeem reward:" << rewardId << std::endl;
    std::string rewardIdStr = btLootsieReward->reward_id;
    std::cout << "redeem reward:" << rewardIdStr << std::endl;

    
    if (isValidEmailAddress(emailStr.c_str())) {
        NativeUtils::redeemReward(emailStr.c_str(), rewardIdStr.c_str());
    } else {
        CCMessageBox("Invalid Email Address!", "Email Address Check");
    }

    
    
    //editBox->onExit();
    //editBox->onExit();
    //editBox->removeFromParent();
    //editBox->getParent()->removeChild(editBox);
}

bool RewardDisplay::isCharacter(const char Character)
{
    return ( (Character >= 'a' && Character <= 'z') || (Character >= 'A' && Character <= 'Z'));
    //Checks if a Character is a Valid A-Z, a-z Character, based on the ascii value
}

bool RewardDisplay::isNumber(const char Character)
{
    return ( Character >= '0' && Character <= '9');
}

bool RewardDisplay::isValidEmailAddress(const char * email)
{
    if(!email)
        return 0;
    if(!isCharacter(email[0]))
        return 0;
    int AtOffset = -1;
    int DotOffset = -1;
    unsigned int Length = strlen(email);
    
    for(unsigned int i = 0; i < Length; i++)
    {
        if(email[i] == '@')
            AtOffset = (int)i;
        else if(email[i] == '.')
            DotOffset = (int)i;
    }
    
    if(AtOffset == -1 || DotOffset == -1)
        return 0;
    if(AtOffset > DotOffset)
        return 0;
    return !(DotOffset >= ((int)Length-1));
    
}