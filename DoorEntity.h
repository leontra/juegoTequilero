//
//  DoorEntity.h
//  JuegoTequilero
//
//  Created by Max on 11/4/14.
//
//

#ifndef __JuegoTequilero__DoorEntity__
#define __JuegoTequilero__DoorEntity__

#include "ObjectEntity.h"

class DoorEntity: public ObjectEntity
{
    
public:
    DoorEntity( );
    DoorEntity( const float& _x, const float& _y, const float& _width, const float& _height );
    
    void setDoorProperties( const int& _idKey, const int& _idDoor, const int& _idConexion );
    
    int& getKeyId( );
    int& getDoorId( );
    int& getNextRoomIndex( );
    
    ~DoorEntity( );
    
protected:
    
    int idDoor;
    int idKey;
    
    bool bfAparicion;
    
};

#endif /* defined(__JuegoTequilero__DoorEntity__) */
