//
//  Resources.h
//  JuegoTequilero
//
//  Created by Max on 7/11/14.
//
//

#ifndef __JuegoTequilero__Resources__
#define __JuegoTequilero__Resources__

#include <iostream>

#include "ResourceObject.h"

#include "cocos2d.h"

class Resource: public cocos2d::Layer
{
private:
    int _iNRecursos;
    
    objectResource* piMapResourcesPoints;
    
    void initArray ();
    
    objectResource*  initVectorWith ( int X, int Y, int width, int height );
    
public:
    
    Resource ();
    
    ~Resource ();
    
    void deleteArray ();
    
    int getNRecursos ();
    
    objectResource* initResources (cocos2d::TMXTiledMap& _tileMap);
    
    
    bool init ();
};


#endif /* defined(__JuegoTequilero__Resources__) */
