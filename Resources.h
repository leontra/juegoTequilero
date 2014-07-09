//
//  Resources.h
//  DemoInduccion
//
//  Created by Administrador on 7/6/14.
//
//

#ifndef __DemoInduccion__Resources__
#define __DemoInduccion__Resources__

#include <iostream>

#include "Vector.h"

#include "cocos2d.h"

class Resource
{
private:
    
    vector* piMapResourcesPoints;
    
    void initArray ();
    
    void deleteArray ();
    
    vector*  initVectorWith ( int X, int Y );
    
public:
    
    Resource ();
    
    ~Resource ();
    
    vector* initResources (cocos2d::TMXTiledMap& _tileMap);
};

#endif /* defined(__DemoInduccion__Resources__) */
