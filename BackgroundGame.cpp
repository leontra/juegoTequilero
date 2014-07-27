//
//  BackgroundGame.cpp
//  JuegoTequilero
//
//  Created by Max on 7/11/14.
//
//

#include "BackgroundGame.h"

#define COCOS2D_DEBUG 1
USING_NS_CC;


bool BackgroundGame::init ()
{
    if( ! LayerColor::initWithColor ( Color4B ( 30,  150,  130,  255 ) ) )
        return false;
    
    cocos2d::Sprite* spriteBackground = Sprite::create ("waterFall1.png");
    
    spriteBackground->setAnchorPoint ( Point(0, 0));
    
    addChild (spriteBackground);
    
    _iBackgroundWidth = spriteBackground->getContentSize().width;
    
    //this -> setColor( Color3B ( 89, 255, 228 ) );
    
    return true;
    
} // Bool init

int BackgroundGame::getBackgroundWidth ()
{
    return _iBackgroundWidth;
}