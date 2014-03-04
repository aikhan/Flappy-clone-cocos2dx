/* ?? Code By: Kashif Asif */
//

#ifndef _GAME_CONFIG_H
#define _GAME_CONFIG_H
#import "cocos2d.h"
#import "Constants.h"
#include "SimpleAudioEngine.h"

#define TEXT_TAG    1
//void FX_BTN()
//{
//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sfx_swooshing.mp3");
//}
USING_NS_CC;

typedef enum
{
    D_EASY = 0,
    D_MEDIUM,
    D_HARD,
}DIFFICULTY;

static bool g_bMusicMute= false;
static bool g_bSoundMute= false;

static bool g_bIsTimeMode= true;

static int g_nDifficulty= D_EASY;

static int g_nCurrentLevel =0;
static int g_nCompleteLevel;
static int g_nTotalScore =0;



static CCAnimation *g_frmBird;

static CCAnimation *g_frmObstacle;

#endif
