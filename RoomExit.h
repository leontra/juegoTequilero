

//
//  RoomExit.h
//  JuegoTequilero
//
//  Created by Max on 10/25/14.
//
//

#ifndef __JuegoTequilero__RoomExit__
#define __JuegoTequilero__RoomExit__

#include <iostream>
#include <vector>
#include "EntranceExit.h"
#include "cocos2d.h"
#include "Sounds.h"


class RoomExit
{
public:
    RoomExit( );
    
    ~RoomExit( );
    
    void initExits( cocos2d::TMXTiledMap& tileMap );
    bool testExitCollision( const float& xPlayerPos, const float& yPlayerPos, const float& width, const float& height );
    void resetRoom( );
    
    void getPlayerInitialPosition( int& x, int& y, const int& width, const int& height );
    
    int& getMapIndex( );
    
private:
    
    int _iSize;
    int _iMapIndex;
    int _iLastTypeConexion;
    
    float _fPlayerPosX;
    float _fPlayerPosY;
    
    int _iActualType;
    
    Sounds* _oEffect;
    
    std::vector< EntranceExit* > _aoEntranceExit;
};

#endif /* defined(__JuegoTequilero__RoomExit__) */




