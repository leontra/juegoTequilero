//
//  PlayScene.h
//  JuegoTequilero
//
//  Created by Max on 9/27/14.
//
//

#ifndef __JuegoTequilero__PlayScene__
#define __JuegoTequilero__PlayScene__

#include "cocos2d.h"

#include "ViewGame.h"
#include "Input.h"
#include "BackgroundGame.h"
#include "PauseGame.h"

class PlayScene : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene( );
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init( );
    
    void pushPauseLayer( );
    void popPauseLayer( );
    
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC( PlayScene );
};

#endif /* defined(__JuegoTequilero__PlayScene__) */
