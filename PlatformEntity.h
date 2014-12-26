//
//  PlatformEntity.h
//  JuegoTequilero
//
//  Created by Max on 10/31/14.
//
//

#ifndef __JuegoTequilero__PlatformEntity__
#define __JuegoTequilero__PlatformEntity__

#include <stdio.h>
#include "Vector.h"
#include "cocos2d.h"

class PlatformEntity
{
public:

    ~PlatformEntity( );
    
    void initPlatforms( cocos2d::TMXTiledMap& tileMap );
    void resetArray( );
    
    bool testPlatformCollision( );
    
    //Getters
    int& getMPoints( );
    int& getNPoints( );
    int& getSize( );
    int& getIWidth( );
    int& getIHeight( );
    vector* getPlatformsPoints( );
    
protected:
    
    PlatformEntity( );
    
    virtual void setLayerName( ) = 0;
    void initTileSize( cocos2d::TMXTiledMap& _tileMap );
    void initNumberOfPoints( cocos2d::TMXLayer* layer );
    void initArray( );
    void setPlatformsPoints( cocos2d::TMXLayer* layer );
    
    void resetValues( );
    
protected:
    
    int iWidth;
    int iHeight;
    int iMPoints;
    int iNPoints;
    
    vector* piCollisionsPoints;
    
    int iSize;
    
    std::string sLayerName;
};

#endif /* defined(__JuegoTequilero__PlatformEntity__) */
