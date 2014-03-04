//
//  AdManagerBridge.cpp
//  FlappyBirdsRevenge
//
//  Created by Waqas Hassan on 11/02/2014.


#import <Social/Social.h>

#include "cocos2d.h"
#include "fbBridge.h"

#import "GameEndLayer.h"

#import "Global.h"
#import "MainScene.h"

#import "MKStoreManager.h"
#import "social/SLComposeViewController.h"

#import <MessageUI/MFMailComposeViewController.h>
#import "AppController.h"
//#import "EAGLView.h"


#import "AppDelegate.h"
#import "RootViewController.h"
#import "AppSpecificValues.h"
#import "RateManager.h"
#include "UIDevice+HardwareString.h"
#include "RootViewController.h"


#define SYSTEM_VERSION_GREATER_THAN(v)              ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedDescending)

USING_NS_CC;

bool fbBridge::checkVersion()
{
   
    NSString *ver = [[UIDevice currentDevice] systemVersion];
    
    float ver_float = [ver floatValue];
    
    if (ver_float < 6.0)
        return false;
    else
        return true;
}



void fbBridge::shareFB(String* text)
{
 //   if([SLComposeViewController isAvailableForServiceType:SLServiceTypeFacebook])
    {
        
        SLComposeViewController *controller = [SLComposeViewController composeViewControllerForServiceType:SLServiceTypeFacebook];
        NSString *txtnew = [[NSString alloc] initWithCString:text->getCString() encoding:NSUTF8StringEncoding];
        
        
        [controller setInitialText:txtnew];
        [controller addURL:[NSURL URLWithString:@"bit.ly/1bHhuuq"]];
        [controller setCompletionHandler:^(SLComposeViewControllerResult result)
        {
            
            switch (result)
            {
                case SLComposeViewControllerResultCancelled:
                    NSLog(@"Post Canceled");
                    break;
                case SLComposeViewControllerResultDone:
                    NSLog(@"Post Sucessful");
                    break;
                    
                default:
                    break;
            }
            
        }];
        
        
         
        RootViewController *rootViewController = (RootViewController*)[UIApplication sharedApplication].keyWindow.rootViewController;
        [rootViewController presentViewController:controller animated:YES completion:nil];
        
        
    }
}


void fbBridge::shareTwitter(String* text)
{
  //  if([SLComposeViewController isAvailableForServiceType:SLServiceTypeFacebook])
    {
        
        SLComposeViewController *controller = [SLComposeViewController composeViewControllerForServiceType:SLServiceTypeTwitter];
        NSString *txtnew2 = [[NSString alloc] initWithCString:text->getCString() encoding:NSUTF8StringEncoding];
        [controller setInitialText:txtnew2];
        
        
    // [controller addURL:[NSURL URLWithString:@"bit.ly/1bHhuuq"]];
        
        RootViewController *rootViewController = (RootViewController*)[UIApplication sharedApplication].keyWindow.rootViewController;
        [rootViewController presentViewController:controller animated:YES completion:nil];

    }
}

void fbBridge::sendMail(String* subject,  String* body, int a)
{

     RootViewController *rootViewController = (RootViewController*)[UIApplication sharedApplication].keyWindow.rootViewController;
    [rootViewController loadEmailView:a];
    

}
void fbBridge::rateMe()
{
    [[RateManager sharedManager] showReviewApp ];
}

