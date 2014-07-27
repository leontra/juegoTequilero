//
//  Button.h
//  JuegoTequilero
//
//  Created by Max on 7/23/14.
//
//

#ifndef __JuegoTequilero__Button__
#define __JuegoTequilero__Button__

#include <iostream>

#include "cocos2d.h"

class Button
{
    
private:
    
    
public:
    Button ();
    
    ~Button ();
    
    cocos2d::EventListenerTouchOneByOne* getNewInputListener ();
    
    void beganTouchForJump (cocos2d::EventListenerTouchOneByOne* listenerInput);
    
};

#endif /* defined(__JuegoTequilero__Button__) */
