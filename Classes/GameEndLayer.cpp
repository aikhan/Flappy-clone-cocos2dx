
/* ?? Code By: Kashif Asif */
#include "fbBridge.h"

#import "GameEndLayer.h"
#import "Global.h"
#import "MainScene.h"

#include "AdManagerBridge.h"
#include "GameCenterBridge.h"
#include "MKStoreKitBridge.h"
#include "SettingsManager.h"
#include "GameCenterBridge.h"


//#import <FacebookSDK/FacebookSDK.h>



#include "Constants.h"
//#import <Social/Social.h>
//#import "MKStoreManager.h"


extern CCMenuItemSprite *purchase;
extern CCMenuItemSprite *m_mContinue;
extern bool  Livespurchased;

#define DEBUG_MODE 0
int g_nMoves[100];
int g_nTimes[100];
Scene* GameEndLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameEndLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool GameEndLayer::init()

{
    if(!Layer::init())
    {
       
    }
    
    Layer::setTouchEnabled(true);
    createBackground();
    initVariable();
        return true;
}

void GameEndLayer::initVariable()
{
    
    
}
int GameEndLayer::getScore()
{
//    return scores;
}

void GameEndLayer::setScore(int score)
{
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("temp_score1", score);
    scores=score;
}

void GameEndLayer::createBackground()
{
    
   
     Size visibleSize = Director::getInstance()->getVisibleSize();
    float sizeW=visibleSize.width;
    float sizeH=visibleSize.height;
    
    
    Sprite* newSpr=Sprite::create("bg.png");
    newSpr->setPosition(CCPoint( sizeW/2, sizeH/2));
    KsetScale(newSpr, RATIO_XY);
    this->addChild(newSpr, -1);
    
    
    Sprite* newSprite1=Sprite::create("end_bg.png");
    newSprite1->cocos2d::Node::setPosition(sizeW/2, sizeH/2);
    KsetScale(newSprite1, RATIO_XY);
    this->addChild(newSprite1, -1);

    Sprite* newSprite2=Sprite::create("game over.png");
    newSprite2->cocos2d::Node::setPosition(getX(384), getY(130));
    KsetScale(newSprite2, RATIO_X);
    this->addChild(newSprite2, 1);
    
    
    
    m_mOk = MenuItemSprite::create(Sprite::create("btn_ok_normal.png"),Sprite::create("btn_ok_pressed.png"),NULL, this, menu_selector(GameEndLayer::onClickOk));
    
    m_mOk->setPosition(getX(70), getY(350));
    KsetScale(m_mOk, RATIO_X);

    
    m_mContinue = cocos2d::MenuItemSprite::create(Sprite::create("btn_continue_normal.png"),Sprite::create("btn_continue_pressed.png"),NULL, this, menu_selector(GameEndLayer::onClickContinue));
    m_mContinue->setPosition(getX(220), getY(350));
    KsetScale(m_mContinue, RATIO_X);
    m_mContinue->setVisible(false);
    m_mContinue->setEnabled(false);
    
    purchase = cocos2d::MenuItemSprite::create(Sprite::create("purchase1.png"),Sprite::create("purchase2.png"),NULL, this, menu_selector(GameEndLayer::onClickContinue));
    purchase->setPosition(getX(220), getY(350));
    KsetScale(purchase, RATIO_X);
  
    


    
    m_mFB = MenuItemSprite::create(Sprite::create("btn_fb_normal.png"),Sprite::create("btn_fb_pressed.png"), NULL, this, menu_selector(GameEndLayer::onClickFB));
    m_mFB->setPosition(getX(147), getY(430));
    KsetScale(m_mFB, RATIO_X);
    
   //
    //CCString *version =
    
    
    
    m_mTW = MenuItemSprite::create(Sprite::create("btn_tw_normal.png"),Sprite::create("btn_tw_pressed.png"),NULL, this, menu_selector(GameEndLayer::onClickTW));
    m_mTW->setPosition(getX(220), getY(430));
    KsetScale(m_mTW, RATIO_X);

    
    m_mML = MenuItemSprite::create(Sprite::create("btn_email_normal.png"),Sprite::create("btn_email_pressed.png"),NULL, this, menu_selector(GameEndLayer::onClickMail));
    m_mML->setPosition(getX(72), getY(430));
    KsetScale(m_mML, RATIO_X);
    
    
    m_mFreeGame =MenuItemSprite::create(Sprite::create("freeBtn.png"),Sprite::create("freeBtn.png"),NULL, this, menu_selector(GameEndLayer::onClickFree));
    m_mFreeGame->setPosition(getX(150), getY(150));
    
    KsetScale(m_mFreeGame, RATIO_X);
    
    
   
    
    
    fbBridge* check;
    if(check->checkVersion())
    {
        menu = CCMenu::create(m_mOk,m_mContinue,purchase, m_mFB, m_mTW , m_mML, m_mFreeGame,  NULL);
        menu->setPosition(0,0);
        this->addChild(menu, 10);
    }
    else
    {
        menu = CCMenu::create(m_mOk,m_mContinue,purchase, m_mFreeGame,  NULL);
        menu->setPosition(0,0);
        this->addChild(menu, 10);
    }

   
    int maxScore = 0;
    maxScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("SCORE");
    scores=CCUserDefault::sharedUserDefault()->getIntegerForKey("temp_score1");
    
    if(maxScore < scores)
    {
        Sprite* newSprite=Sprite::create("new.png");
        newSprite->cocos2d::Node::setPosition(getX(130), getY(268));
        KsetScale(newSprite, RATIO_XY);
        this->addChild(newSprite, 1);
        maxScore = scores;
    }
    CCUserDefault::sharedUserDefault()->setIntegerForKey("SCORE", maxScore);
    // [[NSUserDefaults standardUserDefaults] synchronize];
    
    
    String *tempStr=String::createWithFormat("  %d", scores);
    
    
    CCLabelBMFont* temp1=CCLabelBMFont::create( tempStr->getCString(), "BigGold_Font.fnt", 50);
   // temp1->setColor(ccc3(255,255,255));
    temp1->cocos2d::Node::setPosition(getX(125), getY(254));
    this->addChild(temp1, 190);
    
    
    tempStr=String::createWithFormat("%d", maxScore);
    CCLabelBMFont* temp2=CCLabelBMFont::create( tempStr->getCString(), "BigGold_Font.fnt", 16);
    temp2->setColor(ccc3(255,255,0));
    temp2->cocos2d::Node::setPosition(getX(216), getY(254));
    this->addChild(temp2, 10);
    
    GameCenterBridge* temp;
    temp->submitScore(scores);
    
    
    
    if(g_iLives < 0)
        g_iLives = 0;
#ifdef FreeApp
    if(!CCUserDefault::sharedUserDefault()->getBoolForKey("inapp1"))
    {
        AdManagerBridge* tempAdd;
        tempAdd->giveMeGameOverAdd();
    }
#endif
    

    
    
   
}



 void GameEndLayer::onClickContinue(Object* temp)
{
 //   CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("general_button3.mp3");
    
    if( Livespurchased==true)
    {
       
        
        Livespurchased=false;
        purchase->setVisible(true);
        purchase->setEnabled(true);
        m_mContinue->setEnabled(false);
        m_mContinue->setVisible(false);
        
        g_lGameLayer->recurrenceGame();
        this->removeFromParentAndCleanup(true);
        
        
    }
    
    
    else
    {
        MKStoreKitBridge* temp;
        temp->callIAP(1);

    }

    
    
}


void GameEndLayer::onClickFree(Object* temp)
{

#ifdef FreeApp
    AdManagerBridge* tempAdd1;
    tempAdd1->giveMeFreeGamesAd();
#endif
}

void GameEndLayer::onClickFB(Object* temp)
{
  //CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("general_button3.mp3");
    
    fbBridge* facebookPtr;
    String* temp1=String::createWithFormat("%s%d%s", "Yaay!! I scored ", scores, " :) \nI bet you can't beat mine #flappy #flappybird \nGrab this awesome FREE game now ");
    facebookPtr->shareFB(temp1);
}





  void GameEndLayer::onClickTW(Object* temp)
{
   // CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("general_button3.mp3");
    
    fbBridge* twtPtr;
    String* temp1=String::createWithFormat("%s%d%s", "Yaay!! I scored ", scores, " :) \nI bet you can't beat mine #flappy #flappybird \nGrab this awesome FREE game now bit.ly/1bHhuuq");
    twtPtr->shareTwitter(temp1);
}


void GameEndLayer::onClickMail(Object* temp)
{
   // CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("general_button3.mp3");
  
    fbBridge* mailPtr;
    String* Subject=String::createWithFormat("%s%d%s", "I Scored ", scores, " :D \nDo you Dare to compare?");
    String* Body=String::createWithFormat("%s%d%s", "Hey I have scored ", scores, " in Flappy Birds Easy.\nDo you dare to compare your's?\nYoucan download the free version from bit.ly/1bHhuuq\n\nLet me know when you break my record..!!");
    mailPtr->sendMail(Subject, Body, scores);
}



#pragma mark Share Feature

void GameEndLayer::onClickOk(Object* temp)
{
  //  FX_BTN();
 
    auto director = Director::getInstance();
    auto scene = MainScene::createScene();
    director->replaceScene(scene);
}

void GameEndLayer::showPurchaseAlert(String *messsage,  int tag)
{
//    UIAlertView   *alert = [[UIAlertView alloc] initWithTitle:@"Flappy Bird" message:messsage delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"OK",nil];
//    alert.tag = tag;
//    [alert show];
//    alert = nil;
}


