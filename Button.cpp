//
//  Button.cpp
//  JuegoTequilero
//
//  Created by Max on 7/23/14.
//
//

#include "Button.h"

USING_NS_CC;

Button::Button ()
{
    
}

Button::~Button ()
{
    
}

cocos2d::EventListenerTouchOneByOne* Button::getNewInputListener ()
{
    auto listenerInput = EventListenerTouchOneByOne::create ();
    
    listenerInput->setSwallowTouches (0);
    
    this->beganTouchForJump (listenerInput);
    
    return listenerInput;
}

void Button::beganTouchForJump (cocos2d::EventListenerTouchOneByOne* listenerInput)
{
    listenerInput->onTouchBegan = [&] (cocos2d::Touch* touch, cocos2d::Event* event)
    {
        cocos2d::Point locationInNode = touch->getLocation ();
        
        touch->getID ();
        /*
        Rect rectJump = Rect (0, fDivisionHeight, fWidth, fDivisionHeight);
        
        if (rectJump.containsPoint (locationInNode))
            _iJumpTouch = locationInNode.y;
        */
        return 1;
        
    }; // onTouchBegan
}