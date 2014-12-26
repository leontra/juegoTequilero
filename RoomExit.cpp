//
//  RoomExit.cpp
//  JuegoTequilero
//
//  Created by Max on 10/25/14.
//
//

#include "RoomExit.h"


RoomExit::RoomExit( ):   _iSize( 0 ),
                                    _iMapIndex( 0 ),
                                    _iLastTypeConexion( -1 ),
                                    _fPlayerPosY( 0 ),
                                    _fPlayerPosX( 0 ),
                                    _iActualType( -1 )
{
    _oEffect = new Sounds( );
}

void RoomExit::initExits( cocos2d::TMXTiledMap& tileMap )
{
    //Obtener todos los grupos de cada mapa
    cocos2d::Vector< cocos2d::TMXObjectGroup* > tileGroups = tileMap.getObjectGroups( );
    
    //Iterar sobre cada grupo
    for( cocos2d::TMXObjectGroup* objectGroup : tileGroups )
    {
        //Terminar si el objeto no es un objeto
        if( objectGroup->getGroupName( ) != "Aparicion" )
            continue;
        
        cocos2d::ValueVector objects = objectGroup->getObjects( );
        
        _iActualType = _iLastTypeConexion == 0 ? 1 : _iLastTypeConexion == 2 ? 3 : _iLastTypeConexion == 3 ? 2 : _iLastTypeConexion == 1 ? 0 : -1;
        
        //Revisar por cada propiedad del objeto
        for( cocos2d::Value& object : objects )
        {
            cocos2d::ValueMap properties = object.asValueMap( );
            
            //Condicional para el inicio del juego, la primera vez que aparece en el juego
            if( _iLastTypeConexion == -1 && properties.at( "name" ).asString( ) == "Inicio" )
            {
                _fPlayerPosX = properties.at( "x" ).asInt( );
                _fPlayerPosY = properties.at( "y" ).asInt( );
                continue;
            }
            
            int type = properties.at( "type" ).asInt( );
            
            if( _iActualType == type )
            {
                if( type == 0 )
                {
                    _fPlayerPosX = properties.at( "x" ).asFloat( );
                    _fPlayerPosY = properties.at( "y" ).asFloat( );
                }
                if( type == 1 )
                {
                    _fPlayerPosX = properties.at( "x" ).asFloat( ) + properties.at( "width" ).asFloat( );
                    _fPlayerPosY = properties.at( "y" ).asFloat( );
                }
                if( type == 2 )
                {
                    _fPlayerPosX = properties.at( "x" ).asFloat( );
                    _fPlayerPosY = properties.at( "y" ).asFloat( ) + properties.at( "height" ).asFloat( );
                }
                if( type == 3 )
                {
                    _fPlayerPosX = properties.at( "x" ).asFloat( );
                    _fPlayerPosY = properties.at( "y" ).asFloat( );
                }
            }
            
             //Obtener la conexion de la salida, hacia el cuarto que sigue
            int idConexion =  properties.at( "idConexion" ).asInt( );
            
            float x =  properties.at( "x" ).asFloat( );
            float y = properties.at( "y" ).asFloat( );
            float width = properties.at( "width" ).asFloat( );
            float  height = properties.at( "height" ).asFloat( );
            
            EntranceExit* exit = new EntranceExit( x, y );
            exit->setTypeConexion( type, idConexion );
            exit->setSize( width, height );
            
            _aoEntranceExit.push_back( exit );
            ++_iSize;
        }
    }
}

void RoomExit::getPlayerInitialPosition( int& x, int& y, const int& width, const int& height )
{ 
    if( _iLastTypeConexion == -1 )
    {
        x = _fPlayerPosX + width;
        y = _fPlayerPosY + height;
    }
    else if( _iActualType == 3 )
    {
        x = x;
        y = _fPlayerPosY + height;
    }
    else if( _iActualType ==  2 )
    {
        x = x;
        y = _fPlayerPosY - height;
    }
    else if( _iActualType == 1 )
    {
        x = _fPlayerPosX - width;
        y = y;
    }
    else if( _iActualType == 0 )
    {
        x = _fPlayerPosX + width;
        y = y;
    }
    
    
}

int& RoomExit::getMapIndex( )
{
    return _iMapIndex;
}

bool RoomExit::testExitCollision( const float& xPlayerPos, const float& yPlayerPos, const float& width, const float& height )
{
    std::vector< EntranceExit* >::iterator it;
    
    for( it = _aoEntranceExit.begin( ); it != _aoEntranceExit.end( ); ++it )
    {
        //Colisionar con la salida de abajo ---- 3
        if( (*it)->getType(  ) == 3 )
        {
            if( yPlayerPos < (*it)->getY( )  && xPlayerPos - width >= (*it)->getX( ) && xPlayerPos + width <= (*it)->getX( ) + (*it)->getWidth( ) )
            {
                _oEffect->GetEffect("scenechange", ".wav");
                _iMapIndex = (*it)->getIdConexion( );
                _iLastTypeConexion = (*it)->getType( );
                printf( "\nColision abajo\n withConnection:   %d\n", _iMapIndex);
                return 1;
            }
        }
        
        //Colisionar con la salida de arriba ---- 2
        if( (*it)->getType(  ) == 2 )
        {
            if( yPlayerPos > (*it)->getY( ) + (*it)->getHeight( ) && xPlayerPos - width >= (*it)->getX( ) && xPlayerPos + width <= (*it)->getX( ) + (*it)->getWidth( ) )
            {
                _oEffect->GetEffect("scenechange", ".wav");
                _iMapIndex = (*it)->getIdConexion( );
                _iLastTypeConexion = (*it)->getType( );
                printf( "\nColision arriba\n withConnection:   %d\n", _iMapIndex);
                return 1;
            }
        }
        
        //Colisionar con la salida de arriba ---- 1
        if( (*it)->getType(  ) )
        {
            if( xPlayerPos > (*it)->getX( ) + (*it)->getWidth( ) && yPlayerPos - height >= (*it)->getY( ) && yPlayerPos + height <= (*it)->getY( ) + (*it)->getHeight( ) )
            {
                _oEffect->GetEffect("scenechange", ".wav");
                _iMapIndex = (*it)->getIdConexion( );
                _iLastTypeConexion = (*it)->getType( );
                printf( "\nColision derecha\n withConnection:   %d\n", _iMapIndex);
                return 1;
            }
        }
        
        //Colisionar con la salida de arriba ---- 0
        if( !(*it)->getType(  ) )
        {
            if( xPlayerPos < (*it)->getX( ) && yPlayerPos - height >= (*it)->getY( ) && yPlayerPos + height <= (*it)->getY( ) + (*it)->getHeight( ) )
            {
                _oEffect->GetEffect("scenechange", ".wav");
                _iMapIndex = (*it)->getIdConexion( );
                _iLastTypeConexion = (*it)->getType( );
                printf( "\nColision izquierda\n withConnection:   %d\n", _iMapIndex);
                return 1;
            }
        }
    }
    
    return 0;
}


void RoomExit::resetRoom( )
{
    _aoEntranceExit.clear( );
    _iSize = 0;
}


RoomExit::~RoomExit( )
{
    _iMapIndex = 0;
    delete _oEffect;
    _iLastTypeConexion = -1;
    _iSize = 0;
    _aoEntranceExit.clear( );
}