//
//  Mates.cpp
//  JuegoTequilero
//
//  Created by Max on 11/7/14.
//
//

#include "Mates.h"

Mates::Mates( ) :    _iSize( 0 ),
                                _bText( 0 ),
                                _iActualMate( 0 )
{
    _oMatesBuffer = MatesBuffer::GetInstance( );
    _oResourcesBuffer = ResourcesBuffer::GetInstance( );
    _oEffect = new Sounds();
}

//Inicializar los compañeros al entrar a una escena
void Mates::initMates( const int& indexRoom, cocos2d::Layer* layer )
{
    _apMates = _oMatesBuffer->getRoomMatesBuffer( indexRoom );
    
    std::vector< MateEntity* >::iterator it;
    for( it = _apMates.begin( ); it != _apMates.end( ); ++it )
    {
        (*it)->initSprite( );
        if( (*it)->getSprite( ) != nullptr  )
            layer->addChild( (*it)->getSprite( ) );
    }
}


int Mates::testMatesCollisions( const int& x, const int& y, cocos2d::Layer* layer )
{

    std::vector< MateEntity* >::iterator it;
    for( it = _apMates.begin( ); it != _apMates.end( ); ++it )
    {
        int pointX = (*it)->getCenterX( ) - x;
        int pointY = (*it)->getCenterY( ) - y;
        
        int dist = sqrt( ( pointX * pointX ) + ( pointY * pointY ) );
        
        if( dist < (*it)->getRadiusDetection( ) )
        {
            //Revisar que la compañero ya se haya usado
            if( (*it)->getState( ) == 3 && ( _bText = 1 ) )
            {
                if( (*it)->getType( ) == 1 )
                    setText( layer,  (*it)->getRewardText( ) );
                else
                {
                    _oEffect->GetEffect("talk", ".wav");
                    setText( layer,  (*it)->getText( ) );
                }
                _it = it;
                return -1;
            }
            
            //Revisar que el compañero no necesite herramienta
            if( (*it)->getType( ) == 2 )
            {
                (*it)->setState( 3 );
                _bText = 1;
                setText( layer,  (*it)->getText( ) );
                _it = it;
                _oEffect->GetEffect("hey", ".wav");
                printf( "\nCompañero no necesita herramienta" );
                return (*it)->getUpgrade( );
            }
            
            if( _oResourcesBuffer->testToolForMate( (*it)->getToolId( ) ) )
            {
                _bText = 1;
                setText( layer,  (*it)->getRewardText( ) );
                (*it)->setState( 3 );
                _oEffect->GetEffect("reward", ".wav");
                _it = it;
                return (*it)->getUpgrade( );
            }
            else
            {
                //advertencia no se encontró herramienta
                setText( layer, (*it)->getText( ) );
                _oEffect->GetEffect("hey", ".wav");
                _bText = 1;
                _it = it;
                return -2;
            }
        }
    }
    
    return 0;
}

int Mates::testRemoveText(  const int& x, const int& y, cocos2d::Layer* layer )
{
    if( _bText )
    {
        int pointX = (*_it)->getCenterX( ) - x;
        int pointY = (*_it)->getCenterY( ) - y;
        
        int dist = sqrt( ( pointX * pointX ) + ( pointY * pointY ) );
        
        if( dist > (*_it)->getRadiusDetection( ) )
        {
            printf( "\nRemove text\n" );
            layer->removeChildByTag( 22 );
            _bText = 0;
            return 1;
        }
    }
    
    return 0;
}

void Mates::setText( cocos2d::Layer* layer, std::string text )
{
    auto _text = cocos2d::Label::createWithSystemFont( text, "Helvetica", 32 );
    _text->setAlignment( cocos2d::TextHAlignment::CENTER );
    _text->setAnchorPoint( cocos2d::Point( 0.5, 0.5 ) );
    _text->setOpacity( 230 );
    
    _text->setColor( cocos2d::Color3B( 255, 15, 75 ) );
    _text->setPosition(  layer->getContentSize( ).width / 2, layer->getContentSize( ).height - 70 );
    _text->setTag( 22 );
    layer->addChild( _text );
}

void Mates::resetMates( )
{
    std::vector< MateEntity* >::iterator it;
    for( it = _apMates.begin( ); it != _apMates.end( ); ++it )
    {
        (*it)->deleteSprite( );
    }
    _iSize = 0;
}

Mates::~Mates( )
{
    if( !_apMates.empty( ) )
        _apMates.clear( );
    
    delete _oEffect;
}