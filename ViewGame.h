//
//  ViewGame.h
//  DemoInduccion
//
//  Created by Max on 5/11/14.
//
//

#ifndef __DemoInduccion__ViewGame__
#define __DemoInduccion__ViewGame__

#include <iostream>

#include "cocos2d.h"

//#include "Player.cpp"

#include "BoxCollision.h"

#include "Platform.h"

class ViewGame: public cocos2d::Layer
{
private:
    int iPx, iPy, iPwidth, iPheight, iPG, iPvx, iPvy;
    
    bool bHorizontalRight, bHorizontalLeft, bVerticalPlus, bVerticalMinus;
    
    void checkForCollisions();
    
    void collisions();
    
public:
    
    ViewGame();
    virtual ~ViewGame();
    
    virtual bool init ();
    
    void update(float dt);
    
    
    Platform * platformArray [ 3 ];
    
    CREATE_FUNC( ViewGame );
    
    
    
};

#endif /* defined(__DemoInduccion__ViewGame__) */
