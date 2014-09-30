#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene( )
{
    // 'scene' is an autorelease object
    auto scene = Scene::create( );
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create( );
    
    // add layer as a child to scene
    scene->addChild( layer );
    
    auto layerBackground = BackgroundGame::create( );
    scene -> addChild ( layerBackground,  0 );
    
    auto layerPlayer = Player::create ();
    scene -> addChild ( layerPlayer,  2 );
    
    auto layerViewGame = ViewGame::create ();
    scene -> addChild ( layerViewGame,  1 );
    
    auto layerInput = Input::create ();
    scene -> addChild ( layerInput,  3 );

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    return true;
}


