//
//  inputs.cpp
//  Game Prototype
//
//  Created by Max on 4/14/14.
//
//

#include "Input.h"

#include <CCGeometry.h>

#define COCOS2D_DEBUG 1

USING_NS_CC;



bool Input::bAction = false;

bool Input::bLeft = false;

bool Input::bRight = false;

bool Input::bJump = false;




bool Input::init ()
{
    
    
    if( ! Layer::init() )
        return false;
    
    
    Size visibleSize = Director::getInstance () -> getVisibleSize ();
    //Point origin = Director::getInstance () -> getVisibleOrigin ();
    
    
    //this -> setScale(0.5, 0.5);
    
    this -> setColor ( Color3B( 255, 0, 0 ) );
    
    this -> setOpacity ( 0 );
    
    //auto requiredPortion = CCRectMake(0, 0, 300, 300);
    
    
    
    fDivisionWidth = visibleSize.width / 3;
    
    fDivisionHeight = visibleSize.height / 2;
    
    fWidth = visibleSize.width;
    
    
    
    auto sButtonLeft = Sprite::create ( "button.png" );
    sButtonLeft -> setPosition ( 40, 60 );
    
    auto labelLeft = LabelTTF::create ( "L",  "Helvetica",  20 );
    labelLeft -> setPosition ( 40,  60 );
    labelLeft -> setColor ( Color3B ( 33, 33, 33) );
    
    
    auto sButtonRight = Sprite::create ( "button.png" );
    sButtonRight -> setPosition ( fWidth - 40,  60 );

    auto labelRight = LabelTTF::create ( "R",  "Helvetica",  20 );
    labelRight -> setPosition ( fWidth - 40,  60);
    labelRight -> setColor ( Color3B ( 33, 33, 33) );
    
    this -> addChild ( sButtonLeft );
    this -> addChild ( sButtonRight );
    this -> addChild ( labelLeft );
    this -> addChild ( labelRight );
    
    auto listener1 = EventListenerTouchOneByOne::create ();
    listener1 -> setSwallowTouches( true );
    listener1 -> onTouchBegan = [ & ]( cocos2d::Touch * touch,  cocos2d::Event * event )
    {
        
        
        Point locationInNode = touch -> getLocation ();
        
        
        //Rect rect = Rect(0, 0, visibleSize.width/3 + origin.x, visibleSize.height/2 + origin.y );
        
        
        Rect rectAction = Rect( 0, 0, fWidth, fDivisionHeight );
        Rect rectLeft = Rect( 10, 30, 60, 60 );
        Rect rectRight = Rect( fWidth - 70, 30, 60, 60 );
        Rect rectJump = Rect( 0, fDivisionHeight, fWidth, fDivisionHeight );
    
        
        //rectLeft -> Color4B(33, 33, 33, 33);
        
        
        if ( rectLeft.containsPoint ( locationInNode ) )
            bLeft = true;
        
        else if ( rectRight.containsPoint ( locationInNode ) )
            bRight = true;
        
        else if ( rectJump.containsPoint ( locationInNode ) )
            bJump = true;
        
        if ( rectAction.containsPoint ( locationInNode ) )
            bAction = true;
        
        
        
        
        return true;
        
    }; // onTouchBegan
    
    
    
    listener1 -> onTouchEnded = [ & ]( cocos2d::Touch * touch,  cocos2d::Event * event )
    {
        
        
        if( bLeft )
            bLeft = false;
        
        if( bRight )
            bRight = false;
        
        if( bAction )
            bAction = false;
        
        if( bJump )
            bJump = false;
        
        
    }; //onTouchEnded
    
    
    
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, sButtonLeft);
    
    _eventDispatcher -> addEventListenerWithFixedPriority(listener1, 31);
    
    
    
    return true;
    
    
} // bool init


bool Input::touchLeft( )
{
    
    if( !bLeft )
        return false;
    
    return true;
    
} // bool touchLeft


bool Input::touchRight( )
{
    
    if( !bRight )
        return false;
    
    return true;
    
} // bool touchRight


bool Input::touchAction( )
{
    
    
    
    if( !bAction )
        return false;
    
    
    return true;
    
} // bool touchAction


bool Input::touchJump( )
{
    
    if( !bJump )
        return false;
    
    return true;
    
} // bool touchJump


