//
//  SettingsManager.h
//  FlappyBirdsRevenge
//
//  Created by Waqas Hassan on 04/02/2014.
//
//

#ifndef __FlappyBirdsRevenge__SettingsManager__
#define __FlappyBirdsRevenge__SettingsManager__

#include <iostream>

class SettingsManager
{
 
public:
    bool hasInAppPurchaseBeenMade;
    bool isBigScreen;
    bool isSmallScreen;
    bool isIPhone5;
    bool isIPhone4;
    bool isIPhone;
    bool isIPad;
    int gameOverCounter;
    int ammoAtHand;
    float G_SCALEY=0.5;
    float G_SWIDTH=0.5;
    
    
    
    SettingsManager();
    SettingsManager(SettingsManager const&);              // Don't Implement
    void operator=(SettingsManager const&);
    
     static SettingsManager& getInstance()
    {
        static SettingsManager instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }
    
    
    
    void checkForDeviceType();
    
};


#endif /* defined(__FlappyBirdsRevenge__SettingsManager__) */
