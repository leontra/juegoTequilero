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
    
    float _fMillisStart;
    
    int _fMillisCount;
    
    float _iMillisCount;
    
    bool _bSeconds;
    
    float fGetMilliCount();
    
    int iGetMilliCount ();
    
public:
    
    bool getSecCount ();
    
    float getCount ();
    
    void startCounter ();
    
    float& getSecsCounter ();
    
    int getMillisInterval (int iTimeInterval);
    
    int getEveryMillis ();
    
    Milliseconds ();
    
    ~ Milliseconds();
    
};


#endif /* defined(__JuegoTequilero__Milliseconds__) */
