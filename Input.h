//
//  Input.h
//  JuegoTequilero
//
//  Created by Max on 7/11/14.
//
//

#ifndef __JuegoTequilero__Input__
#define __JuegoTequilero__Input__

#include <iostream>

#include "cocos2d.h"


class Input : public cocos2d::Layer
{
    
    
private:
    
    int _iButtonWidth;
    
    int _iButtonHeight;
    
    bool _bLastJump;
    
    bool _bLastAction;
    
    bool _bLastLeft;
    
    bool _bLastRight;
    
    int _iJumpTouch;
    
    void initInput (cocos2d::Size visibleSize);
    
    void initVariables (cocos2d::Size visibleSize);
    
    cocos2d::EventListenerTouchOneByOne* getInputListener ();
    
    cocos2d::Sprite* getLeftButton (int& iButtonWidthPadding, int& iButtonHeightPadding);
    
    cocos2d::Sprite* getRightButton (int& iButtonWidthPadding, int& iButtonHeightPadding);
    
    void touchForJump (cocos2d::EventListenerTouchOneByOne* listenerInput);
    
    void initButtonsSprites (int& iButtonWidthPadding, int& iButtonHeightPadding);
    
    void beganTouch (cocos2d::EventListenerTouchOneByOne* listenerInput);
    
    void beganTouchForJump (cocos2d::EventListenerTouchOneByOne* listenerInput);
    
    void endedTouch (cocos2d::EventListenerTouchOneByOne* listenerInput);
    
    void endedTouchForJump (cocos2d::EventListenerTouchOneByOne* listenerInput);
    
    void movedTouch (cocos2d::EventListenerTouchOneByOne* listenerInput);
    
    void movedTouchForJump (cocos2d::EventListenerTouchOneByOne* listenerInput);
    
    void checkForTouchMoved (bool& bTouch, bool& bLastTouch);
    
    void initilizeBeganTouch (cocos2d::Point& point, cocos2d::Touch* touch);
    
    void doMovedTouch (cocos2d::Point& locationInNode, cocos2d::Touch* touch);
    
    void testJump (cocos2d::Point& locationInNode);
    
public:
    
    float fDivisionWidth;
    
    float fDivisionHeight;
    
    float fWidth;
    
    virtual bool init();
    
    CREATE_FUNC(Input);
    
    bool touchLeft ();
    
    bool touchRight ();
    
    bool touchAction ();
    
    bool touchJump ();
    
    Input ();
    
    ~Input ();
    
};

#endif /* defined(__JuegoTequilero__Input__) */
