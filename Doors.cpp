//
//  Doors.cpp
//  JuegoTequilero
//
//  Created by Max on 11/4/14.
//
//

#include "Doors.h"


Doors::Doors( ) : _iSize( 0 ),
                            _idDoorToConnect( 0 ),
                            _iNextRoomIndex( 0 ),
                            _bMissKey( 0 ),
                            _iDoorCollisionIndex( 0 )
{
    _oDoorsBuffer = DoorsBuffer::GetInstance( );
    _oResourcesBuffer = ResourcesBuffer::GetInstance( );
    _oEffect = new Sounds;
}

void Doors::initDoors( const int& indexRoom, cocos2d::Layer* layer )
{
    _apDoors = _oDoorsBuffer->getRoomDoorsBuffer( indexRoom );
    _Layer = layer;
    std::vector< DoorEntity* >::iterator it;
    for( it = _apDoors.begin( ); it != _apDoors.end( ); ++it )
    {
        (*it)->initSpriteWithNoScale( );
        if( (*it)->getSprite( ) != nullptr  )
            layer->addChild( (*it)->getSprite( ) );
    }
}

int Doors::testDoorsCollisions( float playerXMax, float playerYMax, float playerXMin, float playerYMin )
{
    if( _bMissKey )
        return 0;
    
    int iDoorIndex = -1;
    std::vector< DoorEntity* >::iterator it;
    for( it = _apDoors.begin( ); it != _apDoors.end( ); ++it )
    {
        ++iDoorIndex;
        //Revisar que las puertas sean solamente salidas
        if( (*it)->getType( ) == 1 )
            continue;
        
        if( ( (*it)->getXMax( ) <= playerXMin && (*it)->getYMax( ) <= playerYMin ) && ( (*it)->getXMin( ) >= playerXMax && (*it)->getYMin( ) >= playerYMax ) )
        {
            _idDoorToConnect = (*it)->getDoorId( ); //Obtener el hash de la puerta a continuar
            _iNextRoomIndex = (*it)->getNextRoomIndex( ); //Obtener el indice del mapa a continuar
            
            //Revisar que la puerta ya se haya usado
            if( (*it)->getState( ) == 3 )
            {
                _oEffect->GetEffect("opendoor", ".wav");
                return -1;
            }
            
            //Revisar que la puerta no necesite llave
            if( (*it)->getKeyId( ) == -1 )
            {
                (*it)->setState( 3 );
                _oEffect->GetEffect("opendoor", ".wav");
                return (*it)->getUpgrade( );
            }
        
            //La llave -1, para las llaves genericas
            if( _oResourcesBuffer->testKeyForDoor( (*it)->getKeyId( ) ) )
            {
                (*it)->setState( 3 );
                _oEffect->GetEffect("opendoor", ".wav");
                return (*it)->getUpgrade( );
            }
            
            setText( "¡Mmm! Creo que necesito encontrar la llave para esta puerta.\n Al parecer está cerrada." );
            _oEffect->GetEffect("lockeddoor", ".wav");
            _iDoorCollisionIndex = iDoorIndex;
            _bMissKey = 1;
            printf( "\nNo se encontró la llave" );
            return -2;
            
        }
    }
    
    _idDoorToConnect = _iNextRoomIndex = 0;
    
    return 0;
}

int Doors::testRemoveText(  const int& x, const int& y )
{
    if( _bMissKey )
    {
        DoorEntity* door = _apDoors[ _iDoorCollisionIndex ];
        
        int pointX = door->getCenterX( ) - x;
        int pointY = door->getCenterY( ) - y;
        
        int dist = sqrt( ( pointX * pointX ) + ( pointY * pointY ) );
        
        if( dist > 100 )
        {
            printf( "\nRemove text Door\n" );
            _Layer->removeChildByTag( 22 );
            _bMissKey = 0;
            _iDoorCollisionIndex = 0;
            return 1;
        }
    }
    
    return 0;
}

void Doors::setText( std::string text )
{
    auto _text = cocos2d::Label::createWithSystemFont( text, "Helvetica", 32 );
    _text->setAlignment( cocos2d::TextHAlignment::CENTER );
    _text->setAnchorPoint( cocos2d::Point( 0.5, 0.5 ) );
    _text->setOpacity( 230 );
    
    _text->setColor( cocos2d::Color3B( 255, 15, 75 ) );
    _text->setPosition(  _Layer->getContentSize( ).width / 2, _Layer->getContentSize( ).height - 50 );
    _text->setTag( 22 );
    _Layer->addChild( _text );
}

int& Doors::getNextRoomIndex( )
{
    return _iNextRoomIndex;
}

int& Doors::getNextDoorId( )
{
    return _idDoorToConnect;
}

void Doors::getPlayerInitialPosition( int& x, int& y, const int& width, const int& height )
{
    
    std::vector< DoorEntity* >::iterator it;
    for( it = _apDoors.begin( ); it != _apDoors.end( ); ++it )
    {
        if( (*it)->getHash( ) == _idDoorToConnect )
        {
            int xPos = (*it)->getCenterX( );
            int yPos = (*it)->getCenterY( );
    
            //Centrar al jugador en la puerta
            x = xPos;
    
            //Posiciona al jugador sobre el suelo
            y = yPos + height;
        }
    }
}

void Doors::resetDoors( )
{
    std::vector< DoorEntity* >::iterator it;
    for( it = _apDoors.begin( ); it != _apDoors.end( ); ++it )
    {
        (*it)->deleteSprite( );
    }
    _iSize = 0;
}


Doors::~Doors( )
{
    if( !_apDoors.empty( ) )
        _apDoors.clear( );
    
    delete _oEffect;
}



