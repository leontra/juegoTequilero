//
//  PauseGame.cpp
//  JuegoTequilero
//
//  Created by Max on 7/29/14.
//
//

#include "PauseGame.h"

USING_NS_CC;

PauseGame::PauseGame( )
{
    std::cout << "Pause Game Constructor" << std::endl;
}

PauseGame::~PauseGame( )
{
    std::cout << "Pause Game Destructor" << std::endl;
}

/*
cocos2d::Scene* PauseGame::createScene( )
{
    // 'scene' is an autorelease object
    auto scene = cocos2d::Scene::create( );
    
    // 'layer' is an autorelease object
    auto layer = PauseGame::create( );
    
    // add layer as a child to scene
    //scene->addChild(layer);
    
    scene->setOpacity( 255 );
    scene->setColor( Color3B( 255, 100, 100 ) );
    
    // return the scene
    return scene;
}
*/

// on "init" you need to initialize your instance
bool PauseGame::init( )
{
    if ( !LayerColor::initWithColor( Color4B ( 8,  33,  38,  200 ) ) )
    {
        return 0;
    }
    
    this->createPauseLabel( );
    
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    
    this->createStartButton( );
    
    return 1;
}

void PauseGame::createPauseLabel( )
{
    auto director = Director::getInstance( );
    
    auto text = Label::createWithSystemFont( "P A U S A", "Helvetica", 21 );
    text->setAlignment( TextHAlignment::CENTER );
    text->setAnchorPoint( Point( 0.5, 0.5 ) );
    text->setColor( Color3B( 111, 255, 255 ) );
    text->setPosition( director->getVisibleSize( ).width / 2, ( director->getVisibleSize( ).height / 9 ) * 8 );
    
    this->addChild( text );
}

void PauseGame::createStartButton( )
{
    auto director = Director::getInstance( );
    
    float x = director->getVisibleSize( ).width - 120;
    float y = director->getVisibleSize( ).height - 120;
    
    _oBackButton = new Button( );
    
    listenerInput = _oBackButton->setNewInputListener( x,  y, 80, 80, this );
    
    this->inputBegan( listenerInput );
    this->inputMoved( listenerInput );
    this->inputEnded( listenerInput );
    
    
    _eventDispatcher->addEventListenerWithFixedPriority( listenerInput, 7 );
}

void PauseGame::inputBegan( cocos2d::EventListenerTouchOneByOne* listenerInput )
{
    listenerInput->onTouchBegan = [&]( cocos2d::Touch* touch, cocos2d::Event* event )
    {
        cocos2d::Point locationInNode = touch->getLocation( );
        
        if( _oBackButton->getRectButton( ).containsPoint( locationInNode ) )
        {
           
        }
        
        touch->getID( );
        return 1;
        
    }; // onTouchBegan
}

void PauseGame::inputMoved( cocos2d::EventListenerTouchOneByOne* listenerInput )
{
    listenerInput->onTouchMoved = [&] (cocos2d::Touch* touch,  cocos2d::Event* event)
    {
        
    };
}

void PauseGame::inputEnded( cocos2d::EventListenerTouchOneByOne* listenerInput )
{
    listenerInput->onTouchEnded = [&] (cocos2d::Touch* touch,  cocos2d::Event* event)
    {
        cocos2d::Point locationInNode = touch->getLocation( );
        
        if( _oBackButton->getRectButton( ).containsPoint( locationInNode ) )
        {
            this->popPause( );
        }
    };
}

void PauseGame::cleanUp( )
{
    
}

void PauseGame::popPause( )
{
    auto director = Director::getInstance( );
    director->getRunningScene( )->removeChild( this );
    _eventDispatcher->removeEventListener( listenerInput );
    director->resume( );
}
