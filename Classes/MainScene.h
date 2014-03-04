//
//  MainScene.h
//  Flappy Bird
//
//  Created by JTK on 1/20/14.
//  Copyright 2014 org. All rights reserved.
//

//#include <Foundation/Foundation.h>


#ifndef MainSceneYo_YO
#define MainSceneYo_YO


//#include<iostream>
#include "cocos2d.h"
USING_NS_CC;



class MainScene:public cocos2d::Layer

{
public:
    
    static  Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MainScene);
    
    

    
    CCMenu *menu;
    CCMenuItemSprite *m_mStart;
    CCMenuItemSprite *m_mScore;
    CCMenuItemSprite *m_mRate;
    CCMenuItemSprite *m_mMore, *removeAdd, *restore;
    
    CCSprite *m_sBirdSprite;
    CCSprite *m_sLogoSprite;
    CCSprite *m_sGroundSprite[2];
    Sprite* mainScreen;
    
    void updateRateButton();
    void initVariable();
    void createBackground();
    
    void bird_fly_animation();
    Animation *animation_bird_fly;
    
    
    void onClickStart(Object * sender);
    void onClickScore(Object * sender);
    void onClickRate(Object * sender);
    void onClickMore(Object * sender);
    
    void onClickRemove(Object * Sender);
    
    void Update(float dt);
    
    float g_fScaleR = 1.0;
    float G_ORG_WIDTH = 288;
    float G_ORG_HEIGHT = 512;
    float G_SWIDTH=1536;   //Screen width
    float G_SHEIGHT=2048;   //Screen height
    
    float G_SCALEX= (G_SWIDTH * g_fScaleR / G_ORG_WIDTH);
    float G_SCALEY= (G_SHEIGHT * g_fScaleR / G_ORG_HEIGHT);
    

};

#endif








