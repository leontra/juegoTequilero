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
    cocos2d::Rect _rectButton;
    
public:
    Button( );
    
    ~Button( );
    
    cocos2d::EventListenerTouchOneByOne* setNewInputListener( const float& x, const float& y, const float& width, const float& height, cocos2d::LayerColor* layer );
    
    cocos2d::Rect& getRectButton( );
    
};

#endif /* defined(__JuegoTequilero__Button__) */
