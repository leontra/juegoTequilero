//
//  PantallaGame.cpp
//  GamePrototype
//
//  Created by Max on 4/14/14.
//


#include "PantallaGame.h"

#include "Player.h"

#include "Input.h"

#include <CCGeometry.h>


#define COCOS2D_DEBUG 1


USING_NS_CC;




Scene * Game::createScene ()
{
    
    
    auto scene = Scene::create ();
    
    auto layerGame = Game::create ();
    
    auto layerPlayer = Player::create ();
    
    auto layerInputs = Input::create ();
    
    scene -> addChild ( layerGame, -2 );
    
    scene -> addChild ( layerPlayer,  1 );
    
    scene -> addChild ( layerInputs,  2 );
    
    
    return scene;
    
    
} // Scene createScene

bool Game::init ()
{
    
    
    if( ! LayerColor::initWithColor ( Color4B ( 255,  255,  255,  255 ) ) )
        return false;
    
    
    this -> setColor( Color3B ( 33, 200, 180 ) );
    
    //Size visibleSize = Director::getInstance () -> getVisibleSize ();
    //Point origin = Director::getInstance () -> getVisibleOrigin ();
    
    
    return true;
    
    
} // Bool init



