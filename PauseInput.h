//
//  PauseInput.h
//  JuegoTequilero
//
//  Created by Max on 12/18/14.
//
//

#ifndef __JuegoTequilero__PauseInput__
#define __JuegoTequilero__PauseInput__

#include <stdio.h>
#include "cocos2d.h"

class PauseInput
{
public:
    
    PauseInput( );
    ~PauseInput( );
    
    cocos2d::EventListenerTouchOneByOne* InitializePauseInput( cocos2d::Layer* layer, int topScrollHeight, int mainScrollHeight );
    cocos2d::EventListenerTouchOneByOne* getPauseInputListener( );
    
    bool testPauseExit( );
    int testTopScroll( );
    int testMainScroll( );
    
private:
    
    cocos2d::EventListenerTouchOneByOne* getInputListener( );
    
    void beganTouch( cocos2d::EventListenerTouchOneByOne* listenerInput );
    bool initializeBeganTouch( cocos2d::Point& locationInNode, cocos2d::Touch* touch );
    
    void endedTouch( cocos2d::EventListenerTouchOneByOne* listenerInput );
    
    void movedTouch( cocos2d::EventListenerTouchOneByOne* listenerInput );
    void doMovedTouch( cocos2d::Point& locationInNode, cocos2d::Touch* touch );
    
    void testTopScroll( cocos2d::Point& locationInNode );
    void testMainScroll( cocos2d::Point& locationInNode );
    
private:
  
    cocos2d::EventListenerTouchOneByOne* listenerPauseInput;
    
    bool _bExit;
    bool _bTopScroll;
    bool _bMainScroll;
    
    int _iTopScroll;
    int _iDeltaTopScroll;
    
    int _iMainScroll;
    int _iDeltaMainScroll;
    
    int _iTopScrollHeight;
    int _iMainScrollHeight;
    
    int _iWidth;
    int _iHeight;
    
};

#endif /* defined(__JuegoTequilero__PauseInput__) */
