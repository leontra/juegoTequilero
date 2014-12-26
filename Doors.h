//
//  Doors.h
//  JuegoTequilero
//
//  Created by Max on 11/4/14.
//
//

#ifndef __JuegoTequilero__Doors__
#define __JuegoTequilero__Doors__

#include "DoorsBuffer.h"
#include "ResourcesBuffer.h"
#include "Sounds.h"

class Doors
{
    
public:
    Doors( );
    
    void initDoors( const int& indexRoom, cocos2d::Layer* layer );
    
    int testDoorsCollisions( float playerXMax, float playerYMax, float playerXMin, float playerYMin );
    int testRemoveText( const int& x, const int& y );
    
    void resetDoors( );
    
    int& getNextRoomIndex( );
    int& getNextDoorId( );
    
    void getPlayerInitialPosition( int& x, int& y, const int& width, const int& height );
    
    ~Doors( );
    
private:
    
    void setText( std::string text );
    
private:
    
    int _iSize;
    
    std::vector< DoorEntity* > _apDoors;
    cocos2d::Layer* _Layer;
    
    DoorsBuffer* _oDoorsBuffer;
    ResourcesBuffer* _oResourcesBuffer;
    
    int _idDoorToConnect;
    int _iNextRoomIndex;
    bool _bMissKey;
    int _iDoorCollisionIndex;
    
    Sounds* _oEffect;
};

#endif /* defined(__JuegoTequilero__Doors__) */
