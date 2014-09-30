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

class PauseGame : public cocos2d::LayerColor
{
private:
    
    Button* _oBackButton;
    
    cocos2d::EventListenerTouchOneByOne* listenerInput;
    
    void createStartButton( );
    void inputBegan( cocos2d::EventListenerTouchOneByOne* listenerInput );
    void inputMoved( cocos2d::EventListenerTouchOneByOne* listenerInput );
    void inputEnded( cocos2d::EventListenerTouchOneByOne* listenerInput );
    
    void createPauseLabel( );
    void cleanUp( );
    void popPause( );
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    //static cocos2d::Scene* createScene( );
    
    virtual bool init();
    
    PauseGame( );
    virtual ~PauseGame( );
    
    CREATE_FUNC( PauseGame );
};

#endif /* defined(__JuegoTequilero__PauseGame__) */
