//
//  Milliseconds.h
//  JuegoTequilero
//
//  Created by Max on 7/11/14.
//
//

#ifndef __JuegoTequilero__Milliseconds__
#define __JuegoTequilero__Milliseconds__

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


#endif /* defined(__JuegoTequilero__Milliseconds__) */
