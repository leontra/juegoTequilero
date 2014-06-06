//
//  Platform.h
//  Game Prototype
//
//  Created by Max on 4/14/14.
//
//

#ifndef __gameTest00__Plataforma__
#define __gameTest00__Plataforma__

#include <iostream>

#include "cocos2d.h"


class Platform
{
    
private:
    
    
public:
    
    void addPlatform( cocos2d::Layer * layer,  int zIndex, int posX, int posY, int _width, int _height );
    
    cocos2d::Sprite * platform;
    
    Platform ()
    {
        
        platform = NULL;
        
    }
    
    ~Platform ()
    {
        
    }
    
};

#endif /* defined(__gameTest00__Plataforma__) */
