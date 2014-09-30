//
//  PlayScene.cpp
//  JuegoTequilero
//
//  Created by Max on 9/27/14.
//
//

#include "PlayScene.h"

USING_NS_CC;

Scene* PlayScene::createScene( )
{
    // 'scene' is an autorelease object
    auto scene = Scene::create( );
    
    //scene->setColor( Color3B( 244, 22, 2 ) );
    
    // 'layer' is an autorelease object
    auto layer = PlayScene::create( );
    
    // add layer as a child to scene
    scene->addChild( layer );
    
    auto layerBackground = BackgroundGame::create( );
    scene -> addChild ( layerBackground,  0 );
    
    auto layerPlayer = Player::create( );
    scene -> addChild ( layerPlayer,  2 );
    
    auto layerViewGame = ViewGame::create( );
    scene -> addChild ( layerViewGame,  1 );
    
    auto layerInput = Input::create( );
    scene -> addChild ( layerInput,  3 );
    
    // return the scene
    return scene;
}

bool PlayScene::init( )
{
    if( !LayerColor::initWithColor( Color4B( 10, 200, 190, 255 ) ) )
    {
        return 0;
    }
    
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    return 1;
}

void PlayScene::pushPauseLayer( )
{
    auto layerPause = PauseGame::create( );
    layerPause->setTag( 99 );
    this->addChild( layerPause );
}

void PlayScene::popPauseLayer( )
{
    this->removeChildByTag( 99 );
}