/* ?? Code By: Kashif Asif */

//
#ifndef Semantic
#define Semantic
//#include <Foundation/Foundation.h>
#include "cocos2d.h"
//#include <MessageUI/MFMailComposeViewController.h>
USING_NS_CC;



class GameEndLayer:public cocos2d::Layer

{
public:
    
    static Scene* createScene();
    
    
    virtual bool init();
    
    
    CREATE_FUNC(GameEndLayer);
    
    CCMenu *menu;
    CCMenuItemSprite *m_mOk, *m_mTW, *m_mFB, *m_mFreeGame, *m_mML;
    void setScore(int score);
   
    
   // bool Livespurchased=false;
    
    
    void initVariable();
    void createBackground();
    void onClickContinue(Object* temp);
    void onClickFree(Object* temp);
    void onClickFB(Object* temp);
    void onClickTW(Object* temp);
    void onClickMail(Object* temp);
    void onClickOk(Object* temp);
    void showPurchaseAlert(String *messsage,  int tag);
    void playMore();
    int getScore();
    
    //    void alertView(UIAlertView *alertView, int buttonIndex);

    int scores=0;
    
};


#endif


