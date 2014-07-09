//
//  CollisionsPoints.h
//  DemoInduccion
//
//  Created by Administrador on 7/6/14.
//
//

#ifndef __DemoInduccion__CollisionsPoints__
#define __DemoInduccion__CollisionsPoints__

#include <iostream>

#include "Vector.h"

#include "cocos2d.h"

class CollisionsPoints
{
    
private:
    
    int _iWidth;
    
    int _iHeight;
    
    int _iMPoints;
    
    int _iNPoints;
    
    vector* _piCollisionsPoints;
    
    void initPoints (cocos2d::TMXTiledMap& _tileMap);
    
    void setCollisionPoint ( cocos2d::TMXLayer* layer );
    
    void initNPoints ( cocos2d::TMXLayer* layer );
    
    void initArray ();
    
    void deleteArray ();
    
    vector*  initVectorWith ( int X, int Y );
    
public:
    
    CollisionsPoints ();
    
    ~CollisionsPoints ();
    
    vector* initCollisionPoints ( cocos2d::TMXTiledMap& _tileMap );
};

#endif /* defined(__DemoInduccion__CollisionsPoints__) */
