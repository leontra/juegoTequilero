//
//  DoorEntity.cpp
//  JuegoTequilero
//
//  Created by Max on 11/4/14.
//
//

#include "DoorEntity.h"

DoorEntity::DoorEntity( ) : ObjectEntity( ),
                                                idDoor( 0 ),
                                                idKey( 0 ),
                                                bfAparicion( 0 )
{ }

DoorEntity::DoorEntity( const float& _x, const float& _y, const float& _width, const float& _height ) : ObjectEntity( _x, _y, _width, _height ),
                                                                                                                                                                            idKey( 0 ),
                                                                                                                                                                            idDoor( 0 ),
                                                                                                                                                                            bfAparicion( 0 )
{ }

void DoorEntity::setDoorProperties( const int& _idKey, const int& _idDoor, const int& _idConexion )
{
    idDoor = _idDoor;
    idKey = _idKey;
    idConexion = _idConexion;
}

int& DoorEntity::getKeyId( )
{
    return idKey;
}

int& DoorEntity::getDoorId( )
{
    return idDoor;
}

int& DoorEntity::getNextRoomIndex( )
{
    return idConexion;
}

DoorEntity::~DoorEntity( )
{
    idDoor = idKey = idConexion = bfAparicion = 0;
}