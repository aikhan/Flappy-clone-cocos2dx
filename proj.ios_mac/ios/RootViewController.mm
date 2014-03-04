#import "RootViewController.h"
#import "cocos2d.h"
#import "EAGLView.h"


#include "GameEndLayer.h"

@implementation RootViewController

// GKLeaderboardViewControllerのDelegate
-(void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController
{
    [self dismissViewControllerAnimated:YES completion:nil];
}

// GKAchievementViewControllerのDelegate
-(void)achievementViewControllerDidFinish:(GKAchievementViewController *)viewController
{
    [self dismissViewControllerAnimated:YES completion:nil];
}


/*
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
 - (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
 if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
 // Custom initialization
 }
 return self;
 }
 */

/*
 // Implement loadView to create a view hierarchy programmatically, without using a nib.
 - (void)loadView {
 }
 */

/*
 // Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
 - (void)viewDidLoad {
 [super viewDidLoad];
 }
 
 */
// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsPortrait(interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
   // return UIInterfaceOrientationMaskPortraitUpsideDown;
    return UIInterfaceOrientationMaskAllButUpsideDown;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation {
	[super didRotateFromInterfaceOrientation:fromInterfaceOrientation];
    
	CGSize s = CGSizeMake([[CCEAGLView sharedEGLView] getWidth], [[CCEAGLView sharedEGLView] getHeight]);
    
	cocos2d::Application::getInstance()->applicationScreenSizeChanged((int) s.width, (int) s.height);
}

//fix not hide status on ios7
- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}


-(void) loadEmailView:(int)scoring
{
    Class mailClass = (NSClassFromString(@"MFMailComposeViewController"));
    
    if (mailClass != nil)
    {
        
        MFMailComposeViewController *pickerMail = [[MFMailComposeViewController alloc] init];
            pickerMail.mailComposeDelegate =self;
        
        [pickerMail mailComposeDelegate];
        
       // GameEndLayer* temp;
     //   int tempscore=temp->getScore();
        
        int tempscore=scoring;
        
        
        String* Subject=String::createWithFormat("%s%d%s", "I Scored ", tempscore, " :D \nDo you Dare to compare?");
          NSString *txtnew = [[NSString alloc] initWithCString:Subject->getCString() encoding:NSUTF8StringEncoding];
        [pickerMail setSubject:txtnew];
        
        // Fill out the email body text
 //       String *emailBody = @"body";
      
        
        
        cocos2d::String* emailBody=cocos2d::String::createWithFormat("%s%d%s", "Hey I have scored ", tempscore, " in Flappy Birds Easy.\nDo you dare to compare your's?\nYou can download the free version from bit.ly/1bHhuuq\n\nLet me know when you break my record..!!");
        
        
        NSString *txtnew1 = [[NSString alloc] initWithCString:emailBody->getCString() encoding:NSUTF8StringEncoding];
        [pickerMail setMessageBody:txtnew1 isHTML:NO];
        
//        RootViewController *rootViewController = (RootViewController*)[UIApplication sharedApplication].keyWindow.rootViewController;
        [self presentViewController:pickerMail animated:YES completion:nil];
        
        [pickerMail setNeedsStatusBarAppearanceUpdate];
        
        
        
        [pickerMail release];
        
        
        // [pickerMail dismissModalViewControllerAnimated:YES];
        
    }
    else
    {
        
    }

}






- (void)mailComposeController:(MFMailComposeViewController*)controller didFinishWithResult:(MFMailComposeResult)result error:(NSError*)error
{

//     RootViewController *rootViewController = (RootViewController*)[UIApplication sharedApplication].keyWindow.rootViewController;
  
     [self dismissModalViewControllerAnimated:YES];
    switch (result) {
        case MFMailComposeResultSent:
        {
            UIAlertView *alert = [[UIAlertView alloc]
                                  initWithTitle: @"Sending Result"
                                  message: @"Email Sent"
                                  delegate: nil
                                  cancelButtonTitle:@"OK"
                                  otherButtonTitles:nil];
            [alert show];
            [alert release];
        }
            
            
            break;
        case MFMailComposeResultSaved:
        {
            UIAlertView *alert = [[UIAlertView alloc]
                                  initWithTitle: @"Email Result"
                                  message: @"Email Saved"
                                  delegate: nil
                                  cancelButtonTitle:@"OK"
                                  otherButtonTitles:nil];
            [alert show];
            [alert release];
        }
            
            break;
        case MFMailComposeResultCancelled:
        {
            UIAlertView *alert = [[UIAlertView alloc]
                                  initWithTitle: @"Email Result"
                                  message: @"Email Cancelled"
                                  delegate: nil
                                  cancelButtonTitle:@"OK"
                                  otherButtonTitles:nil];
            [alert show];
            [alert release];
        }
            
            break;
        case MFMailComposeResultFailed:
        {
            UIAlertView *alert = [[UIAlertView alloc]
                                  initWithTitle: @"Email Result"
                                  message: @"Email Failed"
                                  delegate: nil
                                  cancelButtonTitle:@"OK"
                                  otherButtonTitles:nil];
            [alert show];
            [alert release];
        }
            
            break;
        default:
        {
            UIAlertView *alert = [[UIAlertView alloc]
                                  initWithTitle: @"Email Result"
                                  message: @"Email Other Error"
                                  delegate: nil
                                  cancelButtonTitle:@"OK"
                                  otherButtonTitles:nil];
            [alert show];
            [alert release];
        }
            
            break;
    }
}


@end
