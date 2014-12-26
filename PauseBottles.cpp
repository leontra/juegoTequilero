//
//  PauseBottles.cpp
//  JuegoTequilero
//
//  Created by Max on 12/18/14.
//
//

#include "PauseBottles.h"


PauseBottles::PauseBottles( ) : iWindowWidth( 0 ),
                                                    iWindowHeight( 0 ),
                                                    _bScroll( 0 ),
                                                    _iRightX( 0 ),
                                                    _iLeftX( 0 ),
                                                    _iBottleWidth( 0 ),
                                                    _bExistence( 0 )
{ }

void PauseBottles::InitializeBottles( )
{
    int iBottlesSize = 0;
    iBottlesSize = ResourcesBuffer::GetInstance( )->getTotalBottles( );
    
    for( int i = 0; i < iBottlesSize; ++i )
    {
        ObjectBottle* bottle = ResourcesBuffer::GetInstance( )->testBottleCollected( i );
        if( bottle != nullptr && ( _bExistence = 1 ) )
            _apBottles.push_back( bottle );
    }
}

void PauseBottles::getPauseBottles( cocos2d::Layer* layer )
{
    if( !_bExistence )
        return;
    
    iWindowHeight = layer->getContentSize( ).height;
    iWindowWidth = layer->getContentSize( ).width;
    
    _iRightX = 50;
    _iLeftX = 50;
    
    float y = iWindowHeight - 10;
    _Layer = layer;
    
    std::vector< ObjectBottle* >::iterator it;
    for( it = _apBottles.begin( ); it != _apBottles.end( ); ++it )
    {
        cocos2d::Sprite* spriteResource = (*it)->getSpriteForPause( _iRightX, y );
        
        if( it == _apBottles.begin( ) )
            _iBottleWidth = spriteResource->getContentSize( ).width * 2;
        
        y = iWindowHeight - 10 - (spriteResource->getContentSize( ).height * 2);
        spriteResource->setPositionY( y );
        layer->addChild( spriteResource );
        
        _iRightX += _iBottleWidth + 10;
    }
    
    if( _iRightX >= iWindowWidth - _iBottleWidth - 20 ) _bScroll = 1;
}

void PauseBottles::moveBottlesBy( const int& iDelta )
{
    std::vector< ObjectBottle* >::iterator it;
    for( it = _apBottles.begin( ); it != _apBottles.end( ); ++it )
    {
        if( iDelta > 0 && _iLeftX >= iWindowWidth - _iBottleWidth - 20 )
            break;
        
        if( iDelta < 0 && _iRightX <= 0 + _iBottleWidth + 20 )
            break;
        
        _iLeftX += iDelta;
        _iRightX += iDelta;
        
        (*it)->getSprite( )->setPositionX( iDelta + (*it)->getSprite( )->getPositionX( ) );
    }
}

bool& PauseBottles::testIfItIsScrollable( )
{
    return _bScroll;
}

PauseBottles::~PauseBottles( )
{
    _apBottles.clear( );
}

