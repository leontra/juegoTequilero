//
//  CollisionsPoints.h
//  JuegoTequilero
//
//  Created by Max on 7/11/14.
//
//

#ifndef __JuegoTequilero__CollisionsPoints__
#define __JuegoTequilero__CollisionsPoints__

#include <iostream>

#include "Vector.h"

#include "cocos2d.h"

class CollisionsPoints
{
    
private:
    
    int _lWidth;
    
    int _lHeight;
    
    int _iMPoints;
    
    int _iNPoints;
    
    int _iMapeo;
    
    vector* _piCollisionsPoints;
    
    vector* _piTransparentCollisionsPoints;
    
    vector* initVectorWith(int X, int Y, int Activo, int PA, const int& iLayer = 0);
    
    void initPoints (cocos2d::TMXTiledMap& _tileMap);
    
    void initTileLado (cocos2d::TMXTiledMap& _tileMap);
    
    void setCollisionPoint (cocos2d::TMXLayer* layer, int iLayer);
    
    void initNPoints (cocos2d::TMXLayer* layer);
    
    void initPointsTransparent (cocos2d::TMXTiledMap& _tileMap);
    
    void initArray ();
    
    void initTransparentArray ();
    
    void resetValues ();
    
public:
    
    CollisionsPoints ();
    
    ~CollisionsPoints ();
    
    vector* initCollisionPoints (cocos2d::TMXTiledMap& _tileMap);
    
	vector* initTransparentCollisionPoints(cocos2d::TMXTiledMap& _tileMap);
    
    int& getMPoints ();
    
    int& getNPoints ();
    
    int& getIWidth ();
    
    int& getIHeight ();
    
    void deleteArray ();
};


#endif /* defined(__JuegoTequilero__CollisionsPoints__) */
