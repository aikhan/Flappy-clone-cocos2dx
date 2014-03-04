/* ?? Code By: Kashif Asif */

#include    "cocos2d.h"
#include    <CCParticleExamples.h>
#include    "SimpleAudioEngine.h"
#include    "GameScene.h"
#include    "Global.h"
#include    "MainScene.h"
#include    "GameEndLayer.h"
#include    "AppDelegate.h"
#include    "SettingsManager.h"
#include    "Constants.h"
#include    "AdManagerBridge.h"

USING_NS_CC;
//#ifndef callfunc_selector(_SELECTOR) (SEL_CallFunc)(&_SELECTOR)

//#define callfunc_selector(_SELECTOR) (SEL_CallFunc)(&_SELECTOR)

Scene* GameScene::createScene()

{
    
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}



bool GameScene::init()
{
   if(!Layer::init())
    {
        
        
    }
    Layer::setTouchEnabled(true);
    Layer::registerWithTouchDispatcher();
    
    createBackground();
    
    initVariable();
     g_lGameLayer = this;
    return true;
}


void GameScene::bird_fly_animation()
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


void GameScene:: initVariable()
       
{

  
    
    
    
    MoveBy* move1=MoveBy::create(0.5, CCPoint(0, 20 * G_SCALEY / g_fScaleR));
    MoveBy* move2=MoveBy::create(0.5,CCPoint(0, -20 * G_SCALEY / g_fScaleR));
    
    
    Sequence* seq      =  Sequence::create(move1, move2, NULL);
    RepeatForever* rpt =  RepeatForever::create(seq);
    m_aUpDownAction    =  m_sBirdSprite->runAction(rpt);
     
  
    g_iLives = LIVES_COUNT;

    if(!ENABLE_LIVES)
    {
       g_iLives = 0;
    }
    
    String* temp=String::createWithFormat("%s%d", "Lives: ", g_iLives);
    m_lbtLives->setString(temp->getCString());
    
    
    m_sObstacle[0]->setAnchorPoint(CCPoint(0.5, 0));
    m_sObstacle[1]->setAnchorPoint(CCPoint(0.5, 1));
    m_sObstacle[2]->setAnchorPoint(CCPoint(0.5, 0));
    m_sObstacle[3]->setAnchorPoint(CCPoint(0.5, 1));
    m_sObstacle[4]->setAnchorPoint(CCPoint(0.5, 0));
    m_sObstacle[5]->setAnchorPoint(CCPoint(0.5, 1));
    
    
    m_iObstacleCnt = 0;
    
    int tmp = arc4random() % 256 + 180;
    
     m_sObstacle[0]->setPosition(CCPoint(m_sObstacle[0]->getPositionX(), (tmp + (120 - m_iObstacleCnt * 2)) * G_SCALEY / g_fScaleR));
     m_sObstacle[1]->setPosition(CCPoint(m_sObstacle[1]->getPositionX(), (tmp - (120 - m_iObstacleCnt * 2)) * G_SCALEY / g_fScaleR));
     
    m_gCenPos[0]=CCPoint(m_sObstacle[0]->getPositionX(), tmp * G_SCALEY / g_fScaleR);
    m_gCenPos[1]=CCPoint(m_sObstacle[1]->getPositionX(), tmp * G_SCALEY / g_fScaleR);
    
    m_iObstacleCnt++;
     
    tmp = arc4random() % 256 + 180;
   
    m_sObstacle[2]->setPosition(CCPoint(m_sObstacle[2]->getPositionX(), (tmp + (120 - m_iObstacleCnt * 2)) * G_SCALEY / g_fScaleR));
   
    m_sObstacle[3]->setPosition(CCPoint(m_sObstacle[3]->getPositionX(), (tmp - (120 - m_iObstacleCnt * 2)) * G_SCALEY / g_fScaleR));
     
    m_gCenPos[2]=CCPoint(m_sObstacle[2]->getPositionX(), tmp * G_SCALEY / g_fScaleR);
    m_gCenPos[3]=CCPoint(m_sObstacle[3]->getPositionX(), tmp * G_SCALEY / g_fScaleR);
    m_iObstacleCnt++;
    tmp = arc4random() % 256 + 180;
     
    m_sObstacle[4]->setPosition(CCPoint(m_sObstacle[4]->getPositionX(), (tmp + (120 - m_iObstacleCnt * 2)) * G_SCALEY / g_fScaleR));
     
    m_sObstacle[5]->setPosition(CCPoint(m_sObstacle[5]->getPositionX(), (tmp - (120 - m_iObstacleCnt * 2)) * G_SCALEY / g_fScaleR));
     
    m_gCenPos[4]=CCPoint(m_sObstacle[4]->getPositionX(), tmp * G_SCALEY / g_fScaleR);
    m_gCenPos[5]=CCPoint(m_sObstacle[5]->getPositionX(), tmp * G_SCALEY / g_fScaleR);
    
    m_iPastTime = 0;
    
    m_fSpeedX = 8 * G_SCALEX / g_fScaleR;
    
    this->schedule(schedule_selector(GameScene::Update1),0.05);
    bird_fly_animation();
    Animate*  actionFly = CCAnimate::create(animation_bird_fly);
    m_sBirdSprite->runAction(CCRepeatForever::create(actionFly));
    
    m_iOvercomedObstacle = -1;
    m_iScore = 0;
    m_fTime = 0;
    m_iRecurrenceTime = 0;
}

void GameScene::createBackground()
{
  //  CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bg.mp3", true);
  
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.3);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(1);
    
    Sprite* newSpr=Sprite::create("bg.png");
    newSpr->setPosition(CCPoint(G_SWIDTH/2, G_SHEIGHT/2));
    KsetScale(newSpr, RATIO_XY);
    this->addChild(newSpr, -1);
     
     m_sBirdSprite =Sprite::create("bird0.png");
     m_sBirdSprite->setPosition(CCPoint(getX(90), getY(230)));
    KsetScale(m_sBirdSprite, RATIO_X);
     this->addChild(m_sBirdSprite, 1);
     
     m_sTapSprite=Sprite::create("start_tap.png");
     m_sTapSprite->setPosition(CCPoint(getX(170), getY(260)));
    KsetScale(m_sTapSprite, RATIO_X);
     this->addChild(m_sTapSprite, 1);
     
    m_sReadySprite=Sprite::create("get ready.png");
    m_sReadySprite->setPosition(CCPoint(G_SWIDTH / 2, getY(130)));
    KsetScale(m_sReadySprite, RATIO_X);
    this->addChild(m_sReadySprite, 1);
     
     int tmp = arc4random() % OBSTACLE_COUNT;
    
    std::string temp=std::to_string(tmp);
    std::string temp2=temp;
    
    
    temp="obstacle_up"+temp;
    temp=temp + ".png";
    
    m_sObstacle[0]= Sprite::create(temp);
    m_sObstacle[0]->cocos2d::Node::setPosition(getX(400), getY(230));
    KsetScale(m_sObstacle[0], RATIO_XY);
    this->addChild(m_sObstacle[0], -1);
    
    temp="obstacle_down"+temp2;
    temp=temp + ".png";
    m_sObstacle[1]= Sprite::create(temp);
    m_sObstacle[1]->cocos2d::Node::setPosition(getX(400), getY(230));
    KsetScale(m_sObstacle[1], RATIO_XY);
    this->addChild(m_sObstacle[1], -1);
    
    
     
    tmp = arc4random() % OBSTACLE_COUNT;
    std::string temp3=std::to_string(tmp);
    std::string temp4=temp3;
    
    temp3="obstacle_up"+temp3;
    temp3=temp3 + ".png";
    m_sObstacle[2]= Sprite::create(temp3);
    m_sObstacle[2]->cocos2d::Node::setPosition(getX(600), getY(230));
    KsetScale(m_sObstacle[2], RATIO_XY);
    this->addChild(m_sObstacle[2], -1);
    
    temp3="obstacle_down"+temp4;
    temp3=temp3 + ".png";
    m_sObstacle[3]= Sprite::create(temp3);
    m_sObstacle[3]->cocos2d::Node::setPosition(getX(600), getY(230));
    KsetScale(m_sObstacle[3], RATIO_XY);
    this->addChild(m_sObstacle[3], -1);
    
    tmp = arc4random() % OBSTACLE_COUNT;
    std::string temp5=std::to_string(tmp);
    std::string temp6=temp5;
    
    temp5="obstacle_up"+temp5;
    temp5=temp5 + ".png";
    m_sObstacle[4]= Sprite::create(temp5);
    m_sObstacle[4]->cocos2d::Node::setPosition(getX(800), getY(230));
    KsetScale(m_sObstacle[4], RATIO_XY);
    this->addChild(m_sObstacle[4], -1);
    
    temp5="obstacle_down"+temp6;
    temp5=temp5 + ".png";
    m_sObstacle[5]= Sprite::create(temp5);
    m_sObstacle[5]->cocos2d::Node::setPosition(getX(800), getY(230));
    KsetScale(m_sObstacle[5], RATIO_XY);
    this->addChild(m_sObstacle[5], -1);
    

    m_sGroundSprite[0] = Sprite::create("ground.png");
    m_sGroundSprite[0]->setPosition(CCPoint(getX(154), getY(456)));
    KsetScale(m_sGroundSprite[0], RATIO_XY);
    this->addChild(m_sGroundSprite[0], 0);
    
    m_sGroundSprite[1] = Sprite::create("ground.png");
    m_sGroundSprite[1]->setPosition(CCPoint(getX(460), getY(456)));
    KsetScale(m_sGroundSprite[1], RATIO_XY);
    this->addChild(m_sGroundSprite[1], 0);
    
    m_lColorLayer = CCLayerColor::create(ccc4(0,0,0,150));
    this->addChild(m_lColorLayer, 5);
    m_lColorLayer->setVisible(false);
     
    
    m_mPause = MenuItemSprite::create(Sprite::create("btn_pause_normal.png"),Sprite::create("btn_pause_pressed.png"),NULL, this, menu_selector(GameScene::onClickPause));
    m_mPause->setPosition(getX(30), getY(30));
    KsetScale(m_mPause, RATIO_X);
    m_mPause->setVisible(true);
    m_mPause->setEnabled(true);
    
     
    m_mResume = MenuItemSprite::create(Sprite::create("btn_resume_normal.png"),Sprite::create("btn_resume_normal.png"),NULL, this, menu_selector(GameScene::onClickResume));
    m_mResume->setPosition(getX(30), getY(30));
    KsetScale(m_mResume, RATIO_X);
    m_mResume->setVisible(false);
    m_mResume->setEnabled(false);
    
    m_mMenu = MenuItemSprite::create(Sprite::create("btn_menu_normal.png"),Sprite::create("btn_menu_normal.png"),NULL, this, menu_selector(GameScene::onClickMenu));
    m_mMenu->setPosition(G_SWIDTH/2, G_SHEIGHT/2);
    KsetScale(m_mMenu, RATIO_X);
    m_mMenu->setEnabled(false);
    m_mMenu->setVisible(false);
    
    menu = CCMenu::create(m_mPause, m_mResume, m_mMenu, NULL);
    menu->setPosition(0,0);
    this->addChild(menu, 10);

     
     
    CCMenu *music_item;
    itemOff=CCMenuItemSprite::create(Sprite::create("btn_musicoff.png"), NULL, this, menu_selector(GameScene::onClickMusic));
    itemOn=CCMenuItemSprite::create(Sprite::create("btn_musicon.png"), NULL, this, menu_selector(GameScene::onClickMusic));
    
    KsetScale(itemOff, RATIO_X);
    KsetScale(itemOn, RATIO_X);
    
    itemOff->setPosition(getX(70), getY(30));
    itemOn->setPosition(getX(70), getY(30));
    
    itemOff->setVisible(true);
    itemOff->setEnabled(true);
    
    itemOn->setVisible(false);
    itemOn->setEnabled(false);
    
    music_item = CCMenu::create(itemOn, itemOff, NULL);
    music_item->setPosition(0,0);
    this->addChild(music_item, 100);
    
    
    

    m_lbtScore=CCLabelBMFont::create("Score: 0", "BigGold_Font.fnt", 500*visibleSize.height/2048);
    m_lbtScore->setColor(ccc3(255,255,255));
    m_lbtScore->cocos2d::Node::setPosition(G_SWIDTH/2, getY(25));
    m_lbtScore->setScale(visibleSize.height*2/2048);
    m_lbtScore->setAnchorPoint(CCPoint(0.5, 0.5));
    this->addChild(m_lbtScore);
                                   
    m_lbtLives=CCLabelBMFont::create("Lives: 3", "BigGold_Font.fnt", 500);
    m_lbtLives->setColor(ccc3(255,255,255));
    m_lbtLives->cocos2d::Node::setPosition(getX(250), getY(25));
    m_lbtLives->setAnchorPoint(CCPoint(0.5, 0.5));
    m_lbtLives->setScale(visibleSize.height*2/2048);
    this->addChild(m_lbtLives);

                                   
                                   
                                   
    
    if(!ENABLE_LIVES)
        m_lbtLives->setOpacity(0);
}

                                   
                                   
                                   


#pragma mark -ClickActions

void GameScene::onClickMusic(Object* temp)
{
    g_bMusicMute = !g_bMusicMute;
    
    if(g_bMusicMute)
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(0);
        
        itemOff->setVisible(false);
        itemOff->setEnabled(false);
        
        itemOn->setVisible(true);
        itemOn->setEnabled(true);
       
    }
    else
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.3);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(1);
        
        itemOff->setVisible(true);
        itemOff->setEnabled(true);
        
        itemOn->setVisible(false);
        itemOn->setEnabled(false);
        
    }
}

void GameScene::onClickPause(Object* temp)
{

    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
    m_mPause->setEnabled(false);
    m_mPause->setVisible(false);
         
    m_mResume->setEnabled(true);
    m_mResume->setVisible(true);
         
    Layer::setTouchEnabled(false);
    m_mMenu->setVisible(true);
    m_mMenu->setEnabled(true);
         
    m_lColorLayer->setVisible(true);
         
    this->unschedule(schedule_selector(GameScene::Update1));
    
    m_sBirdSprite->pauseSchedulerAndActions();
         
}

void GameScene::onClickMenu(Object* temp)
     
{

    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_swooshing.mp3");
    auto director = Director::getInstance();
    auto scene = MainScene::createScene();
    director->replaceScene(scene);
}

void GameScene::onClickResume(Object* temp)
{

    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    
    
    m_mPause->setEnabled(true);
    m_mPause->setVisible(true);
    
    m_mResume->setEnabled(false);
    m_mResume->setVisible(false);
    
    
    Layer::setTouchEnabled(false);
    
    m_mMenu->setEnabled(false);
    m_mMenu->setVisible(false);
    
    m_lColorLayer->setVisible(false);
    
    this->schedule(schedule_selector(GameScene::Update1),0.05);
    
    
    m_sBirdSprite->resumeSchedulerAndActions();
    
}
#pragma mark -GameEngine
void GameScene::gameEnd()
{
    
    
    m_lColorLayer->setVisible(true);
    m_lColorLayer->setZOrder(99);
    Layer::setTouchEnabled(false);
    this->unschedule(schedule_selector(GameScene::Update1));
    
    m_sBirdSprite->pauseSchedulerAndActions();
    class GameEndLayer objScore;
    objScore.setScore(m_iScore);
    
    auto director = Director::getInstance();
    auto scene = GameEndLayer::createScene();
    director->pushScene(scene);
}

void GameScene::recurrenceGame()
{
   // this->removeChild(m_lGameEndLayer);
    
    
    auto director = Director::getInstance();
    director->popScene();
    
    
    std::string sa = std::to_string(g_iLives);
    sa="Lives: " + sa;
    m_lbtLives->setString(sa);

    m_mPause->setEnabled(true);
    m_mPause->setVisible(true);
    
    m_mResume->setEnabled(false);
    m_mResume->setVisible(false);
    
    m_mMenu->setEnabled(false);
    m_mMenu->setVisible(false);
    
    Layer::setTouchEnabled(true);
    m_lColorLayer->setVisible(false);
    
    m_fSpeedY = 7 * G_SCALEX / g_fScaleR;
    m_iPastTime = 0;
    m_fSpeedX = 8 * G_SCALEX / g_fScaleR;
    m_iRecurrenceTime = 120;

    m_sBirdSprite->runAction(CCBlink::create(1, 5));
    m_sBirdSprite->runAction(CCFadeTo::create(1, 255));
    
    this->schedule(schedule_selector(GameScene::Update1),0.05);
    m_sBirdSprite->resumeSchedulerAndActions();
    m_sBirdSprite->setPosition(Point(m_sBirdSprite->getPositionX(), getY(230)));
}

void GameScene::Update1(float dt)
{
    if(m_aUpDownAction != NULL)
        return;
    
    m_fTime = m_fTime+ 0.05;
    m_fSpeedY  = m_fSpeedY-( 0.7 * m_iPastTime);
    m_iPastTime++;
    
    if(g_iLives<1)
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_die.mp3");
        gameEnd();
        
    }
    
    if(m_sBirdSprite->getPositionY()+ m_fSpeedY< G_SHEIGHT)
    {
    m_sBirdSprite->setPosition(CCPoint(m_sBirdSprite->getPositionX(), m_sBirdSprite->getPositionY()+ m_fSpeedY));
    }
    
    
  
    
    m_sBirdSprite->runAction(RotateTo::create(0.2, -CC_RADIANS_TO_DEGREES(atan2f(m_fSpeedY, m_fSpeedX))));
    
    
    
    for (int i = 0; i < 6; i ++)
    {
        m_sObstacle[i]->setPosition(CCPoint(m_sObstacle[i]->getPositionX() - m_fSpeedX, m_sObstacle[i]->getPositionY()));
        
        if(m_sObstacle[i]->getPositionX() < -30 * G_SCALEX / g_fScaleR)
        {
            int tmp = arc4random() % 256 + 180;
            if(m_iObstacleCnt < 70)
            {
                m_iObstacleCnt++;
                
            }
            
            
            m_sObstacle[i]->setPosition(CCPoint(m_sObstacle[i]->getPositionX() + 600.0 * G_SCALEX / g_fScaleR, (tmp + (120 - m_iObstacleCnt)) * G_SCALEY / g_fScaleR));
 
            m_sObstacle[i + 1]->setPosition(CCPoint(m_sObstacle[i]->getPositionX(), (tmp - (120 - m_iObstacleCnt)) * G_SCALEY / g_fScaleR));
            m_gCenPos[i] = ccp(m_sObstacle[i]->getPositionX() + 600.0 * G_SCALEX / g_fScaleR, tmp * G_SCALEY / g_fScaleR);
            m_gCenPos[i + 1] = ccp(m_sObstacle[i + 1]->getPositionX() + 600.0 * G_SCALEX / g_fScaleR, tmp * G_SCALEY / g_fScaleR);
            
            
            
       
            
            tmp = arc4random() % OBSTACLE_COUNT;
            i++;
            
        }
        
        if(m_sObstacle[(m_iScore * 2) % 6]->getPositionX() < m_sBirdSprite->getPositionX())
        {
            m_iScore++;
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_point.mp3");
            
        }
        
        if(m_iRecurrenceTime > 0)
        {
            m_iRecurrenceTime--;
        }
        else{
            Rect rect1= m_sObstacle[i]->getBoundingBox();
            Rect rect2= m_sBirdSprite->getBoundingBox();
            
            
            if(rect1.intersectsRect(rect2) )
            {
                g_iLives--;
                if(g_iLives < 0)
                    g_iLives = 0;
                
                if(g_iLives < 1)
                {
                    Layer::setTouchEnabled(false);
                    if(m_fSpeedX != 0)
                        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_die.mp3");

                    m_fSpeedX = 0;
                }
                else
                {
                    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_hit.mp3");
                
                    m_iRecurrenceTime = 120;
                    

                    m_sBirdSprite->runAction(CCBlink::create(1, 5));
                    m_sBirdSprite->runAction(CCFadeTo::create(1, 255));
                    
                    
            
                    std::string ba = std::to_string(g_iLives);
                    ba="Lives: " + ba;
                    m_lbtLives->setString(ba);
                }
            }
            
        }
    }
    
    std::string ca = std::to_string(g_iLives);
    ca="Lives: " + ca;
    m_lbtLives->setString(ca);

    int tempInt=m_iScore;
    ca = std::to_string(tempInt);
    ca="Score: " + ca;
    m_lbtScore->setString(ca);

    
    m_sGroundSprite[0]->setPosition(CCPoint(m_sGroundSprite[0]->getPositionX() - m_fSpeedX, m_sGroundSprite[0]->getPositionY()));
    m_sGroundSprite[1]->setPosition(CCPoint(m_sGroundSprite[1]->getPositionX() - m_fSpeedX, m_sGroundSprite[1]->getPositionY()));
    
    
    if(m_sGroundSprite[0]->getPositionX() < -154 * G_SCALEX / g_fScaleR)
    {
        m_sGroundSprite[0]->setPosition(CCPoint(getX(154), getY(456)));
        m_sGroundSprite[1]->setPosition(CCPoint(getX(460), getY(456)));
    }
    
    if(m_sBirdSprite->getPositionY() < 70 * G_SCALEY / g_fScaleR){
        {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_die.mp3");
            Object * temp;
            g_iLives=0;
            gameEnd();
          //  onClickPause(temp);
            
            
        }
        
    }
}


void GameScene::continueGame()
{
    
}
#pragma mark -TouchDelegate

bool GameScene::onTouchBegan (Touch *touch,Event *event)
{
//    UITouch *touch = [touches anyObject];

    Point location = touch->getLocationInView();
    location = CCDirector::getInstance()->convertToGL(location);

  
    if(m_aUpDownAction != NULL)
    {
         /*
        NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
        int runCnt = [userDefaults integerForKey:@"ADS"];
        [userDefaults setInteger: runCnt + 1 forKey:@"ADS"];
        
        if(runCnt % 2)
          {
            AppController *delegate = (AppController *)[[UIApplication sharedApplication] delegate];
            if((runCnt / 2) % 2) [delegate showAdBanner];
            else [delegate showBanner];
          }*/
        
    
    m_sBirdSprite->stopAction(m_aUpDownAction);
    m_aUpDownAction=NULL;
    
    
    // m_aUpDownAction = NULL;
    

    m_sTapSprite->runAction(FadeTo::create(0.5, 0));
    m_sReadySprite->runAction(FadeTo::create(0.5, 0));
    }
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_wing.mp3");


    m_fSpeedY = 7 *G_SCALEX/g_fScaleR;

    m_iPastTime = 0;
    
}



void GameScene::onEnter()
{
    Layer::onEnter();
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan      = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved      = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded      = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    listener->onTouchCancelled  = CC_CALLBACK_2(GameScene::onTouchCancelled, this);
    
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    
}


void dealloc()
{
  //  [super dealloc];
  //  g_lGameLayer = NULL;
}
//#endif

