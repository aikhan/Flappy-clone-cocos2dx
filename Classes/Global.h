/* ?? Code By: Kashif Asif */

#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include "cocos2d.h"
//#import <UIKit/UIDevice.h>
#include "GameConfig.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include  "SettingsManager.h"




//#define G_ORG_WIDTH 288
//#define G_ORG_HEIGHT 512
#ifdef UI_USER_INTERFACE_IDIOM//()
#define IS_IPAD() (SettingsManager::getInstance().isBigScreen)


#else
#define IS_IPAD() (false)
#endif

//#define G_SWIDTH    (IS_IPAD() ? 768: [[CCDirector sharedDirector] winSize].width)  //Screen width
//#define G_SHEIGHT   (IS_IPAD() ? 1024: [[CCDirector sharedDirector] winSize].height)   //Screen height
//
//#define G_SCALEX    (G_SWIDTH * g_fScaleR / G_ORG_WIDTH)
//#define G_SCALEY    (G_SHEIGHT * g_fScaleR / G_ORG_HEIGHT)


//extern MenuScene *g_layerMenu;
//extern GameScene *g_layerGame;
//http://we.tl/Heys8cnCrP



//int g_nCompleteLevel;


typedef enum
{
    RATIO_XY = 0,
    RATIO_X,
    RATIO_Y,
}Ratio;

typedef enum{
    NORMALTOOLS = 588,
} TOOLSTATE;

extern float g_fScaleR; //For some retina things such text
extern GameScene *g_lGameLayer;
extern MainScene *g_lMainLayer;
extern int g_iLives;
float getX(int x);
float getY(int y);







void loadGameInfo();
void updateGameInfo();






CCAnimation *newAnimation(String *name, int nStartNum, int nFrameNum, bool isAscending, float fDelayPerUnit);
CCSpriteFrame *getSpriteFromAnimation(CCAnimation *ani, int index);
void KsetScale(CCNode *node, int nRatio);
CCLabelTTF *addTextToButton(CCPoint pos, CCNode *scene, String *str, int fontSize, int z);
#endif