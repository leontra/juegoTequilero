//
//  ResourceLevel.h
//  JuegoTequilero
//
//  Created by Max on 10/17/14.
//
//

#ifndef JuegoTequilero_ResourceLevel_h
#define JuegoTequilero_ResourceLevel_h

#include "cocos2d.h"

struct _ResourceLevel
{
    int iState;
    int index;
    
    std::string name;
    
    cocos2d::Sprite* spriteResource;
    
    void init( )
    {
        iState = 0;
        index = -1;
    }
};

typedef _ResourceLevel ResourceLevel;

#endif
