//
//  Input.cpp
//  JuegoTequilero
//
//  Created by Max on 7/11/14.
//
//

#include "Input.h"

#define COCOS2D_DEBUG 1

USING_NS_CC;

static bool _bLeft = 0;

static bool _bRight = 0;

static bool _bAction = 0;

static bool _bJump = 0;



Input::Input( ): fDivisionHeight (0),
                  fDivisionWidth (0),
                  fWidth (0),
                  _iButtonHeight (0),
                  _iButtonWidth (0),
                  _bLastAction (0),
                  _bLastJump (0),
                  _bLastLeft (0),
                  _bLastRight (0),
                  _iJumpTouch (0)
{
}

Input::~Input ()
{
}

bool Input::init ()
{
    if (!Layer::init())
        return 0;
    
    Size visibleSize = Director::getInstance ()->getVisibleSize ();
    
    //Hacer translucido el fondo del layer del input
    this->setOpacity (0);
    
    this->initInput (visibleSize);
    
    return 1;
} // bool init

void Input::initInput( cocos2d::Size visibleSize )
{
    //Inicializar las variables de la clase
    this->initVariables (visibleSize);
    
    //Inicializar las variables para crear los botones de movimiento
    int iButtonWidthPadding = 30;
    int iButtonHeightPadding = 30;
    
    //Inicializar los sprites del input de movimiento
    this->initButtonsSprites( iButtonWidthPadding, iButtonHeightPadding);
    
    //Inicializar el input del player
    auto listenerInputPlayer = this->getInputListener( );
    
    //Inicializar los diferentes tipos de eventos del input
    this->beganTouch( listenerInputPlayer );
    this->movedTouch( listenerInputPlayer );
    this->endedTouch( listenerInputPlayer );
    this->cancelledTouch( listenerInputPlayer );
    
    //Agregar el input a los eventos del juego
    _eventDispatcher->addEventListenerWithFixedPriority( listenerInputPlayer, 5 );
}

void Input::initVariables (Size visibleSize)
{
    fDivisionWidth = visibleSize.width / 3;
    fDivisionHeight = visibleSize.height / 2;
    fWidth = visibleSize.width;
    _iButtonWidth = 130;
    _iButtonHeight = 120;
}

void Input::initButtonsSprites (int& iButtonWidthPadding, int& iButtonHeightPadding)
{
    this->addChild (this->getLeftButton (iButtonWidthPadding, iButtonHeightPadding));
    this->addChild (this->getRightButton (iButtonWidthPadding, iButtonHeightPadding));
}

Sprite* Input::getLeftButton (int& iButtonWidthPadding, int& iButtonHeightPadding)
{
    auto sButtonLeft = Sprite::create ("Button_00.png");
    sButtonLeft->setOpacity (150);
    sButtonLeft->setAnchorPoint (Point (0, 0));
    sButtonLeft->setContentSize (Size (200, 200));
    sButtonLeft->setPosition (iButtonWidthPadding, iButtonHeightPadding);
    
    return sButtonLeft;
}

Sprite* Input::getRightButton (int& iButtonWidthPadding, int& iButtonHeightPadding)
{
    auto sButtonRight = Sprite::create ("Button_00.png");
    sButtonRight->setOpacity (150);
    sButtonRight->setAnchorPoint (Point (0, 0));
    sButtonRight->setPosition (fWidth - sButtonRight->getContentSize().width - iButtonWidthPadding,  iButtonHeightPadding);
    
    return sButtonRight;
}

EventListenerTouchOneByOne* Input::getInputListener( )
{
    auto listenerInputPlayer = EventListenerTouchOneByOne::create( );
    
    listenerInputPlayer->setSwallowTouches( 0 );
    
    return listenerInputPlayer;
}

void Input::beganTouch( cocos2d::EventListenerTouchOneByOne* listenerInput )
{
    listenerInput->onTouchBegan = [ & ]( cocos2d::Touch* touch, cocos2d::Event* event )
    {
        Point locationInNode = touch->getLocation( );
        
        return initilizeBeganTouch( locationInNode, touch );
        
    }; // onTouchBegan
}

bool Input::initilizeBeganTouch (cocos2d::Point& locationInNode, cocos2d::Touch* touch)
{
    // Rect rectAction = Rect ( 0, 0, fWidth, fDivisionHeight);
    Rect rectLeft = Rect ( 0, 0, _iButtonWidth, _iButtonHeight);
    Rect rectRight = Rect (fWidth - _iButtonWidth, 0, _iButtonWidth, _iButtonHeight);
    Rect rectJump = Rect( 0, 0, fWidth, fDivisionHeight * 2);
    //Rect rectAction = Rect( 0, 0, fWidth, fDivisionHeight * 2);
    
    //std::cout << "Input Touch Began" << std::endl;
    
    if (rectLeft.containsPoint (locationInNode))
    {
        _bLeft = 1;
        touch->_ID = 1;
        return 1;
    }
    else
    if (rectRight.containsPoint (locationInNode))
    {
        _bRight = 1;
        touch->_ID = 2;
        return 1;
    }
    else
    if (rectJump.containsPoint (locationInNode))
    {
        _iJumpTouch = locationInNode.y;
        touch->_ID = touch->_ID;
        return 1;
    }
    
    return 0;
}

void Input::endedTouch (cocos2d::EventListenerTouchOneByOne* listenerInput)
{
    listenerInput->onTouchEnded = [&] (cocos2d::Touch* touch, cocos2d::Event* event)
    {
        Point locationInNode = touch -> getLocation ();
        
        int iTouchID = touch->_ID;
        
        if( iTouchID == 1 )
            _bLeft = 0;
        
        if( iTouchID == 2 )
            _bRight = 0;
        
        if( ( iTouchID == 12 || iTouchID == 11 || iTouchID == 14 ) )
        {
            _bLastAction = 0;
            _bJump = 0;
            _bAction = 0;
        }
    }; //onTouchEnded
}

void Input::movedTouch (cocos2d::EventListenerTouchOneByOne* listenerInput)
{
    //Revisar si movio el dedo sin despegarlo de la pantalla
    listenerInput->onTouchMoved = [&] (cocos2d::Touch* touch,  cocos2d::Event* event)
    {
        Point locationInNode = touch -> getLocation ();
        
        this->doMovedTouch (locationInNode, touch);
        
    }; //Touch Moved
}

void Input::doMovedTouch (cocos2d::Point& locationInNode, cocos2d::Touch* touch)
{
    Rect rectLeft = Rect (0, 0, _iButtonWidth, _iButtonHeight);
    Rect rectRight = Rect (fWidth - _iButtonWidth, 0, _iButtonWidth, _iButtonHeight);
    
    int iTouchID = touch->_ID;
    
    if( iTouchID == 1 && !rectLeft.containsPoint( locationInNode ) )
        _bLeft = 0;
    
    if( iTouchID == 2 && !rectRight.containsPoint( locationInNode ) )
        _bRight = 0;
    
    if( ( iTouchID == 12 || iTouchID == 11 ) && !_bLastAction )
        this->testJump( locationInNode );
}

void Input::cancelledTouch( cocos2d::EventListenerTouchOneByOne* listenerInput )
{
    listenerInput->onTouchCancelled = [&] (cocos2d::Touch* touch,  cocos2d::Event* event)
    {
        Point locationInNode = touch->getLocation( );
        
        this->doCancelledTouch( locationInNode, touch );
        
    };
}

void Input::doCancelledTouch( cocos2d::Point& locationInNode, cocos2d::Touch* touch )
{
    Rect rectLeft = Rect (0, 0, _iButtonWidth, _iButtonHeight);
    Rect rectRight = Rect (fWidth - _iButtonWidth, 0, _iButtonWidth, _iButtonHeight);
    
    int iTouchID = touch->_ID;
    
    if (iTouchID == 1 && !rectLeft.containsPoint (locationInNode))
        _bLeft = 0;
    
    if (iTouchID == 2 && !rectRight.containsPoint (locationInNode))
        _bRight = 0;
    
    if ( ( iTouchID == 12 || iTouchID == 11 ) && !_bLastAction)
        this->testJump (locationInNode);
}

void Input::testJump (cocos2d::Point& locationInNode)
{
    Rect rectJump = Rect (0, fDivisionHeight, fWidth, fDivisionHeight);
    
    if (locationInNode.y > _iJumpTouch + 30)
    {
        _bLastAction = 1;
        _bJump = 1;
    }
    if (locationInNode.y < _iJumpTouch - 40)
    {
        _bLastAction = 1;
        _bAction = 1;
    }
}

void Input::checkForTouchMoved (bool& bTouch, bool& bLastTouch)
{
    if (bLastTouch && bTouch)
    {
        bLastTouch = 0;
        bTouch = 0;
    }
}

bool Input::touchLeft( )
{
    return _bLeft;
} // bool touchLeft


bool Input::touchRight( )
{
    return _bRight;
    
} // bool touchRight


bool Input::touchAction( )
{
    if( _bAction )
    {
        _bAction = 0;
        return 1;
    }
    return _bAction;
} // bool touchAction


bool Input::touchJump( )
{
    if( _bJump )
    {
        _bJump = 0;
        return 1;
    }
    return 0;
} // bool touchJump