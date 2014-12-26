//
//  MatesBuffer.cpp
//  JuegoTequilero
//
//  Created by Max on 11/7/14.
//
//

#include "MatesBuffer.h"

MatesBuffer::MatesBuffer( ) { }

void MatesBuffer::setRoomBuffer( cocos2d::TMXTiledMap& tileMap, const int& roomIndex )
{
    
    //Vector de vectores, para localizar los objetos de cada nivel
    std::vector< MateEntity* > roomBuffer = *new std::vector< MateEntity* >;
    
    //Obtener todos los grupos de cada mapa
    cocos2d::Vector< cocos2d::TMXObjectGroup* > tileGroups = tileMap.getObjectGroups( );
    
    //Iterar sobre cada grupo
    for( cocos2d::TMXObjectGroup* objectGroup : tileGroups )
    {
        //Terminar si el objeto no es un objeto
        if( objectGroup->getGroupName( ) != "Companero" )
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
            int type = properties.at( "type" ).asInt( );
            // -> para el tipo, 0 == Sin herramienta requerida, 1 == Con herramienta requerida
            
            //Obtener las propiedades de cada puerta
            int idConexion = properties.at( "idConexion" ).asInt( ); // -> para la conexion con el emblema a desbloquear
            int idTool = properties.at( "idTool" ).asInt( ); // -> para la conexion con la herramienta pedida
            std::string sPopText = properties.at( "popText" ).asString( ); // -> Para el texto de la nube
            int hash = 0;
            
            //Evitar errores
            if( !object.isNull( ) )
            {
                MateEntity* oMateEntity = new MateEntity(  x, y, width ,height  );
                
                oMateEntity->setSpriteName( name, nameExtension );
                oMateEntity->setMateProperties( idTool, idConexion );
                oMateEntity->setObject( hash, type, roomIndex );
                
                
                if( type != 2 )
                {
                    std::string sPopRewardText = properties.at( "popRewardText" ).asString( );
                    oMateEntity->setStateUpgrade( 0, 25 );
                    oMateEntity->setMateTexts( sPopText, sPopRewardText );
                }
                else
                {
                    oMateEntity->setStateUpgrade( 0, 5 );
                    oMateEntity->setMateTexts( sPopText );
                }
                roomBuffer.push_back( oMateEntity );
                
            }//if
            
        }//For
        
    }//For
    
    //Agregar los objetos por cuarto
    _apBuffer.push_back( roomBuffer );
    
}//void

int MatesBuffer::getTotalRoomDoors( const int& indexRoom )
{
    std::vector< MateEntity* > buffer = _apBuffer[ indexRoom ];
    int total = ( int )buffer.size( );
    return total;
}

std::vector< MateEntity* > MatesBuffer::getRoomMatesBuffer( const int& indexRoom )
{
    std::vector< MateEntity* > buffer = _apBuffer[ indexRoom ];
    return buffer;
}

MateEntity& MatesBuffer::getRoomMateBuffer( const int& indexRoom, const int& index )
{
    std::vector< MateEntity* > buffer = _apBuffer[ indexRoom ];
    MateEntity* MateRoom = buffer[ index ];
    return *MateRoom;
}


MatesBuffer::~MatesBuffer( )
{
    _InstanceFlag = 0;
    std::vector< std::vector< MateEntity* > >::iterator it;
    for( it = _apBuffer.begin( ); it != _apBuffer.end( ); ++it )
        (*it).clear( );
    
    _apBuffer.clear( );
}



//
//
///
////
/////Singleton Pattern
int MatesBuffer::_InstanceFlag = 0;
MatesBuffer* MatesBuffer::singMatesBuffer = nullptr;

MatesBuffer* MatesBuffer::GetInstance( )
{
    if( !_InstanceFlag && ( _InstanceFlag = 1 ) )
        singMatesBuffer = new MatesBuffer( );
    
    return singMatesBuffer;
}