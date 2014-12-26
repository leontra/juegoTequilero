//
//  PauseGame.h
//  JuegoTequilero
//
//  Created by Max on 7/29/14.
//
//

#ifndef __JuegoTequilero__PauseGame__
#define __JuegoTequilero__PauseGame__

#include <iostream>

#include "cocos2d.h"
#include "Button.h"
#include "ViewPause.h"
#include "PauseInput.h"
#include "Sounds.h"




class PauseGame : public cocos2d::LayerColor
{
private:
    
    void createStartButton( );
    
    void createPauseLabel( );
    void cleanUp( );
    void popPause( );
    
    void beganTouch( cocos2d::EventListenerTouchOneByOne* listenerInput );
    bool initializeBeganTouch( cocos2d::Point& locationInNode, cocos2d::Touch* touch );
    
    void endedTouch( cocos2d::EventListenerTouchOneByOne* listenerInput );
    
    void movedTouch( cocos2d::EventListenerTouchOneByOne* listenerInput );
    void doMovedTouch( cocos2d::Point& locationInNode, cocos2d::Touch* touch );
    
    void testTopScroll( cocos2d::Point& locationInNode );
    void testMainScroll( cocos2d::Point& locationInNode );
    
public:
    
    virtual bool init( );
    
    PauseGame( );
    virtual ~PauseGame( );
    
    CREATE_FUNC( PauseGame );
    
private:
    
    Button* _oBackButton;
    cocos2d::EventListenerTouchOneByOne* listenerInput;
    
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
    
    ViewPause* _oViewPause;
    Sounds* _oEffect;
};

#endif /* defined(__JuegoTequilero__PauseGame__) */
