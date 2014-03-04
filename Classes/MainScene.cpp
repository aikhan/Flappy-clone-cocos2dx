//
//  MainScene.m
//  Flappy Bird
//
//  Created by JTK on 1/20/14.
//  Copyright 2014 org. All rights reserved.
//

#import "MainScene.h"
#include "Global.h"
#import "AppDelegate.h"
#include "Constants.h"
#include "AdManagerBridge.h"
#include "GameCenterBridge.h"
#include "fbBridge.h"
#include "MKStoreKitBridge.h"
USING_NS_CC;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    
    // return the scene
    return scene;
}



bool MainScene::init()

{
    if((!Layer::init()))
        
    {
        Layer::setTouchEnabled(true);
    }
    createBackground();
    initVariable();
    g_lMainLayer = this;
    return true;
}

void MainScene::initVariable()

{
    MoveBy* actionOne=CCMoveBy::create(0.5,  CCPoint(0, 20));
    MoveBy* actionTwo=CCMoveBy::create(0.5, CCPoint(0, -20));
    Sequence* seq1=Sequence::create(actionOne,actionTwo,  NULL);
    RepeatForever* rep1=RepeatForever::create(seq1);
    m_sBirdSprite->runAction(rep1);
    
    MoveBy* actionOne1=CCMoveBy::create(0.5,  CCPoint(0, 20 ));
    MoveBy* actionTwo1=CCMoveBy::create(0.5, CCPoint(0, -20 ));
    Sequence* seq11=Sequence::create(actionOne1,actionTwo1,NULL);
    RepeatForever* rep11=RepeatForever::create(seq11);
    m_sLogoSprite->runAction(rep11);
    
    bird_fly_animation();
    Animate*  actionFly = CCAnimate::create(animation_bird_fly);
    m_sBirdSprite->runAction(CCRepeatForever::create(actionFly));
    this->schedule(schedule_selector(MainScene::Update),0.01);
    
}



void MainScene::bird_fly_animation()
{
    animation_bird_fly= CCAnimation::create();
    
    
    for (int i = 0; i < 2; i++)
    {
        char szImageFileName[128] = {0};
        sprintf(szImageFileName, "bird%i.png", i);
        animation_bird_fly->addSpriteFrameWithFileName(szImageFileName);
    }
    
    
    animation_bird_fly->setDelayPerUnit(0.2);
    animation_bird_fly->setRestoreOriginalFrame(true);
    animation_bird_fly->retain();
    
}




void MainScene::createBackground()
{
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    mainScreen=Sprite::create("bg.png");
    mainScreen->setPosition(CCPoint(visibleSize.width/2,visibleSize.height/2));
     KsetScale(mainScreen, RATIO_XY);
    this->addChild(mainScreen, 0);
    
    m_sBirdSprite = Sprite::create("bird0.png");
    m_sBirdSprite->cocos2d::Node::setPosition(getX(260), getY(100));
     KsetScale(m_sBirdSprite, RATIO_XY);
    this->addChild(m_sBirdSprite, 1);
    
    m_sLogoSprite = Sprite::create("flappy bird.png");
    m_sLogoSprite->cocos2d::Node::setPosition(getX(130), getY(100));
     KsetScale(m_sLogoSprite, RATIO_XY);
    this->addChild(m_sLogoSprite, 1);
    
    m_sGroundSprite[0] = Sprite::create("ground.png");
    m_sGroundSprite[0]->cocos2d::Node::setPosition(getX(154), getY(456));
     KsetScale(m_sGroundSprite[0], RATIO_XY);
    this->addChild(m_sGroundSprite[0], 0);
    
    m_sGroundSprite[1] = Sprite::create("ground.png");
    m_sGroundSprite[1]->cocos2d::Node::setPosition(getX(460), getY(456));
    KsetScale(m_sGroundSprite[1], RATIO_XY);
    
  
    
   
    
    this->addChild(m_sGroundSprite[1], 0);
    
    
    //================================================================================================
    //================================================================================================
    //==================================================================================================
    
    
    m_mStart = MenuItemSprite::create(Sprite::create("btn_start_normal.png"),Sprite::create("btn_start_pressed.png"),NULL, this, menu_selector(MainScene::onClickStart));
    m_mStart->setPosition(getX(88), getY(338-10));
    KsetScale(m_mStart, RATIO_X);
    
    
    m_mScore = MenuItemSprite::create(Sprite::create("btn_score_normal.png"),Sprite::create("btn_score_pressed.png"),NULL, this, menu_selector(MainScene::onClickScore));
    m_mScore->setPosition(getX(207), getY(338-10));
    KsetScale(m_mScore, RATIO_X);
    
    m_mRate = MenuItemSprite::create(Sprite::create("btn_rate_normal.png"),Sprite::create("btn_rate_pressed.png"),NULL, this, menu_selector(MainScene::onClickRate));
    m_mRate->setPosition(getX(207), getY(285-10));
    KsetScale(m_mRate, RATIO_X);
    
    
    m_mMore=MenuItemSprite::create(Sprite::create("btn_more_normal.png"),Sprite::create("btn_more_pressed.png"),NULL, this, menu_selector(MainScene::onClickMore));
    m_mMore->setPosition(getX(207), getY(391-10));
    KsetScale(m_mMore, RATIO_X);


  
    removeAdd=MenuItemSprite::create(Sprite::create("remove1.png"),Sprite::create("remove2.png"),NULL, this, menu_selector(MainScene::onClickRemove));
    removeAdd->setPosition(getX(148), getY(444-10));
    KsetScale(removeAdd, RATIO_X);

    
    restore=MenuItemSprite::create(Sprite::create("restore2.png"),Sprite::create("restore1.png"),NULL, this, menu_selector(MainScene::onClickMore));
    restore->setPosition(getX(88), getY(391-10));
    KsetScale(restore, RATIO_X);
   
    
    


    
#ifdef FreeApp
if(!CCUserDefault::sharedUserDefault()->getBoolForKey("inapp1"))
{
    menu = CCMenu::create(m_mStart, m_mScore,m_mMore, removeAdd,m_mRate, restore, NULL);
    menu->setPosition(0,0);
    this->addChild(menu, 10);
}
else
{
    menu = CCMenu::create(m_mStart, m_mScore,m_mMore,m_mRate, NULL);
    menu->setPosition(0,0);
    this->addChild(menu, 10);
}
#endif
    
    
#ifdef PaidApp
    menu = CCMenu::create(m_mStart, m_mScore,m_mMore,m_mRate,NULL);
    menu->setPosition(0,0);
    this->addChild(menu, 10);
#endif
    
    
 //   if(!CCUserDefault::sharedUserDefault()->getBoolForKey("Rated"))
      //  menu->addChild(m_mRate);
    
}

void MainScene::onClickRemove(Object * Sender)
{
 
    MKStoreKitBridge * storeTemp;
    storeTemp->initialise();
    storeTemp->callRemoveAds();
    
    
}

void MainScene::updateRateButton()
{
    menu->removeChild(m_mRate, true);
    
}

void MainScene::onClickStart(Object * sender)
{
  
    auto director = Director::getInstance();
    auto scene = GameScene::createScene();
    director->replaceScene(scene);
    
    fbBridge* temp;
    
    if(temp->checkVersion())
    {
        log("%d", 1);
        
    }
    else
    {
        log("%d", 0);

    }
   
    
    
    
}

void MainScene::onClickScore(Object * sender)
{
    GameCenterBridge* temp;
    temp->showScores();
    
}

void MainScene::onClickRate(Object * sender)
{
    fbBridge* temp;
    temp->rateMe();
    
    m_mRate->setEnabled(false);
    m_mRate->setVisible(false);
    
    
}

void MainScene::onClickMore(Object * sender)
{

  // if(!CCUserDefault::sharedUserDefault()->getBoolForKey("inapp"))
   {
       AdManagerBridge* tempAdd;
       tempAdd->giveMeMoreGamesAd();
   }

}

void MainScene::Update(float dt)
{
   
    m_sGroundSprite[0]->setPosition(CCPoint(m_sGroundSprite[0]->getPositionX() - 8 ,m_sGroundSprite[0]->getPositionY()));
    
    m_sGroundSprite[1]->setPosition(CCPoint(m_sGroundSprite[1]->getPositionX() - 8 , m_sGroundSprite[1]->getPositionY()));
  //  log("%f", m_sGroundSprite[0]->getPositionX());
    
    
    
    if(m_sGroundSprite[0]->getPositionX() < 0 * G_SCALEX / g_fScaleR)
        
    {
        m_sGroundSprite[0]->setPosition(CCPoint(getX(154), getY(456)));
        m_sGroundSprite[1]->setPosition(CCPoint(getX(460), getY(456)));
    }
}

