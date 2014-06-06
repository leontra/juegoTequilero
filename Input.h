//
//
//  Input.h
//  Game Prototype
//
//  Created by Max on 4/14/14.
//
//

#ifndef __gameTest00__inputs__
#define __gameTest00__inputs__

#include <iostream>

#include "cocos2d.h"



class Input : public cocos2d::Layer
{
    
    
private:
    
    static bool bLeft;
    
    static bool bRight;
    
    static bool bAction;
    
    static bool bJump;
    
    
    
public:
    
    float fDivisionWidth;
    
    float fDivisionHeight;
    
    float fWidth;
    
    virtual bool init();
    
    CREATE_FUNC(Input);
    
    static bool touchLeft( );
    
    static bool touchRight( );
    
    static bool touchAction( );
    
    static bool touchJump( );
    
    Input ()
    {
        
        fDivisionWidth = 0;
        
        fDivisionHeight = 0;
        
        fWidth = 0;
        
    }
    
    ~Input ()
    {
        
        
    }
    
};

#endif /* defined(__gameTest00__inputs__) */
