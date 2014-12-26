//
//  DoorsBuffer.cpp
//  JuegoTequilero
//
//  Created by Max on 11/4/14.
//
//

#include "DoorsBuffer.h"

DoorsBuffer::DoorsBuffer( ) : _iDoorHash( 0 )
{ }

void DoorsBuffer::setRoomBuffer( cocos2d::TMXTiledMap& tileMap, const int& roomIndex )
{
        //Vector de vectores, para localizar los objetos de cada nivel
        std::vector< DoorEntity* > roomBuffer = *new std::vector< DoorEntity* >;
        
        //Obtener todos los grupos de cada mapa
        cocos2d::Vector< cocos2d::TMXObjectGroup* > tileGroups = tileMap.getObjectGroups( );
        
        //Iterar sobre cada grupo
        for( cocos2d::TMXObjectGroup* objectGroup : tileGroups )
        {
            //Terminar si el objeto no es un objeto
            if( objectGroup->getGroupName( ) != "Puerta" )
                continue;
            
            //Obtener objeto
            cocos2d::ValueVector objects = objectGroup->getObjects( );
            
            //Revisar por cada propiedad del objeto
            for( cocos2d::Value& object : objects )
            {
                cocos2d::ValueMap properties = object.asValueMap( );
                
                std::string name = properties.at( "name" ).asString( );
                std::string nameExtension = "png";
                float x = properties.at( "x" ).asFloat( );
                float y = properties.at( "y" ).asFloat( );
                float width = properties.at( "width" ).asFloat( );
                float height = properties.at( "height" ).asFloat( );
                int type = properties.at( "type" ).asInt( ); // -> para el tipo, 0 == SalidaEntrada, 1 == Entrada, 2 == Salida
                
                //Obtener las propiedades de cada puerta
                int idConexion =  properties.at( "idConexion" ).asInt( ); // -> para la conexion con el cuarto a seguir
                int idKey = properties.at( "idKey" ).asInt( ); // -> para la conexion con la llave a usar
                int idDoor = properties.at( "idDoor" ).asInt( ); // -> para la conexion con la puerta a usar
                int hash = _iDoorHash;
                
                //Evitar errores
                if( !object.isNull( ) )
                {
                    DoorEntity* oDoorEntity = new DoorEntity(  x, y, width ,height  );
                    
                    oDoorEntity->setSpriteName( name, nameExtension );
                    oDoorEntity->setDoorProperties( idKey, idDoor, idConexion );
                    oDoorEntity->setObject( hash, type, roomIndex );
                    oDoorEntity->setStateUpgrade( 0, 4 );
                    roomBuffer.push_back( oDoorEntity );
                    ++_iDoorHash;
                }//if
                
            }//For
            
        }//For
        
        //Agregar los objetos por cuarto
        _apBuffer.push_back( roomBuffer );
    
}//void

int DoorsBuffer::getTotalRoomDoors( const int& indexRoom )
{
    std::vector< DoorEntity* > buffer = _apBuffer[ indexRoom ];
    int total = ( int )buffer.size( );
    return total;
}

std::vector< DoorEntity* > DoorsBuffer::getRoomDoorsBuffer( const int& indexRoom )
{
    std::vector< DoorEntity* > buffer = _apBuffer[ indexRoom ];
    return buffer;
}

DoorEntity& DoorsBuffer::getRoomDoorBuffer( const int& indexRoom, const int& index )
{
    std::vector< DoorEntity* > buffer = _apBuffer[ indexRoom ];
    DoorEntity* DoorRoom = buffer[ index ];
    return *DoorRoom;
}


DoorsBuffer::~DoorsBuffer( )
{
    _InstanceFlag = 0;
    std::vector< std::vector< DoorEntity* > >::iterator it;
    for( it = _apBuffer.begin( ); it != _apBuffer.end( ); ++it )
        (*it).clear( );
    
    
    _apBuffer.clear( );
    
    
}



//
//
///
////
/////Singleton Pattern
int DoorsBuffer::_InstanceFlag = 0;
DoorsBuffer* DoorsBuffer::singDoorsBuffer = nullptr;

DoorsBuffer* DoorsBuffer::GetInstance( )
{
    if( !_InstanceFlag && ( _InstanceFlag = 1 ) )
        singDoorsBuffer = new DoorsBuffer( );
    
    return singDoorsBuffer;
}