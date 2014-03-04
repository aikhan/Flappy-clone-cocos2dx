/*
 
 File: AppSpecificValues.h
 Abstract: Basic introduction to GameCenter
 
 Version: 1.0
 */
#ifndef __FlyingBirdEasyy__AppSpecValues__
#define __FlyingBirdEasyy__AppSpecValues__

#define maxBirds 5
#define MaxBirdstoShow 10///i.e 10 after combining both left and right

static int hit;
static int miss;


#ifdef FreeApp
#define kEasyLeaderboardID @"com.semanticnotion.flappyeasyfree.leaderboard"
#endif

#ifdef PaidApp
#define kEasyLeaderboardID @"com.semanticnotion.flappyeasyfree.leaderboard"
#endif


//Achievement IDs
#define kAchievement1 @""
#define kAchievement2 @""
#define kAchievement3 @""
#define kAchievement4 @""

#endif