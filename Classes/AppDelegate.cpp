#include "AppDelegate.h"
#include "GameScene.h"
#include "MainScene.h"
#include "AdManagerBridge.h"
#include "GameCenterBridge.h"
#include "MKStoreKitBridge.h"
#include "SettingsManager.h"
#include    "SimpleAudioEngine.h"
USING_NS_CC;



AppDelegate::AppDelegate() {
    
}

AppDelegate::~AppDelegate()
{
}
cocos2d::CCMenuItemSprite *purchase, *m_mContinue;
bool  Livespurchased=false;


bool AppDelegate::applicationDidFinishLaunching()
{
    auto director = Director::getInstance();
    auto eglView = EGLView::getInstance();
    
    director->setOpenGLView(eglView);
    director->setDisplayStats(false);
    director->setAnimationInterval(1.0 / 60);
    
    AdManagerBridge *adManager;
    GameCenterBridge::getInstance().initGameCenter();
    MKStoreKitBridge *storeBridge;
    storeBridge->initialise();
    
    configureSettings();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bg.mp3", true);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1);
    
#ifdef FreeApp
    
    if (!SettingsManager::getInstance().hasInAppPurchaseBeenMade)
    {
        adManager->giveMeBootupAd();
    }
    
#endif
    
#ifdef PaidApp
    SettingsManager::getInstance().hasInAppPurchaseBeenMade = true;
    
    adManager->giveMePaidBootupAd();
#endif
    
    auto scene = MainScene::createScene();
    
    director->runWithScene(scene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
    AdManagerBridge *bridge;
    
    
        bridge->giveMePaidBootupAd();
    
}

void AppDelegate::configureSettings()
{
    int appStartupCount;
    
    appStartupCount = CCUserDefault::sharedUserDefault()->getIntegerForKey("startupcount");
    appStartupCount++;
    CCUserDefault::sharedUserDefault()->setIntegerForKey("startupcount", appStartupCount);
    
    
    
    
    if (appStartupCount <= 1) {
        
        
#ifdef FreeApp
        CCUserDefault::sharedUserDefault()->setBoolForKey("inapp", false);
        SettingsManager::getInstance().hasInAppPurchaseBeenMade = false;
#endif
        
#ifdef PaidApp
        CCUserDefault::sharedUserDefault()->setBoolForKey("inapp1", true);
        SettingsManager::getInstance().hasInAppPurchaseBeenMade = true;
#endif
   
        
        
        
    }
    else
    {
        SettingsManager::getInstance().hasInAppPurchaseBeenMade = CCUserDefault::sharedUserDefault()->getBoolForKey("inapp1");
        
    }
}

