//
//  PauseInput.cpp
//  JuegoTequilero
//
//  Created by Max on 12/18/14.
//
//

#include "PauseInput.h"

PauseInput::PauseInput( ) :
                                                _iTopScrollHeight( 0 ),
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


cocos2d::EventListenerTouchOneByOne* PauseInput::InitializePauseInput( cocos2d::Layer* layer, int topScrollHeight, int mainScrollHeight )
{
    _iTopScrollHeight = topScrollHeight;
    _iMainScrollHeight = mainScrollHeight;
    _iWidth = layer->getContentSize( ).width;
    _iHeight = layer->getContentSize( ).height;
    
    listenerPauseInput = this->getInputListener( );
    
    beganTouch( listenerPauseInput );
    movedTouch( listenerPauseInput );
    endedTouch( listenerPauseInput );

    return listenerPauseInput;
}

cocos2d::EventListenerTouchOneByOne* PauseInput::getInputListener( )
{
    auto listenerInputPlayer = cocos2d::EventListenerTouchOneByOne::create( );
    
    listenerInputPlayer->setSwallowTouches( 0 );
    
    return listenerInputPlayer;
}

void PauseInput::beganTouch( cocos2d::EventListenerTouchOneByOne* listenerInput )
{
    listenerInput->onTouchBegan = [ & ]( cocos2d::Touch* touch, cocos2d::Event* event )
    {
        cocos2d::Point locationInNode = touch->getLocation( );
        
        return initializeBeganTouch( locationInNode, touch );
        
    };
}

bool PauseInput::initializeBeganTouch( cocos2d::Point& locationInNode, cocos2d::Touch* touch )
{
    cocos2d::Rect rectExit = cocos2d::Rect( _iWidth  - 120, _iHeight - 120,  120, 120 );
    cocos2d::Rect rectTopScroll = cocos2d::Rect( 0,  _iHeight - _iTopScrollHeight, _iWidth - 130, _iTopScrollHeight );
    cocos2d::Rect rectMainScroll = cocos2d::Rect( 0,  0, _iWidth, _iMainScrollHeight );
    
    if( rectExit.containsPoint( locationInNode ) )
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

void PauseInput::endedTouch( cocos2d::EventListenerTouchOneByOne* listenerInput )
{
    listenerInput->onTouchEnded = [&] (cocos2d::Touch* touch, cocos2d::Event* event)
    {
        cocos2d::Point locationInNode = touch -> getLocation ();
        
        int iTouchID = touch->_ID;
        
        if( iTouchID == 1 )
            _bExit = 0;
        
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

void PauseInput::movedTouch( cocos2d::EventListenerTouchOneByOne* listenerInput )
{
    listenerInput->onTouchMoved = [&] (cocos2d::Touch* touch,  cocos2d::Event* event)
    {
        cocos2d::Point locationInNode = touch -> getLocation ();
        
        this->doMovedTouch (locationInNode, touch);
        
    };
}

void PauseInput::doMovedTouch( cocos2d::Point& locationInNode, cocos2d::Touch* touch )
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
        
        //this->testJump( locationInNode );
    }
}

void PauseInput::testTopScroll( cocos2d::Point& locationInNode )
{
    cocos2d::Rect rectTopScroll = cocos2d::Rect( 0,  _iHeight - _iTopScrollHeight, _iWidth - 130, _iTopScrollHeight );
    
    _iDeltaTopScroll = locationInNode.x - _iTopScroll;
    
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

void PauseInput::testMainScroll( cocos2d::Point& locationInNode )
{
    cocos2d::Rect rectMainScroll = cocos2d::Rect( 0,  0, _iWidth, _iMainScrollHeight );
    
    _iDeltaMainScroll = locationInNode.x - _iMainScroll;
    
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

bool PauseInput::testPauseExit( )
{
    if( _bExit )
    {
        _bExit = 0;
        return 1;
    }
    
    return 0;
}

int PauseInput::testTopScroll( )
{
    if( _iDeltaTopScroll )
    {
        int iReturn = _iDeltaTopScroll;
        _iDeltaTopScroll = 0;
        return iReturn;
    }
    
    return 0;
}

int PauseInput::testMainScroll( )
{
    if( _iDeltaMainScroll )
    {
        int iReturn = _iDeltaMainScroll;
        _iDeltaMainScroll = 0;
        return iReturn;
    }
    
    return 0;
}

cocos2d::EventListenerTouchOneByOne* PauseInput::getPauseInputListener( )
{
    return listenerPauseInput;
}

PauseInput::~PauseInput( )
{
}

