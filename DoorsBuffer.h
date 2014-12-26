//
//  DoorsBuffer.h
//  JuegoTequilero
//
//  Created by Max on 11/4/14.
//
//

#ifndef __JuegoTequilero__DoorsBuffer__
#define __JuegoTequilero__DoorsBuffer__

#include "DoorEntity.h"
#include <vector>

class DoorsBuffer
{
    
public:
    void setRoomBuffer( cocos2d::TMXTiledMap& tileMap, const int& roomIndex );
    
     int getTotalRoomDoors( const int& indexRoom );
    
    std::vector< DoorEntity* > getRoomDoorsBuffer( const int& indexRoom );
    
    DoorEntity& getRoomDoorBuffer( const int& indexRoom, const int& index );
    
private:
    DoorsBuffer( );
    ~DoorsBuffer( );
    
public:
    
    static DoorsBuffer* GetInstance( );
    
private:
    
    int _iDoorHash;
    
    static int _InstanceFlag;
    static DoorsBuffer* singDoorsBuffer;
    
    std::vector< std::vector< DoorEntity* > > _apBuffer;
    
};

#endif /* defined(__JuegoTequilero__DoorsBuffer__) */
