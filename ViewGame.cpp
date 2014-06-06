//
//  ViewGame.cpp
//  DemoInduccion
//
//  Created by Max on 5/11/14.
//
//

#include "ViewGame.h"

#include <CCGeometry.h>

#include "Player.h"

#define COCOS2D_DEBUG 1

USING_NS_CC;

ViewGame::ViewGame()
{
    iPx = 0;
    iPy = 0;
    iPwidth = 0;
    iPheight = 0;
    iPG = 0;
    iPvx = 0;
    iPvy = 0;
    bHorizontalRight = 0;
    bHorizontalLeft = 0;
    bVerticalMinus = 0;
    bVerticalPlus = 0;
    
    platformArray[ 0 ] = new Platform;
    
    platformArray[ 1 ] = new Platform;
    
    platformArray[ 2 ] = new Platform;
}

ViewGame::~ViewGame()
{
    delete platformArray[3];
}


bool ViewGame::init ()
{
    
    if( !Layer :: init() )
        return false;
    
    Size visibleSize = Director::getInstance () -> getVisibleSize ();
    //Point origin = Director::getInstance () -> getVisibleOrigin ();
    
    auto layer = this;
    
    platformArray[ 0 ] -> addPlatform( layer,  0,  0,  0,  visibleSize.width,  120  );
    
    platformArray[ 1 ] -> addPlatform( layer,  0,  130,  120,  visibleSize.width/10,  50  );
    
    platformArray[ 2 ] -> addPlatform( layer,  0,  300,  180,  visibleSize.width/12,  30  );
    
    this->schedule( schedule_selector ( ViewGame::update ) );

    
    return 1;
}

void ViewGame::update(float dt)
{
    Player::getAllValues(iPx, iPy, iPwidth, iPheight, iPG, iPvx, iPvy);
    this -> checkForCollisions();
}

void ViewGame::checkForCollisions()
{
    
   // for ( int i = 0; i < 3; i ++ )
    //{
            BoxCollision :: checkCollision( platformArray[ 1 ] -> platform, iPx, iPy, iPvx, iPvy, iPwidth, iPheight, iPG, bHorizontalLeft, bHorizontalRight, bVerticalPlus, bVerticalMinus );
            
            this -> collisions();
            
      //      if( bHorizontalLeft || bHorizontalRight || bVerticalMinus || bVerticalPlus )
        //        break;
    //}  //For
    
    if ( bVerticalMinus )
        Player::changeBoolAt(true, 1);
    else
        Player::changeBoolAt(false, 1);
    
}

void ViewGame::collisions()
{
    
}
