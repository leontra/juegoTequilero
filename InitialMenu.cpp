//
//  InitialMenu.cpp
//  JuegoTequilero
//
//  Created by Max on 9/27/14.
//
//

#include "InitialMenu.h"

USING_NS_CC;

cocos2d::Scene* InitialMenu::createScene( )
{
    auto scene = cocos2d::Scene::create();
    
    auto layer = InitialMenu::create( );
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool InitialMenu::init( )
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor( Color4B ( 33,  33,  33,  255 ) ) )
        return 0;
    
    _oEffect = new Sounds( );
    
    _bEnterInput = 0;
    
    ////Inicializar los buffers del juego desde un principio, durante el splash
    _oGameBuffering = new GameBuffering( );
    _oGameBuffering->initGameBuffers( );
    
    auto director = Director::getInstance( );
    
    cocos2d::Vec2 origin = director->getVisibleOrigin( );
    
    /*
    cocos2d::Sprite* spriteBackground = Sprite::create ("FondoMenu_00.png");
    spriteBackground->setAnchorPoint ( Point(0, 0));
    addChild (spriteBackground);
    */
    _oAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance( );
    _oAudioEngine->preloadEffect( "BackGround_00.wav" );
    _oAudioEngine->playBackgroundMusic( "BackGround_01.wav", 1 );
    
    this->createTextLabel( );
    this->createStartLabel( );
    this->createStartButton( );
    
    this->schedule( schedule_selector( InitialMenu::update ) );
    
    return 1;
}

void InitialMenu::createTextLabel( )
{
    auto director = Director::getInstance( );
    
    auto text = Label::createWithSystemFont( "Te - Ki - La \n Soñadora Amargura", "Helvetica", 77 );
    text->setAlignment( TextHAlignment::CENTER );
    text->setAnchorPoint( Point( 0, 0 ) );
    text->setColor( Color3B( 255, 87, 107 ) );
    text->setPosition(  ( director->getVisibleSize( ).width / 10 ), ( director->getVisibleSize( ).height / 10 ) * 6 );

    this->addChild( text );
}

void InitialMenu::createStartLabel( )
{
    auto director = Director::getInstance( );
    
    auto text = Label::createWithSystemFont( "Empezar", "Helvetica", 25 );
    text->setAlignment( TextHAlignment::CENTER );
    text->setAnchorPoint( Point( 0.5, 0.5 ) );
    text->setColor( Color3B( 247, 205, 19 ) );
    text->setPosition( director->getVisibleSize( ).width / 2, ( director->getVisibleSize( ).height / 10 ) * 3 );

    this->addChild( text );
    
}

void InitialMenu::createStartButton( )
{
    auto director = Director::getInstance( );
    
    float x = ( director->getVisibleSize( ).width / 2 ) - 40;
    float y = ( director->getVisibleSize( ).height / 12 ) * 2;
    
    _oEnterButton = new Button( );
    
    auto listenerInput = _oEnterButton->setNewInputListener( x,  y, 80, 80, this );
    
    this->inputBegan( listenerInput );
    this->inputMoved( listenerInput );
    this->inputEnded( listenerInput );
    
    _eventDispatcher->addEventListenerWithFixedPriority( listenerInput, 1 );
}

void InitialMenu::inputBegan( cocos2d::EventListenerTouchOneByOne* listenerInput )
{
    listenerInput->onTouchBegan = [&]( cocos2d::Touch* touch, cocos2d::Event* event )
    {
        cocos2d::Point locationInNode = touch->getLocation( );
        
        if (_oEnterButton->getRectButton( ).containsPoint( locationInNode ) )
        {
            _oEffect->GetEffect("pause", ".wav");
            _bEnterInput = 0;
        }
        
        touch->getID( );
        return 1;
        
    }; // onTouchBegan
}

void InitialMenu::inputMoved( cocos2d::EventListenerTouchOneByOne* listenerInput )
{
    listenerInput->onTouchMoved = [&] (cocos2d::Touch* touch,  cocos2d::Event* event)
    {
    };
}

void InitialMenu::inputEnded( cocos2d::EventListenerTouchOneByOne* listenerInput )
{
    listenerInput->onTouchEnded = [&] (cocos2d::Touch* touch,  cocos2d::Event* event)
    {
        cocos2d::Point locationInNode = touch->getLocation( );
        
        if( _oEnterButton->getRectButton( ).containsPoint( locationInNode ) )
        {
            _bEnterInput = 1;
        }
    };
}

void InitialMenu::update (float dt)
{
    if( _bEnterInput )
    {
        _eventDispatcher->removeAllEventListeners( );
        cocos2d::Director::getInstance( )->replaceScene( PlayScene::createScene( ) );
        _bEnterInput = 0;
    }
    
}

InitialMenu::~InitialMenu( )
{
    printf( "\nDestructor Menu" );
    
    delete _oEffect;
    _oAudioEngine->stopBackgroundMusic( );
    this->removeAllChildrenWithCleanup( 1 );
    delete _oEnterButton;
    delete _oGameBuffering;
}

