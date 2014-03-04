// Flying Bird Easy
// Kashif Asif


#include "AdManagerBridge.h"
#import "SNAdsManager.h"


void AdManagerBridge::giveMeBootupAd()
{
    [[SNAdsManager sharedManager] giveMeBootUpAd];
}
void AdManagerBridge::giveMePaidBootupAd()
{
    [[SNAdsManager sharedManager] giveMePaidFullScreenAd];
}
void AdManagerBridge::giveMeWillEnterForegroundAd()
{
    [[SNAdsManager sharedManager] giveMeWillEnterForegroundAd];
}
void AdManagerBridge::giveMeOnBecomeActiveAd()
{
    [[SNAdsManager sharedManager] giveMeBootUpAd];
}

void AdManagerBridge::giveMeFullScreenAd()
{
    [[SNAdsManager sharedManager] giveMeFullScreenAd];
}

void AdManagerBridge::hideBannerAd()
{
     [[SNAdsManager sharedManager] hideBannerAd];
}
void AdManagerBridge::giveMeBannerAdAtTop()
{
    [[SNAdsManager sharedManager] giveMeBannerAdAtTop];
}

void AdManagerBridge::giveMeBannerAd()
{
    [[SNAdsManager sharedManager] giveMeBannerAd];
}

void AdManagerBridge::giveMeFreeGamesAd()
{
    [[SNAdsManager sharedManager] giveMeLinkAd];
}

void AdManagerBridge::giveMeThirdGameOverAd()
{
    [[SNAdsManager sharedManager] giveMeThirdGameOverAd];
}

void AdManagerBridge::giveMeMoreGamesAd()
{
    [[SNAdsManager sharedManager] giveMeMoreAppsAd];
}
void AdManagerBridge::giveMeGameOverAdd()
{
    [[SNAdsManager sharedManager] giveMeGameOverAd];
}

