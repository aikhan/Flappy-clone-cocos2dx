//
//  SettingsManager.cpp
//  FlappyBirdsRevenge
//
//  Created by Waqas Hassan on 04/02/2014.
//
//

// We have 2 sets of graphics. One for iphone 320 * 480  and one for ipad 768 * 1024

#include "SettingsManager.h"
#include "cocos2d.h"
USING_NS_CC;

SettingsManager::SettingsManager()
{
    checkForDeviceType();
}

void SettingsManager::checkForDeviceType()
{
    Size size = CCDirector::getInstance()->getWinSize();
    isIPhone5 = false;
    isIPhone4 = false;
    isIPad = false;
    isIPhone = false;
    isBigScreen = true;
    

    if (size.width == 1136) {
        isIPhone5 = true;
        
    } else if(size.width == 1024) {
        isIPad = true;
       
    }
    else if (size.width == 960)
    {
        isIPhone4 = true;
    }
    else if (size.width == 480){
        isIPhone = true;
        isBigScreen = false;
    }
    
    if (size.width<=480) {
        isBigScreen = false;
    }
    else
    {
        isBigScreen = true;
    }
   
}
