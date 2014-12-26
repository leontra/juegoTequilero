//
//  Obstacles.h
//  JuegoTequilero
//
//  Created by Max on 11/1/14.
//
//

#ifndef __JuegoTequilero__Obstacles__
#define __JuegoTequilero__Obstacles__

#include "MainObstacle.h"
#include "Sounds.h"

class Obstacles
{
    
public:
    Obstacles( );
    
    void initObstacles( cocos2d::TMXTiledMap& _tileMap, cocos2d::Layer* layer );
    
    bool testObstaclesCollisions( float playerXMax, float playerYMax, float playerXMin, float playerYMin );
    
    void resetObstacles( );
    
    ~Obstacles( );
    
private:
    
    int _iSize;
    Sounds* _oEffect;
    
    std::vector< MainObstacle > _apObstacles;
    
};

#endif /* defined(__JuegoTequilero__Obstacles__) */
