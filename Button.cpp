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

cocos2d::EventListenerTouchOneByOne* Button::setNewInputListener( const float& x, const float& y, const float& width, const float& height, cocos2d::LayerColor* layer )
{
    auto listenerInput = EventListenerTouchOneByOne::create( );
    
    _rectButton = Rect( x, y, width, height);
    
    auto spriteButton = Sprite::create( "Button_00.png" );
    spriteButton->setOpacity( 90 );
    spriteButton->setAnchorPoint( Point( 0.0, 0.0 ) );
    spriteButton->setPosition( x, y );
    
    layer->addChild( spriteButton );
    
    listenerInput->setSwallowTouches( 0 );
    
    return listenerInput;
}

cocos2d::Rect& Button::getRectButton( )
{
    return _rectButton;
}



