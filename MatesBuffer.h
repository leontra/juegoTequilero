//
//  MatesBuffer.h
//  JuegoTequilero
//
//  Created by Max on 11/7/14.
//
//

#ifndef __JuegoTequilero__MatesBuffer__
#define __JuegoTequilero__MatesBuffer__

#include "MateEntity.h"
#include <vector>

class MatesBuffer
{
    
public:
    void setRoomBuffer( cocos2d::TMXTiledMap& tileMap, const int& roomIndex );
    
    int getTotalRoomDoors( const int& indexRoom );
    
    std::vector< MateEntity* > getRoomMatesBuffer( const int& indexRoom );
    
    MateEntity& getRoomMateBuffer( const int& indexRoom, const int& index );
    
private:
    MatesBuffer( );
    ~MatesBuffer( );
    
public:
    
    static MatesBuffer* GetInstance( );
    
private:
    
    static int _InstanceFlag;
    static MatesBuffer* singMatesBuffer;
    
    std::vector< std::vector< MateEntity* > > _apBuffer;
    
};

#endif /* defined(__JuegoTequilero__MatesBuffer__) */
