//
//  PauseLogo.cpp
//  JuegoTequilero
//
//  Created by Max on 12/18/14.
//
//

#include "PauseLogo.h"

PauseLogo::PauseLogo( ) : PauseObjectEntity( ), _iLogoSize( 0 ) { }

void PauseLogo::InitializeObjects( )
{
    int iObjectsSize = 0;
    iObjectsSize = ResourcesBuffer::GetInstance( )->getTotalLogos( );
    
    for( int i = 0; i < iObjectsSize; ++i )
    {
        ObjectLogo* object = ResourcesBuffer::GetInstance( )->testLogoCollected( i );
        if( object != nullptr && ( _bExistence = 1 ) )
            _apObjects.push_back( object );
    }
}

void PauseLogo::getPauseObjects( cocos2d::Layer* layer, int& xOffset )
{
    if( !_bExistence )
        return;
    
    iWindowHeight = layer->getContentSize( ).height;
    iWindowWidth = layer->getContentSize( ).width;
    _Layer = layer;
    
    _iLogoSize = 2;
    
    std::vector< ObjectLogo* >::iterator it;
    for( it = _apObjects.begin( ); it != _apObjects.end( ); ++it )
    {
        setLogoPosition((*it), xOffset );
    }
    xOffset += ( _iObjectWidth * _iLogoSize ) + 60;
}

void PauseLogo::setLogoPosition( ObjectLogo* logo, const int& xOffset )
{
    cocos2d::Sprite* spriteResource = logo->getSpriteForPause( 0, 0 );
    spriteResource->setScale( 1 );
    _iObjectWidth = (*_apObjects.begin( ))->getSprite( )->getContentSize( ).width;
    _iObjectHeight = (*_apObjects.begin( ))->getSprite( )->getContentSize( ).height;
    float y = 40;
    int x = xOffset;
    int idIndex = logo->getIdConexion( );
    
    if( idIndex == 3 )
    {
        _iLogoSize = 2;
        x += _iObjectWidth;
        spriteResource->setPosition( x, y );
    }
    
    if( idIndex == 2 )
    {
        spriteResource->setPosition( x, y );
    }
    
    if( idIndex == 1 )
    {
        _iLogoSize = 2;
        x += _iObjectWidth;
        y +=  _iObjectHeight;
        spriteResource->setPosition( x, y );
    }
    
    if( idIndex == 0 )
    {
        y += _iObjectHeight;
        spriteResource->setPosition( x, y );
    }
    
    _Layer->addChild( spriteResource );
}

void PauseLogo::moveObjectBy( const int& iDelta )
{
    std::vector< ObjectLogo* >::iterator it;
    for( it = _apObjects.begin( ); it != _apObjects.end( ); ++it )
    {
        (*it)->getSprite( )->setPositionX( iDelta + (*it)->getSprite( )->getPositionX( ) );
    }
}

PauseLogo::~PauseLogo( )
{
    _apObjects.clear( );
}

