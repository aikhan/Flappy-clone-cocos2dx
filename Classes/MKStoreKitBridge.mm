//
//  MKStoreKitBridge.cpp
//  FlappyBirdsRevenge
//
//  Created by Waqas Hassan on 11/02/2014.
//
//

#import "MKStoreKitBridge.h"
#import "MKStoreManager.h"
#include "SettingsManager.h"
#include "cocos2d.h"
#import "MMProgressHUD.h"
#import "MMProgressHUDOverlayView.h"
#include "GameEndLayer.h"
#include "Constants.h"
#include "Global.h"

#ifdef FreeApp
#define featureAIdVar @"com.semanticnotion.flappybirdeasyfree.removeads"
#define buyAmmo100 @"com.semanticnotion.flappyrevenge.3lives"
#define buyAmmo300 @"com.semanticnotion.flappyrevenge.ammo300"
#define buyAmmo600 @"com.semanticnotion.flappyrevenge.ammo600"
#define buyAmmo1000 @"com.semanticnotion.flappyrevenge.ammo1000"
#endif

#ifdef PaidApp
#define featureAIdVar @""
#define buyAmmo100 @"com.semanticnotion.flappyrevengepaid.ammo100"
#define buyAmmo300 @"com.semanticnotion.flappyrevengepaid.ammo300"
#define buyAmmo600 @"com.semanticnotion.flappyrevengepaid.ammo600"
#define buyAmmo1000 @"com.semanticnotion.flappyrevengepaid.ammo1000"
#endif

USING_NS_CC;


extern CCMenuItemSprite *purchase;
extern CCMenuItemSprite *m_mContinue;
extern bool  Livespurchased;



void MKStoreKitBridge::callRemoveAds()
{
//    [MKStoreManager sharedManager];
    
    
        [MMProgressHUD setPresentationStyle:MMProgressHUDPresentationStyleSwingLeft];
        [MMProgressHUD showWithTitle:@"Purchasing" status:@"Please Wait"];
    //
    [[MKStoreManager sharedManager] buyFeature:featureAIdVar
                                    onComplete:^(NSString* purchasedFeature,
                                                 NSData* purchasedReceipt,
                                                 NSArray* availableDownloads)
     {
         
         
         //[[SettingsManager sharedManager].rootViewController hideLoadingView];
         NSLog(@"Purchased: %@", purchasedFeature);
         SettingsManager::getInstance().hasInAppPurchaseBeenMade = true;
         CCUserDefault::sharedUserDefault()->setBoolForKey("inapp1", true);
         
         //
         //         NSUserDefaults *standardUserDefaults = [NSUserDefaults standardUserDefaults];
         //         [standardUserDefaults setBool:true forKey:@"inapp"];
         //         [standardUserDefaults synchronize];
         //[[SNAdsManager sharedManager] hideBannerAd];
                  [MMProgressHUD dismissWithSuccess:@"Enjoy your game without Adds! "];
         
         //         [self removeChildByTag:6 cleanup:YES];
     }
     onCancelled:^
     {
         //         NSLog(@"Something went wrong");
         
                  [MMProgressHUD dismissWithError:@"Unable to process your transaction.\nPlease try again in a moment." title:@"Error"];
         
     }];
}
/*
void MKStoreKitBridge::ShowbuyLivePopUp()
{
    UIAlertView *alert= [[UIAlertView alloc] initWithTitle:@"Buy More Lives" message:@"Are you sure you want to buy Lives" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"yes", nil];
    [alert show];
    
}
void MKStoreKitBridge::alertView(UIAlertView *alertView, NSInteger buttonIndex)
{
    
}
*/
void MKStoreKitBridge::initialiseWithMainscene()
{

}
void MKStoreKitBridge::callIAP(int ammoIndex)
{
   
//#ifdef FreeApp
    NSString *buyingId = @"";
    switch (ammoIndex) {
        case 1:
            buyingId = buyAmmo100;
            break;
        case 2:
            buyingId = buyAmmo300;
            break;
        case 3:
            buyingId = buyAmmo600;
            break;
        case 4:
            buyingId = buyAmmo1000;
            break;
            
        default:
            break;
    }
    [MMProgressHUD setPresentationStyle:MMProgressHUDPresentationStyleSwingLeft];
    [MMProgressHUD showWithTitle:@"Purchasing" status:@"Please Wait"];
    [[MKStoreManager sharedManager] buyFeature:buyingId
                                    onComplete:^(NSString* purchasedFeature,
                                                 NSData* purchasedReceipt,
                                                 NSArray* availableDownloads)
     {
         
        
         NSLog(@"Purchased: Ammo");
         NSUserDefaults *standardUserDefaults = [NSUserDefaults standardUserDefaults];
         int x = SettingsManager::getInstance().ammoAtHand;
         switch (ammoIndex) {
             case 1:
                 x += 100;
                 break;
             case 2:
                 x  += 300;
                 break;
             case 3:
                 x  += 600;
                 break;
             case 4:
                 x  += 1000;
                 break;
                 
             default:
                 break;
         }
         SettingsManager::getInstance().ammoAtHand = x;
         CCUserDefault::sharedUserDefault()->setIntegerForKey("totalAmmo", SettingsManager::getInstance().ammoAtHand);
         [MMProgressHUD dismissWithSuccess:@"Got More Lives, Fly More !"];
       
         g_iLives+=3;
         Livespurchased=true;
         purchase->setEnabled(false);
         purchase->setVisible(false);
         m_mContinue->setVisible(true);
         m_mContinue->setEnabled(true);
         
         
     }
      onCancelled:^
     {
         NSLog(@"Something went wrong");
         [MMProgressHUD dismissWithError:@"Unable to process your request.\nPlease try again in a moment." title:@"Error"];
     }];
    
//#endif
    
}
void MKStoreKitBridge::initialise()
{
     [MKStoreManager sharedManager];
}
void MKStoreKitBridge::callRestoreIAP()
{
    
//#ifdef FreeApp
    [MMProgressHUD setPresentationStyle:MMProgressHUDPresentationStyleSwingRight];
    [MMProgressHUD showWithTitle:@"Restoring" status:@"Please Wait"];
    [[MKStoreManager sharedManager] restorePreviousTransactionsOnComplete:^{
        
        if([MKStoreManager isFeaturePurchased: featureAIdVar] == NO) {
            [MMProgressHUD dismissWithError:@"No In app purchases to restore." title:@"Error"];
        }
        else {
            SettingsManager::getInstance().hasInAppPurchaseBeenMade = true;
            CCUserDefault::sharedUserDefault()->setBoolForKey("inapp1", true);
            
            NSLog(@"true");
        }
        [MMProgressHUD dismissWithSuccess:@"Success!"];
        
    } onError:^(NSError *A) {
        [MMProgressHUD dismissWithError:@"Unable to process your transaction.\nPlease try again in a moment." title:@"Error"];
    }];
//#endif
    
}


