//
//  InitialMenu.h
//  JuegoTequilero
//
//  Created by Max on 9/27/14.
//
//

#ifndef __JuegoTequilero__InitialMenu__
#define __JuegoTequilero__InitialMenu__

#include <iostream>
#include "cocos2d.h"
#include "Button.h"
#include "PlayScene.h"

class InitialMenu : public cocos2d::LayerColor
{
private:
    Button* _oEnterButton;
    
    bool _bEnterInput;
    
    void createStartButton( );
    void createStartLabel( );
    void createTextLabel( );
    
    void inputBegan( cocos2d::EventListenerTouchOneByOne* listenerInput );
    void inputMoved( cocos2d::EventListenerTouchOneByOne* listenerInput );
    void inputEnded( cocos2d::EventListenerTouchOneByOne* listenerInput );
    
    void update (float dt);
    
public:

    static cocos2d::Scene* createScene( );
    
    virtual bool init( );
    
    ~InitialMenu( );
    
    void menuCloseCallback( cocos2d::Ref* pSender );
    
    CREATE_FUNC( InitialMenu );
};


#endif /* defined(__JuegoTequilero__InitialMenu__) */
