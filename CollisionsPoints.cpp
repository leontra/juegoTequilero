//
//  CollisionsPoints.cpp
//  JuegoTequilero
//
//  Created by Max on 7/11/14.
//
//

#include "CollisionsPoints.h"


#define COCOS2D_DEBUG 1

USING_NS_CC;

CollisionsPoints::CollisionsPoints ():
                                            _piCollisionsPoints (0),
                                            _piTransparentCollisionsPoints (0),
                                            _lWidth (0),
                                            _lHeight (0),
                                            _iMPoints (0),
                                            _iNPoints (0)
{
}

CollisionsPoints::~CollisionsPoints ()
{
    deleteArray ();
}

vector* CollisionsPoints::initCollisionPoints (cocos2d::TMXTiledMap& _tileMap)
{
    this->initTileLado (_tileMap);
    
    this->initPoints (_tileMap);
    
    return _piCollisionsPoints;
}

vector* CollisionsPoints::initTransparentCollisionPoints(cocos2d::TMXTiledMap& _tileMap)
{
    this->initPointsTransparent (_tileMap);
    
    return _piTransparentCollisionsPoints;
}

int& CollisionsPoints::getMPoints ()
{
    return _iMPoints;
}

int& CollisionsPoints::getNPoints ()
{
    return _iNPoints;
}

int& CollisionsPoints::getIWidth ()
{
    return _lWidth;
}

int& CollisionsPoints::getIHeight ()
{
    return _lHeight;
}

void CollisionsPoints::initPoints (cocos2d::TMXTiledMap& _tileMap)
{
    
    for( auto& object : _tileMap.getChildren() )
    {
        auto layer = dynamic_cast <cocos2d::TMXLayer*>(object);
        
        auto layerName = layer->getLayerName ();
        
        if (layerName != "CollisionLayer")
            continue;
        
        this->initNPoints ( layer );
        
        if (!_piCollisionsPoints)
            this->initArray ();
        
        if( layer != nullptr )
            this->setCollisionPoint (layer, 0);
    }
}

void CollisionsPoints::initTileLado (cocos2d::TMXTiledMap& _tileMap)
{
    auto tileGroups = _tileMap.getObjectGroups ();
    
    auto tileSize = _tileMap.getTileSize ();
    
    _lWidth = tileSize.width;
    
    _lHeight = tileSize.height;
    
}

void CollisionsPoints::setCollisionPoint (cocos2d::TMXLayer* layer, int iLayer)
{
    
    for (int y = 0; y < _iNPoints; ++y)
    {
        for (int x = 0; x < _iMPoints; ++x)
        {
            //Hacer el recorrido por cada X en Y
            auto p = layer->getPositionAt (Point (x, y));
            
            printf ("\n\nPunto: (%d, %d)", x, y);
            
            auto tileSprite = layer->getTileAt (Point (x, y));
            
            //Colocar activo falso donde no hay tile
            int bActivo = 0;
            
            //Agregar solo los existentes cuadros en el mapa
            if (tileSprite)
            {
                //log ( "\nEl valor del tile = (%f  :  %f)", p.x, p.y);
                bActivo = 1;
            }
            
            if (!iLayer)
                _piCollisionsPoints [x + (y * _iMPoints)] = *(this->initVectorWith (int (p.x), int (p.y), bActivo));
            if (iLayer)
            {
                int iLayer = 0;
                if (bActivo && layer->getLayerName() == "TransparentPlatformsTop")
                    iLayer = 1;
                
                if (!_piTransparentCollisionsPoints [x + (y * _iMPoints)].iActivo)
                    _piTransparentCollisionsPoints [x + (y * _iMPoints)] = *(this->initVectorWith (int (p.x), int (p.y), bActivo, iLayer));
            }
        }
    }
}

void CollisionsPoints::initNPoints (cocos2d::TMXLayer* layer)
{
    cocos2d::Size layerSize = layer->getLayerSize ();
    
    _iMPoints = layerSize.width;
    
    _iNPoints = layerSize.height;
}

void CollisionsPoints::initArray ()
{
    this->_piCollisionsPoints = new vector [(_iMPoints * _iNPoints)] ();
}

void CollisionsPoints::initPointsTransparent(cocos2d::TMXTiledMap& _tileMap)
{
    for( auto& object : _tileMap.getChildren() )
    {
        auto layer = dynamic_cast <cocos2d::TMXLayer*>(object);
        
        auto layerName = layer->getLayerName();
        
        if (layerName != "TransparentPlatformsBottom" && layerName != "TransparentPlatformsTop")
            continue;
        
        if (!_iNPoints && !_iMPoints)
            this->initNPoints (layer);
        
        if (!_piTransparentCollisionsPoints)
            this->initTransparentArray ();
        
        if (layer != nullptr )
            this->setCollisionPoint (layer, 1);
    }
    
}

void CollisionsPoints::initTransparentArray ()
{
    this->_piTransparentCollisionsPoints = new vector [(_iMPoints * _iNPoints)] ();
}

vector* CollisionsPoints::initVectorWith (int X, int Y, int Activo, const int& iLayer)
{
    vector* vPosCollision = new vector ();
    
    vPosCollision->x = X;
    
    vPosCollision->y = Y;
    
    vPosCollision->iActivo = Activo;
    
    vPosCollision->iToB = iLayer;
    
    return vPosCollision;
}

void CollisionsPoints::deleteArray ()
{
    delete [] _piCollisionsPoints;
    
    delete [] _piTransparentCollisionsPoints;
    
    _piCollisionsPoints = 0;
    
    _piTransparentCollisionsPoints = 0;
    
    this->resetValues ();
}

void CollisionsPoints::resetValues ()
{
    _iMPoints = 0;
    _iNPoints = 0;
    _lWidth = 0;
    _lHeight = 0;
}


