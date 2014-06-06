//
//  Milliseconds.h
//  gameTest00
//
//  Created by Max on 4/20/14.
//
//

#ifndef __gameTest00__Milliseconds__
#define __gameTest00__Milliseconds__

#include <iostream>

#include "cocos2d.h"

class Milliseconds
{
    
    
private:
    
    float fMillisStart;
    
    float fMillisCount;
    
    
    bool bSeconds;
    
    
public:
    
    static float fGetMilliCount();
    
    bool getSecCount();
    
    float getCount();
    
    Milliseconds()
    {
        
        fMillisStart = 0;
        
        fMillisCount = 0;
        
        bSeconds = false;
        
    }
    
    ~ Milliseconds()
    {
        
        
        
    }
    
    
    
    
};





#endif /* defined(__gameTest00__Milliseconds__) */
