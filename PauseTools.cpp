//
//  PauseTools.cpp
//  JuegoTequilero
//
//  Created by Max on 12/18/14.
//
//

#include "PauseTools.h"

PauseTools::PauseTools( ) : PauseObjectEntity( ), _bBadge( 0 ) { }

void PauseTools::InitializeObjects( )
{
    int iObjectsSize = 0;
    iObjectsSize = ResourcesBuffer::GetInstance( )->getTotalTools( );
    
    for( int i = 0; i < iObjectsSize; ++i )
    {
        ObjectTool* object = ResourcesBuffer::GetInstance( )->testToolCollected( i );
        
        if( object == nullptr )
            continue;
        
        if( object->getState( ) == 4 )
        {
            spriteResource = cocos2d::Sprite::create( "BadgeCompanerismo.png" );
            spriteResource->setScale( 1 );
            this->spriteResource->setAnchorPoint( cocos2d::Point( 0, 0 ) );
            if( spriteResource != nullptr )
                _bBadge = 1;
        }
        else
        {
            _bExistence = 1;
            _apObjects.push_back( object );
        }
    }
}

void PauseTools::getPauseObjects( cocos2d::Layer* layer, int& xOffset )
{
    if( _bBadge )
    {
        spriteResource->setPosition( xOffset, 50 );
        layer->addChild( spriteResource );
        xOffset += spriteResource->getContentSize( ).width+ 25;
    }
    
    if( !_bExistence )
        return;
    
    iWindowHeight = layer->getContentSize( ).height;
    iWindowWidth = layer->getContentSize( ).width;
    _Layer = layer;
    
    float y = 20;
    
    std::vector< ObjectTool* >::iterator it;
    for( it = _apObjects.begin( ); it != _apObjects.end( ); ++it )
    {
        cocos2d::Sprite* spriteResource = (*it)->getSpriteForPause( xOffset, y );
        
        if( it == _apObjects.begin( ) )
            _iObjectWidth = spriteResource->getContentSize( ).width * 2;
        
        spriteResource->setPositionY( y );
        layer->addChild( spriteResource );
        
        y += 50 + ( spriteResource->getContentSize( ).height * 2 );
    }
    
    xOffset += _iObjectWidth + 50;
}

void PauseTools::moveObjectBy( const int& iDelta )
{
    std::vector< ObjectTool* >::iterator it;
    for( it = _apObjects.begin( ); it != _apObjects.end( ); ++it )
    {
        (*it)->getSprite( )->setPositionX( iDelta + (*it)->getSprite( )->getPositionX( ) );
    }
    
    if( _bBadge )
    {
        spriteResource->setPositionX( spriteResource->getPositionX( ) + iDelta );
    }
}

PauseTools::~PauseTools( )
{
    _apObjects.clear( );
}

