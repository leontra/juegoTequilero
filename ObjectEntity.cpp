//
//  ObjectEntity.cpp
//  JuegoTequilero
//
//  Created by Max on 10/18/14.
//
//

#include <stdio.h>
#include "ObjectEntity.h"

ObjectEntity::ObjectEntity( ) { }

ObjectEntity::ObjectEntity( const float& _x, const float& _y, const float& _width, const float& _height ):
                            x( _x ),
                            y( _y ),
                            width( _width ),
                            height( _height ),
                            hash( 0 ),
                            type( 0 ),
                            state( 0 ),
                            upgrade( 0 ),
                            idConexion( 0 ),
                            indexRoom( 0 ),
                            spriteResource( 0 )
{ }

void ObjectEntity::setObject( const int& _hash, const int& _type, const int& _indexRoom )
{
    this->hash = _hash;
    this->type = _type;
    this->indexRoom = _indexRoom;
}

void ObjectEntity::setSpriteName( std::string& _name, std::string& _extension )
{
    this->name = _name;
    this->spriteExtension = _extension;
}

void ObjectEntity::setStateUpgrade( const int& _state, const float& _upgrade )
{
    this->state = _state;
    this->upgrade = _upgrade;
}

void ObjectEntity::setConexion( const int& _conexion )
{
    
    this->idConexion = _conexion;
}

//Iniciar la imagen con escala al empezar la escena
void ObjectEntity::initSprite( )
{
    std::string spriteName = name + "." + spriteExtension;
    this->spriteResource = cocos2d::Sprite::create( spriteName );
    
    spriteResource->setScale( 0.5 );
    
    if( spriteResource != nullptr )
    {
        this->spriteResource->setAnchorPoint( cocos2d::Point( 0, 0 ) );
        this->spriteResource->setPosition( x, y );
    }
}

//Iniciar la imagen sin escala al empezar la escena
void ObjectEntity::initSpriteWithNoScale( )
{
    std::string spriteName = name + "." + spriteExtension;
    this->spriteResource = cocos2d::Sprite::create( spriteName );
    
    if( spriteResource != nullptr )
    {
        this->spriteResource->setAnchorPoint( cocos2d::Point( 0, 0 ) );
        this->spriteResource->setPosition( x, y );
    }
    
}

void ObjectEntity::deleteSprite( )
{
    if( spriteResource != nullptr )
        spriteResource->removeFromParent( );
}

float ObjectEntity::getXMax( )
{
    return x;
}

float ObjectEntity::getYMax( )
{
    return y;
}

float ObjectEntity::getXMin( )
{
    return x + width;
}

float ObjectEntity::getYMin( )
{
    return y + height;
}

int ObjectEntity::getCenterX( )
{
    return x + ( width / 2 );
}

int ObjectEntity::getCenterY( )
{
    return static_cast<int>( y );
}

int& ObjectEntity::getState( )
{
    return state;
}

int& ObjectEntity::getRoomIndex( )
{
    return indexRoom;
}

int& ObjectEntity::getHash( )
{
    return hash;
}

int& ObjectEntity::getIdConexion( )
{
    return idConexion;
}

int& ObjectEntity::getType( )
{
    return type;
}

void ObjectEntity::setState( const int& _state )
{
    this->state = _state;
}

cocos2d::Sprite* ObjectEntity::getSprite( )
{
    return spriteResource;
}

cocos2d::Sprite* ObjectEntity::getSpriteForPause( float _x, float _y )
{
    std::string spriteName = name + "." + spriteExtension;
    this->spriteResource = cocos2d::Sprite::create( spriteName );
    
    spriteResource->setScale( 2 );
    
    if( spriteResource != nullptr )
    {
        this->spriteResource->setAnchorPoint( cocos2d::Point( 0, 0 ) );
        this->spriteResource->setPosition( _x, _y );
    }
    
    return spriteResource;
}

float& ObjectEntity::getUpgrade( )
{
    return upgrade;
}

void ObjectEntity::unPaintSprite( )
{
    if( state == 1 )
    {
        state = 0;
        this->deleteSprite( );
    }
}

void ObjectEntity::resetResourceForRoom( )
{
    setState( 1 );
}

ObjectEntity::~ObjectEntity( )
{
    this->x = this->y = this->width = this->height = 0;
    this->hash = this->type = 0;
    this->name = this->spriteExtension = "";
}


