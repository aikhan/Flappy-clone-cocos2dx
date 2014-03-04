/* ?? Code By: Kashif Asif */
#ifndef kashif
#define kashif
#include "Global.h"
#include "Constants.h"
USING_NS_CC;

float g_fScaleR = 1.0;
GameScene *g_lGameLayer;
MainScene *g_lMainLayer;
int g_iLives;
float G_ORG_WIDTH = 288;
float G_ORG_HEIGHT = 512;


float G_SWIDTH=1536; //Screen width
float G_SHEIGHT=2048;   //Screen height

float G_SCALEX= (G_SWIDTH * g_fScaleR / G_ORG_WIDTH);
float G_SCALEY= (G_SHEIGHT * g_fScaleR / G_ORG_HEIGHT);


float getX(int x)
{
    float fx;
    
    fx = G_SWIDTH * x / G_ORG_WIDTH;
    return fx;
}

float getY(int y)
{
    float fy;
    fy = G_SHEIGHT - G_SHEIGHT * y / G_ORG_HEIGHT;
    return fy;
}


void loadGameInfo()
{
//    g_nCompleteLevel =CCUserDefault::sharedUserDefault()->getIntegerForKey("Competed");
//    
//    for (int i = 0; i < LEVEL_COUNT; i++)
//    {
//        String *str = String::createWithFormat("Time%d", i);
//        g_nMoves[i] = CCUserDefault::sharedUserDefault()->getIntegerForKey(str);
//        
//
//    }
//    
//    for (int i = 0; i < LEVEL_COUNT; i++)
//    {
//        String *str = String::createWithFormat("Time%d", i);
//        g_nTimes[i] = CCUserDefault::sharedUserDefault()->getIntegerForKey(str);
//    }
}

void saveGameInfo()
{
//   NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
//    [userDefaults setInteger:g_nCompleteLevel forKey:@"Completed"];
//    
//    CCUserDefault::sharedUserDefault()->setIntegerForKey("Completed", g_nCompleteLevel);
//    
//    
//     for (int i = 0; i < LEVEL_COUNT; i++)
//     {
//         String *str = String::createWithFormat("Move%d", i);
//    
//         CCUserDefault::sharedUserDefault()->setIntegerForKey(str->getCString(), g_nMoves[i]);
//         
//    }
//     
//     for (int i = 0; i < LEVEL_COUNT; i++)
//     {
//         String *str = String::createWithFormat("Time%d", i);
//         CCUserDefault::sharedUserDefault()->setIntegerForKey(str->getCString(), g_nTimes[i]);
//     }
}




 
 




CCSpriteFrame *getSpriteFromAnimation(CCAnimation *ani, int index)
{
//    CCAnimationFrame *frame = [ani.frames objectAtIndex:index];
//    CCSprite *frame = ani->getFrames();
//    
    //Array kashif = ;
    
    
    
 //   return frame.spriteFrame;
    
    
}


void KsetScale(CCNode *node, int nRatio)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
   
    G_SWIDTH=visibleSize.width; //Screen width
    G_SHEIGHT=visibleSize.height;
    //Screen height
   
    G_SCALEX= (G_SWIDTH * g_fScaleR / G_ORG_WIDTH);
    G_SCALEY= (G_SHEIGHT * g_fScaleR / G_ORG_HEIGHT);
    if(nRatio == RATIO_XY)
    {
        node->setScaleX(G_SCALEX);
        node->setScaleY(G_SCALEY);
        
    }
    else if(nRatio == RATIO_X)
        node->setScale(G_SCALEX);
    else if(nRatio == RATIO_Y)
        node->setScale(G_SCALEY);
    
}
#endif