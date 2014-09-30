//
//  ResourceObject.h
//  JuegoTequilero
//
//  Created by Max on 7/13/14.
//
//

#ifndef JuegoTequilero_ResourceObject_h
#define JuegoTequilero_ResourceObject_h

#include "cocos2d.h"

struct _ObjectResource
{
    int x;
    int y;
    int iActivo;
    int width;
    int height;
    int iType;
    
    std::string name;
    
    cocos2d::Sprite* spriteResource;
};

typedef _ObjectResource objectResource;

#endif
