/* ?? Code By: Kashif Asif */

#ifndef __FlappyBirdsRevenge__SettingsManager__1
#define __FlappyBirdsRevenge__SettingsManager__1

#include "cocos2d.h"
#include "GameEndLayer.h"

USING_NS_CC;


class GameScene:public cocos2d::Layer
{
public:
    static Scene* createScene();
    
    
    virtual bool init();
    
    
    CREATE_FUNC(GameScene);
    
    void bird_fly_animation();
    Animation *animation_bird_fly;
   
    CCMenu *menu;
    CCMenuItemSprite *m_mPause, *m_mResume, *m_mMenu;
    CCMenuItemToggle *m_mMusic;
    CCLayerColor *m_lColorLayer;
    CCMenuItemSprite *itemOn, *itemOff;
    
    CCSprite *m_sBirdSprite;
    
    CCSprite *m_sObstacle[10];
    CCSprite *m_sGroundSprite[2];
    CCSprite *m_sTapSprite;
    CCSprite *m_sReadySprite;
    CCAction *m_aUpDownAction;
    CCPoint m_gCenPos[10];
    
    CCLabelBMFont *m_lbtScore, *m_lbtLives;
    GameEndLayer *m_lGameEndLayer;
    
    int m_iScore;
    int m_iOvercomedObstacle;
    float m_fSpeedY;
    float m_fSpeedX;
    int m_iPastTime;
    int m_iRecurrenceTime;
    int m_iObstacleCnt;
    float m_fTime;
    
    void recurrenceGame();
    void dealloc();
    
    void initVariable();
    void createBackground();
    void onClickMusic(Object* temp);
    void onClickPause(Object* temp);
    void onClickMenu(Object* temp);
    void onClickResume(Object* temp);
    void continueGame();
    void gameEnd();
    
    
    
    float g_fScaleR = 1.0;
    float G_ORG_WIDTH = 288;
    float G_ORG_HEIGHT = 512;
    CCSize visibleSize = Director::getInstance()->getVisibleSize();
    
    float G_SWIDTH=visibleSize.width;   //Screen width
    float G_SHEIGHT=visibleSize.height;   //Screen height
   
    float G_SCALEX= (G_SWIDTH * g_fScaleR / G_ORG_WIDTH);
    float G_SCALEY= (G_SHEIGHT * g_fScaleR / G_ORG_HEIGHT);
    
//    int LIVES_COUNT=3;
    
    void Update1(float dt);
    
    virtual  bool onTouchBegan (Touch *touch,Event *event);
    virtual void onEnter();
    
    
};


#endif



