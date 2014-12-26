//
//  SceneView.cpp
//  JuegoTequilero
//
//  Created by Max on 7/11/14.
//
//

#include "SceneView.h"

#define COCOS2D_DEBUG 1
USING_NS_CC;


Scene * SceneView::createScene( )
{
    auto scene = Scene::create( );
    
    auto layerBackground = BackgroundGame::create ();
    scene -> addChild ( layerBackground,  0 );
    
    //auto layerPlayer = Player::create ();
    //scene -> addChild ( layerPlayer,  2 );
    
    auto layerViewGame = ViewGame::create ();
    scene -> addChild ( layerViewGame,  1 );
    
    auto layerInput = Input::create ();
    scene -> addChild ( layerInput,  3 );
    
    return scene;
    
} // Scene createScene

bool SceneView::init ()
{
    if( ! Layer::init() )
        return false;
    
    
    this -> setColor( Color3B ( 33, 200, 180 ) );
    
    //Size visibleSize = Director::getInstance () -> getVisibleSize ();
    //Point origin = Director::getInstance () -> getVisibleOrigin ();
    
    
    return true;
    
    
} // Bool init

