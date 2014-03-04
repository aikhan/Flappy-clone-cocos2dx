//
//  GameCenterBridge.h
//  FlappyBirdsRevenge
//
//  Created by Waqas Hassan on 11/02/2014.
//
//

#ifndef __FlappyBirdsRevenge__GameCenterBridge__
#define __FlappyBirdsRevenge__GameCenterBridge__


class GameCenterBridge
{
    
public:
    
    GameCenterBridge();
    GameCenterBridge(GameCenterBridge const&);              // Don't Implement
    void operator=(GameCenterBridge const&);
    
    static GameCenterBridge& getInstance()
    {
        static GameCenterBridge GCinstance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return GCinstance;
    }
    
    
    void initGameCenter();
    void ReportScore(int score);
    void submitScore(int score);
    void showScores();
    
    
};


#endif /* defined(__FlappyBirdsRevenge__GameCenterBridge__) */
