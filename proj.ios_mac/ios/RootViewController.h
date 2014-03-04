#import <UIKit/UIKit.h>
#import <GameKit/GameKit.h>
#import <MessageUI/MFMailComposeViewController.h>


@interface RootViewController : UIViewController <GKAchievementViewControllerDelegate, GKLeaderboardViewControllerDelegate, MFMailComposeViewControllerDelegate> {
    
}
- (BOOL) prefersStatusBarHidden;
//- (void)mailComposeController:(MFMailComposeViewController*)controller didFinishWithResult:(MFMailComposeResult)result error:(NSError*)error;

- (void) sendMail:(NSString *)subject :(NSString *)body;
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation;
-(void) loadEmailView:(int)scoring;




@end
