//
//  PlatformEntity.cpp
//  JuegoTequilero
//
//  Created by Max on 10/31/14.
//
//

#include "PlatformEntity.h"


PlatformEntity::PlatformEntity( ):    iWidth( 0 ),
                                                    iHeight( 0 ),
                                                    iMPoints( 0 ),
                                                    iNPoints( 0 ),
                                                    piCollisionsPoints( 0 ),
                                                    iSize( 0 ),
                                                    sLayerName( "" )
{ }

void PlatformEntity::initPlatforms( cocos2d::TMXTiledMap& tileMap )
{
    this->initTileSize( tileMap );
    
    for( auto& object : tileMap.getChildren( ) )
    {
        auto layer = dynamic_cast <cocos2d::TMXLayer*>( object );
        
        auto layerName = layer->getLayerName( );
        
        if( layerName != sLayerName )
            continue;
        
        this->initNumberOfPoints( layer );
        
        if( !piCollisionsPoints )
            this->initArray( );
        
        if( layer != nullptr )
            this->setPlatformsPoints( layer );
    }
}

void PlatformEntity::initTileSize( cocos2d::TMXTiledMap& _tileMap )
{
    auto tileGroups = _tileMap.getObjectGroups( );
    auto tileSize = _tileMap.getTileSize( );
    
    iWidth = tileSize.width;
    iHeight = tileSize.height;
}

void PlatformEntity::initNumberOfPoints( cocos2d::TMXLayer* layer )
{
    cocos2d::Size layerSize = layer->getLayerSize( );
    
    iMPoints= layerSize.width;
    iNPoints = layerSize.height;
    
    iSize = iMPoints * iNPoints;
}

void PlatformEntity::initArray( )
{
    this->piCollisionsPoints = new vector[ ( iMPoints * iNPoints ) ]( );
}

void PlatformEntity::setPlatformsPoints( cocos2d::TMXLayer* layer )
{
    for( int y = 0; y < iNPoints; ++y )
    {
        for( int x = 0; x < iMPoints; ++x )
        {
            //Hacer el recorrido por cada X en Y
            auto p = layer->getPositionAt( cocos2d::Point( x, y ) );
            auto tileSprite = layer->getTileAt( cocos2d::Point( x, y ) );
            
            //Colocar activo falso donde no hay tile
            int bActivo = 0;
            
            //Agregar solo los existentes cuadros en el mapa
            if( tileSprite )
                bActivo = 1;
            
            //cocos2d::log( "\nEl valor del tile = (%f  :  %f)", p.x, p.y);
    
            vector vPlatform( p.x, p.y, bActivo );
            piCollisionsPoints[ x + ( y * iMPoints ) ] = vPlatform;
        }
    }
}


//---------------- o ------------------//
//Getters
//
vector* PlatformEntity::getPlatformsPoints( )
{
    return piCollisionsPoints;
}

int& PlatformEntity::getMPoints ()
{
    return iMPoints;
}

int& PlatformEntity::getNPoints ()
{
    return iNPoints;
}

int& PlatformEntity::getIWidth ()
{
    return iWidth;
}

int& PlatformEntity::getIHeight ()
{
    return iHeight;
}

int& PlatformEntity::getSize( )
{
    return iSize;
}
//
//

bool PlatformEntity::testPlatformCollision( )
{
    return 0;
}

void PlatformEntity::resetArray( )
{
    delete[ ] piCollisionsPoints;
    
    piCollisionsPoints = 0;
    
    this->resetValues( );
}

void PlatformEntity::resetValues( )
{
    iNPoints = iMPoints = iWidth = iHeight = iSize = 0;
    
    
}

PlatformEntity::~PlatformEntity( )
{
    this->resetArray( );
}





