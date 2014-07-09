//
//  ViewGame.h
//  DemoInduccion
//
//  Created by Max on 5/11/14.
//
//

#ifndef __DemoInduccion__ViewGame__
#define __DemoInduccion__ViewGame__

#include <iostream>

#include "cocos2d.h"

#include "Player.cpp"

#include "BoxCollision.h"

#include "Platform.h"

#include "Map.h"

#include "Resources.h"

#include "CollisionsPoints.h"


class ViewGame: public cocos2d::Layer
{
private:
    
    const float _kPixelsPerMeter = 32.0f;
    
    int iPx, iPy, iPwidth, iPheight, iPG, iPvx, iPvy;
    
    bool bHorizontalRight, bHorizontalLeft, bVerticalPlus, bVerticalMinus;
    
    void checkForCollisions();
    
    void collisions();
    
    cocos2d::TMXTiledMap* _tileMap;
    
    MapWorld* _oMap;
    
    Resource* _oResource;
    
    CollisionsPoints* _oCollisionsPoints;
    
    vector* _piResourcePoints;
    
    vector* _piCollisionPoints;
    
public:
    
    ViewGame ();
    
    ~ViewGame ();
    
    bool init ();
    
    void update(float dt);
    
    
    Platform * platformArray [ 3 ];
    
    CREATE_FUNC( ViewGame );
    
    
    
};

#endif /* defined(__DemoInduccion__ViewGame__) */
