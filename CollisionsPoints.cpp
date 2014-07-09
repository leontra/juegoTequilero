//
//  CollisionsPoints.cpp
//  DemoInduccion
//
//  Created by Administrador on 7/6/14.
//
//

#include "CollisionsPoints.h"

#define COCOS2D_DEBUG 1

USING_NS_CC;

CollisionsPoints::CollisionsPoints ():
                                       _piCollisionsPoints (0),
                                       _iWidth (0),
                                       _iHeight (0),
                                       _iMPoints (0),
                                       _iNPoints (0)
{
    
}

CollisionsPoints::~CollisionsPoints ()
{
    deleteArray ();
}

vector* CollisionsPoints::initCollisionPoints ( cocos2d::TMXTiledMap& _tileMap )
{
    this->initPoints ( _tileMap );
    
    return _piCollisionsPoints;
}

void CollisionsPoints::initPoints ( cocos2d::TMXTiledMap& _tileMap )
{
    for( auto& object : _tileMap.getChildren() )
    {
        auto layer = dynamic_cast <cocos2d::TMXLayer*>(object);
        
        this->initNPoints ( layer );
        
        if( layer != nullptr )
            this->setCollisionPoint (layer);
    }
}

void CollisionsPoints::setCollisionPoint ( cocos2d::TMXLayer* layer )
{
    for (int i = 0; i < _iMPoints; ++i)
    {
        for (int j = 0; j < _iNPoints; ++j)
        {
            auto p = layer->getPositionAt ( Point (i, j) );
            
            vector* vPosResource = this->initVectorWith ( p.x, p.y );
            
            _piCollisionsPoints [j + (i * _iMPoints)] = *vPosResource;
        }
    }
}

void CollisionsPoints::initNPoints ( cocos2d::TMXLayer* layer )
{
    cocos2d::Size layerSize = layer->getLayerSize ();
    
    _iMPoints = layerSize.height;
    
    _iNPoints = layerSize.width;
    
    this->initArray ();
}

void CollisionsPoints::initArray ()
{
    this->_piCollisionsPoints = new vector [ (_iMPoints * _iNPoints) ] ();
}

vector* CollisionsPoints::initVectorWith ( int X, int Y )
{
    vector* vPosResource = new vector ();
    
    vPosResource->x = X;
    
    vPosResource->y = Y;
    
    return vPosResource;
}

void CollisionsPoints::deleteArray ()
{
    for (int i = 0; i < 10; ++i)
    {
        //vector vDelete = piMapResourcesPoints [i];
    }
}


