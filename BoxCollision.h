//
//  BoxCollision.h
//  gameTest00
//
//  Created by Max on 4/16/14.
//
//

#ifndef __gameTest00__BoxCollision__
#define __gameTest00__BoxCollision__

#include <iostream>

#include "cocos2d.h"



class BoxCollision
{
    
    
private:
    
    
    
public:
    
    static void checkCollision ( cocos2d::Sprite * platform, int &x, int &y, int &sumX, int &sumY, int &_pWidth, int &_pHeight, int &g, bool &horizontalLeft, bool &horizontalRight, bool &verticalPlus, bool &verticalMinus );
    
    
    BoxCollision()
    {
        
        
    }
    
    
    ~BoxCollision()
    {
        
        
        
    }
    
    
};



#endif /* defined(__gameTest00__BoxCollision__) */
