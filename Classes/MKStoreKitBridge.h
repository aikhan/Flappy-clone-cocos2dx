//
//  MKStoreKitBridge.h
//  FlappyBirdsRevenge
//
//  Created by Waqas Hassan on 11/02/2014.
//
//
#include "MainScene.h"

#ifndef __FlappyBirdsRevenge__MKStoreKitBridge__
#define __FlappyBirdsRevenge__MKStoreKitBridge__



class MKStoreKitBridge
{
public:
    void callRemoveAds();
    void callIAP(int ammoIndex);
    void callRestoreIAP();
    void initialise();
    void ShowbuyLivePopUp();
//    void alertView(UIAlertView *alertView, NSInteger buttonIndex);
    
    
    
    void initialiseWithMainscene();
    
};
#endif /* defined(__FlappyBirdsRevenge__MKStoreKitBridge__) */
