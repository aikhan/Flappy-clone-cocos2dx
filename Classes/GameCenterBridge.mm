//
//  GameCenterBridge.cpp
//  FlappyBirdsRevenge
//
//  Created By: kashif Asif

#include "GameCenterBridge.h"
#import "GameCenterManager.h"
#include "AppController.h"
#include "AppSpecificValues.h"


static GameCenterManager *gameCenterManager;


GameCenterBridge::GameCenterBridge()
{
    
}

void GameCenterBridge::initGameCenter()
{
//	if (viewController2 != nil)
//		return;
//	viewController2 = [GCViewController alloc];
	
    
	if ([GameCenterManager isGameCenterAvailable])
	{
		gameCenterManager = [[GameCenterManager alloc] init];
		[gameCenterManager authenticateLocalUser];
	}
}

void GameCenterBridge::ReportScore(int score)
{
//    GameCenterManager *gameCenterManager;
    initGameCenter();
//    if ([GameCenterManager isGameCenterAvailable])
//	{
//		gameCenterManager = [[[GameCenterManager alloc] init] autorelease];
//        //		[gameCenterManager setDelegate:self];
//		[gameCenterManager authenticateLocalUser];
//	}
    
//	NSString* identifier= NULL;
//    
//	if (score>=2000) {
//		identifier= kAchievement4;
//	}
//	else if (score>=1500) {
//		identifier= kAchievement3;
//	}
//	else if (score>=1000) {
//		identifier= kAchievement2;
//	}
//	else {
//		identifier= kAchievement1;
//	}
//	if(identifier!= NULL){
//		[gameCenterManager submitAchievement: identifier percentComplete:100.0];
//	}
//    if(score>0){
//		[gameCenterManager reportScore:score forCategory: kEasyLeaderboardID];
//	}
    
    
    submitScore(score);
}

void GameCenterBridge::submitScore(int score)
{
    if(score>0){
		[gameCenterManager reportScore:score forCategory: kEasyLeaderboardID];
	}
}

void GameCenterBridge::showScores()
{
    AppController* appController = (AppController*) [UIApplication sharedApplication].delegate;
    [appController showScores];

}

