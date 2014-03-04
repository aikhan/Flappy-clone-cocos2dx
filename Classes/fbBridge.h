// Created By: Kashif Asif


//
#include "cocos2d.h"


USING_NS_CC;

#ifndef SemanticNotion_Flying
#define SemanticNotion_Flying




class fbBridge 
{
public:
    void shareFB(String*  text);
    void shareTwitter(String* text);
    void sendMail(String* subject,  String* body, int a);
    void rateMe();
    bool checkVersion();
    
    
    
};



#endif 
