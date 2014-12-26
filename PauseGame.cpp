//
//  PauseGame.cpp
//  JuegoTequilero
//
//  Created by Max on 7/29/14.
//
//

#include "PauseGame.h"

USING_NS_CC;

PauseGame::PauseGame( ) : _iTopScrollHeight( 0 ),
                                                    _iMainScrollHeight( 0 ),
                                                    _bExit( 0 ),
                                                    _bTopScroll( 0 ),
                                                    _bMainScroll( 0 ),
                                                    _iTopScroll( 0 ),
                                                    _iDeltaTopScroll( 0 ),
                                                    _iMainScroll( 0 ),
                                                    _iDeltaMainScroll( 0 ),
                                                    _iWidth( 0 ),
                                                    _iHeight( 0 )
{ }

PauseGame::~PauseGame( )
{
    //delete _oViewPause;
    delete _oEffect;
    std::cout << "Pause Game Destructor" << std::endl;
}

bool PauseGame::init( )
{
    if ( !LayerColor::initWithColor( Color4B ( 33,  33,  33,  220 ) ) )
        return 0;
    
    _oEffect = new Sounds( );
    _oEffect->GetEffect("pause", ".wav");
    this->createPauseLabel( );
    
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    
    this->createStartButton( );
    
    _oViewPause = ViewPause::create( );
    this->addChild ( _oViewPause,  1 );
    
    return 1;
}

void PauseGame::createPauseLabel( )
{
    auto director = Director::getInstance( );
    
    auto text = Label::createWithSystemFont( "I N V E N T A R I O", "Helvetica", 23 );
    text->setAlignment( TextHAlignment::CENTER );
    text->setAnchorPoint( Point( 0.5, 0.5 ) );
    text->setColor( Color3B( 211, 245, 79 ) );
    text->setPosition( director->getVisibleSize( ).width / 2, ( director->getVisibleSize( ).height / 9 ) * 6 );
    
    this->addChild( text );
}

void PauseGame::createStartButton( )
{
    auto director = Director::getInstance( );
    
    float x = director->getVisibleSize( ).width - 120;
    float y = director->getVisibleSize( ).height - 120;
    
    _oBackButton = new Button( );
    
    _iWidth = this->getContentSize( ).width;
    _iHeight = this->getContentSize( ).height;
    _iTopScrollHeight = 220;
    _iMainScrollHeight = _iHeight - _iTopScrollHeight;
    
    listenerInput = _oBackButton->setNewInputListener( x,  y, 120, 120, this );
    
    beganTouch( listenerInput );
    movedTouch( listenerInput );
    endedTouch( listenerInput );
    
    _eventDispatcher->addEventListenerWithFixedPriority( listenerInput, 1 );
}

void PauseGame::beganTouch( cocos2d::EventListenerTouchOneByOne* listenerInput )
{
    listenerInput->onTouchBegan = [ & ]( cocos2d::Touch* touch, cocos2d::Event* event )
    {
        cocos2d::Point locationInNode = touch->getLocation( );
        
        return initializeBeganTouch( locationInNode, touch );
        
    };
}

bool PauseGame::initializeBeganTouch( cocos2d::Point& locationInNode, cocos2d::Touch* touch )
{
    cocos2d::Rect rectTopScroll = cocos2d::Rect( 0,  _iHeight - _iTopScrollHeight, _iWidth - 130, _iTopScrollHeight );
    cocos2d::Rect rectMainScroll = cocos2d::Rect( 0,  0, _iWidth, _iMainScrollHeight );
    
    if( _oBackButton->getRectButton( ).containsPoint( locationInNode ) )
    {
        _bExit = 1;
        touch->_ID = 1;
        printf( "Exit\n" );
        return 1;
    }
    
    if( rectTopScroll.containsPoint( locationInNode ) )
    {
        _bTopScroll = 1;
        _iTopScroll = locationInNode.x;
        touch->_ID = 2;
        printf( "TopScroll\n" );
        return 1;
    }
    
    if( rectMainScroll.containsPoint( locationInNode ) )
    {
        _bMainScroll = 1;
        _iMainScroll = locationInNode.x;
        touch->_ID = 3;
        printf( "MainScroll\n" );
        return 1;
    }
    
    return 0;
}

void PauseGame::endedTouch( cocos2d::EventListenerTouchOneByOne* listenerInput )
{
    listenerInput->onTouchEnded = [&] (cocos2d::Touch* touch, cocos2d::Event* event)
    {
        cocos2d::Point locationInNode = touch -> getLocation ();
        
        int iTouchID = touch->_ID;
        
        if( iTouchID == 1 )
        {
            if( _oBackButton->getRectButton( ).containsPoint( locationInNode ) )
            {
                this->popPause( );
                return;
            }
            _bExit = 0;
            
        }
        if( iTouchID == 2 )
        {
            _bTopScroll = 0;
            _iTopScroll = 0;
            _iDeltaTopScroll = 0;
        }
        
        if( iTouchID == 3  )
        {
            _bMainScroll = 0;
            _iDeltaMainScroll = 0;
            _iMainScroll = 0;
        }
    };
}

void PauseGame::movedTouch( cocos2d::EventListenerTouchOneByOne* listenerInput )
{
    listenerInput->onTouchMoved = [&] (cocos2d::Touch* touch,  cocos2d::Event* event)
    {
        cocos2d::Point locationInNode = touch -> getLocation ();
        
        this->doMovedTouch (locationInNode, touch);
        
    };
}

void PauseGame::doMovedTouch( cocos2d::Point& locationInNode, cocos2d::Touch* touch )
{
    cocos2d::Rect rectExit = cocos2d::Rect( _iWidth  - 120, _iHeight - 120,  100, 100 );
    
    int iTouchID = touch->_ID;
    
    if( iTouchID == 1 && !rectExit.containsPoint( locationInNode ) )
        _bExit = 0;
    
    if( iTouchID == 2  )
    {
        testTopScroll( locationInNode );
    }
    
    if( iTouchID == 3 )
    {
        testMainScroll( locationInNode );
    }
}

void PauseGame::testTopScroll( cocos2d::Point& locationInNode )
{
    cocos2d::Rect rectTopScroll = cocos2d::Rect( 0,  _iHeight - _iTopScrollHeight, _iWidth - 130, _iTopScrollHeight );
    
    _iDeltaTopScroll = locationInNode.x - _iTopScroll;
    
    _oViewPause->moveTopScroll( _iDeltaTopScroll );
    
    if( !rectTopScroll.containsPoint( locationInNode ) )
    {
        _iTopScroll = 0;
        _bTopScroll = 0;
    }
    else
    {
        _iTopScroll = locationInNode.x;
    }
}

void PauseGame::testMainScroll( cocos2d::Point& locationInNode )
{
    cocos2d::Rect rectMainScroll = cocos2d::Rect( 0,  0, _iWidth, _iMainScrollHeight );
    
    _iDeltaMainScroll = locationInNode.x - _iMainScroll;
    
    _oViewPause->moveMainScroll( _iDeltaMainScroll );
    
    if( !rectMainScroll.containsPoint( locationInNode ) )
    {
        _iMainScroll = 0;
        _bMainScroll = 0;
    }
    else
    {
        _iMainScroll = locationInNode.x;
    }
}

void PauseGame::cleanUp( ){ }

void PauseGame::popPause( )
{
    _oEffect->GetEffect("pause", ".wav");
    auto director = Director::getInstance( );
    //printf( "PopPause\n" );
    _oViewPause->clean( );
    director->getRunningScene( )->removeChild( this );
    _eventDispatcher->removeEventListener( listenerInput );
    Director::getInstance( )->resume( );
}
