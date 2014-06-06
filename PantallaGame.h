//
//  PantallaGame.h
//  Game Prototype
//
//  Created by Max on 4/14/14.
//
//


#ifndef __gameTest00__pantallaPrueba__
#define __gameTest00__pantallaPrueba__

#include <iostream>

#include "cocos2d.h"

class Game  :  public cocos2d::LayerColor
{
    
    
private:
    
    
    
public:
    
    static cocos2d::Scene * createScene ();
    
    virtual bool init ();
    
    CREATE_FUNC( Game );
    
    
};

#endif /* defined(__gameTest00__pantallaPrueba__) */
