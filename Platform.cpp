//
//  Platform.cpp
//  Game Prototype
//
//  Created by Max on 4/14/14.
//
//

#include "Platform.h"

#include <CCGeometry.h>

#define COCOS2D_DEBUG 1

USING_NS_CC;


void Platform::addPlatform ( cocos2d::Layer * layer, int zIndex, int posX, int posY, int _width, int _height )
{
    
    Rect requiredPortion = Rect( 0, 0, _width, _height );
    
    Rect drawArea = Rect( posX, posY, _width, 50 );
    
    
    Image *image = new Image ();
    
    image -> initWithImageFile ( "texture.png" );
    
    
    Texture2D *texture = new Texture2D ();
    
    texture -> initWithImage ( image );
    
    
    platform = Sprite::createWithTexture( texture, requiredPortion );
    
    
    platform -> setAnchorPoint( Point ( 0,  0 ) );
    
    platform -> setScale ( drawArea.size.width / requiredPortion.size.width );
    
    platform -> setPosition ( drawArea.origin );
    
    
    layer -> addChild ( platform , zIndex);
    
    
    
}

