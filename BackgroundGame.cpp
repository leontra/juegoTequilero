//
//  BackgroundGame.cpp
//  DemoInduccion
//
//  Created by Max on 5/12/14.
//
//

#include "BackgroundGame.h"
#include <CCGeometry.h>
#define COCOS2D_DEBUG 1
USING_NS_CC;


bool BackgroundGame::init ()
{
    
    
    if( ! LayerColor::initWithColor ( Color4B ( 255,  255,  255,  255 ) ) )
        return false;
    
    
    this -> setColor( Color3B ( 89, 255, 228 ) );

    
    return true;
    
    
} // Bool init