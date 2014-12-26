//
//  PauseKeys.cpp
//  JuegoTequilero
//
//  Created by Max on 12/18/14.
//
//

#include "PauseKeys.h"

PauseKeys::PauseKeys( ) : PauseObjectEntity( ) { }

void PauseKeys::InitializeObjects( )
{
    int iObjectsSize = 0;
    iObjectsSize = ResourcesBuffer::GetInstance( )->getTotalKeys( );
    
    for( int i = 0; i < iObjectsSize; ++i )
    {
        ObjectKey* object = ResourcesBuffer::GetInstance( )->testKeyCollected( i );
        if( object != nullptr && ( _bExistence = 1 ) )
            _apObjects.push_back( object );
    }
}

void PauseKeys::getPauseObjects( cocos2d::Layer* layer, int& xOffset )
{
    if( !_bExistence )
        return;
    
    iWindowHeight = layer->getContentSize( ).height;
    iWindowWidth = layer->getContentSize( ).width;
    _Layer = layer;
    
    float y = 20;
    
    std::vector< ObjectKey* >::iterator it;
    for( it = _apObjects.begin( ); it != _apObjects.end( ); ++it )
    {
        cocos2d::Sprite* spriteResource = (*it)->getSpriteForPause( xOffset, y );
        
        if( it == _apObjects.begin( ) )
            _iObjectWidth = spriteResource->getContentSize( ).width * 2;
        
        spriteResource->setPositionY( y );
        layer->addChild( spriteResource );
        
        y += 50 + (spriteResource->getContentSize( ).height * 2);
    }
    xOffset += _iObjectWidth + 50;
}

void PauseKeys::moveObjectBy( const int& iDelta )
{
    std::vector< ObjectKey* >::iterator it;
    for( it = _apObjects.begin( ); it != _apObjects.end( ); ++it )
    {
        (*it)->getSprite( )->setPositionX( iDelta + (*it)->getSprite( )->getPositionX( ) );
    }
}

PauseKeys::~PauseKeys( )
{
    _apObjects.clear( );
}