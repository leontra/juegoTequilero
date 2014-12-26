//
//  Resources.cpp
//  JuegoTequilero
//
//  Created by Max on 7/11/14.
//
//

#include "Resources.h"

USING_NS_CC;

Resource::Resource( ):   _iNRoomResources( 0 ),
                                        _iLastLetterCollected( 0 ),
                                        _bLetterCollected( 0 ),
                                        _iRoomIndex( 0 )
{
   _osResourceBuffer = ResourcesBuffer::GetInstance( );
    _oEffect = new Sounds();
}

Resource::~Resource( )
{
    _osResourceBuffer = nullptr;
    delete _oEffect;
}

bool Resource::init( )
{
    if( !Layer::init( ) )
        return 0;
    
    return 1;
}

void Resource::initResourcesRoom( const int& iRoomIndex )
{
    //Obtener la cantidad de recursos por mapa
    _iNRoomResources = _osResourceBuffer->getTotalRoomResources( iRoomIndex );
    
    _aiResourcesCollected = new int[ _iNRoomResources ];
    
    _iRoomIndex = iRoomIndex;
    
    //Iniciar arreglo para guardar direcciones de memoria
    //this->initArray( );
    
    this->setResourcesToArray( iRoomIndex );
}

void Resource::setResourcesToArray( const int& iRoomIndex )
{
    int iLetterIndex = 0;
    for( int i = 0; i < _iNRoomResources; ++i )
    {
        ObjectResource object = _osResourceBuffer->getRoomResourcesBuffer( iRoomIndex, i );
        
        if( object.getType( ) == 1 )
        {
            ObjectBottle* bottle = object.getObjectBottle( );
            if( !bottle->getState( ) ) bottle->setState( 1 );
            _apBottles.push_back( bottle );
            
            if( bottle->getState( ) == 1 )
            {
                bottle->initSprite( );
                this->addChild( bottle->getSprite( ) );
            }
            
        }
        
        if( object.getType( ) == 2 )
        {
            ObjectKey* key = object.getObjectKey( );
            
            if( !key->getState( ) ) key->setState( 1 );
            _apKeys.push_back( key );
            if( key->getState( ) == 1 )
            {
                key->initSprite( );
                this->addChild( key->getSprite( ) );
            }
            
        }
        
        if( object.getType( ) == 3 )
        {
            ObjectTool* tool = object.getObjectTool( );
            
            if( !tool->getState( ) ) tool->setState( 1 );
            _apTools.push_back( tool );
            if( tool->getState( ) == 1 )
            {
                tool->initSprite( );
                this->addChild( tool->getSprite( ) );
            }
        }
        
        if( object.getType( ) == 4 )
        {
            ObjectLetter* letter = object.getObjectLetter( );
            
            if( !letter->getState( ) ) letter->setState( 1 );
            if( letter->getState( ) == 3 )
            {
                _bLetterCollected = 1;
                _iLastLetterCollected = iLetterIndex;
            }
            _apLetters.push_back( letter );
            ++iLetterIndex;
            if( letter->getState( ) == 1 )
            {
                letter->initSprite( );
                this->addChild( letter->getSprite( ) );
            }
        }
        
        if( object.getType( ) == 5 )
        {
            ObjectLogo* logo = object.getObjectLogo( );
            
            if( !logo->getState( ) ) logo->setState( 1 );
            _apLogos.push_back( logo );
            if( logo->getState( ) == 1 )
            {
                logo->initSprite( );
                this->addChild( logo->getSprite( ) );
            }
            
        }
        
    }
}

int Resource::testResourcesCollisions( float playerXMax, float playerYMax, float playerXMin, float playerYMin )
{
    for( int i = 0; i < _apBottles.size( ); ++i )
    {
        //State 1 es el estado de pintado
        if( _apBottles[ i ]->getState( ) != 1 )
            continue;
        
        if( ( _apBottles[ i ]->getXMax( ) <= playerXMin && _apBottles[ i ]->getYMax( ) <= playerYMin ) && ( _apBottles[ i ]->getXMin( ) >= playerXMax && _apBottles[ i ]->getYMin( ) >= playerYMax ) )
        {
            _apBottles[ i ]->setState( 3 );
            _oEffect->GetEffect("bottle", ".wav");
            _apBottles[ i ]->deleteSprite( );
            return _apBottles[ i ]->getUpgrade( );
        }
    }
    
    for( int i = 0; i < _apLogos.size( ); ++i )
    {
        if( _apLogos[ i ]->getState( ) != 1 )
            continue;
        
        if( ( _apLogos[ i ]->getXMax( ) <= playerXMin && _apLogos[ i ]->getYMax( ) <= playerYMin ) && ( _apLogos[ i ]->getXMin( ) >= playerXMax && _apLogos[ i ]->getYMin( ) >= playerYMax ) )
        {
            _oEffect->GetEffect("logoflip", ".wav");
            _apLogos[ i ]->setState( 3 );
            _apLogos[ i ]->deleteSprite( );
            _osResourceBuffer->sumLogos( );
            return _apLogos[ i ]->getUpgrade( );
        }
    }
    
    for( int i = 0; i < _apLetters.size( ); ++i )
    {
        if( _apLetters[ i ]->getState( ) != 1 )
            continue;
        
        if( ( _apLetters[ i ]->getXMax( ) <= playerXMin && _apLetters[ i ]->getYMax( ) <= playerYMin ) && ( _apLetters[ i ]->getXMin( ) >= playerXMax && _apLetters[ i ]->getYMin( ) >= playerYMax ) )
        {
            if( _bLetterCollected )
            {
                _apLetters[ _iLastLetterCollected ]->setState( 1 );
                _apLetters[ _iLastLetterCollected ]->initSprite( );
                this->addChild( _apLetters[ _iLastLetterCollected ]->getSprite( ) );
            }
            _apLetters[ i ]->setState( 3 );
            this->removeChild( _apLetters[ i ]->getSprite( ) );
            _oEffect->GetEffect("letras", ".wav");
            _bLetterCollected = 1;
            _iLastLetterCollected = i; 
            
            return 0;
        }
    }
    
    for( int i = 0; i < _apKeys.size( ); ++i )
    {
        if( _apKeys[ i ]->getState( ) != 1 )
            continue;
        
        if( ( _apKeys[ i ]->getXMax( ) <= playerXMin && _apKeys[ i ]->getYMax( ) <= playerYMin ) && ( _apKeys[ i ]->getXMin( ) >= playerXMax && _apKeys[ i ]->getYMin( ) >= playerYMax ) )
        {
            if( _osResourceBuffer->testKeysCollected( ) )
            {
                int keyIndex = _osResourceBuffer->respawnLastKey( _iRoomIndex );
                if( keyIndex >= 0 )
                {
                    _apKeys[ keyIndex ]->setState( 1 );
                    this->addChild( _apLetters[ keyIndex ]->getSprite( ) );
                }
            }
            _oEffect->GetEffect("keys", ".wav");
            _osResourceBuffer->sumKeysCollectedBy( 1, _apKeys[ i ]->getHash( ) );
            _apKeys[ i ]->setState( 3 );
            _apKeys[ i ]->deleteSprite( );
            return 0;
        }
    }
    
    for( int i = 0; i < _apTools.size( ); ++i )
    {
        if( _apTools[ i ]->getState( ) != 1 )
            continue;
        
        if( ( _apTools[ i ]->getXMax( ) <= playerXMin && _apTools[ i ]->getYMax( ) <= playerYMin ) && ( _apTools[ i ]->getXMin( ) >= playerXMax && _apTools[ i ]->getYMin( ) >= playerYMax ) )
        {
            if( _osResourceBuffer->testToolsCollected( ) )
            {
                int toolIndex = _osResourceBuffer->respawnLastTool( _iRoomIndex );
                if( toolIndex >= 0 )
                {
                    _apTools[ toolIndex ]->setState( 1 );
                    this->addChild( _apTools[ toolIndex ]->getSprite( ) );
                }
            }
            _oEffect->GetEffect("toolsound", ".wav");
            _apTools[ i ]->setState( 3 );
            _apTools[ i ]->deleteSprite( );
            return 0;
        }
    }
    
    return 0;
}

int& Resource::getNRecursos ()
{
    return _iNRoomResources;
}

void Resource::resetArrays( )
{
    _iNRoomResources = 0;
    _bLetterCollected = 0;
    _iLastLetterCollected = 0;
    
    std::vector< ObjectBottle* >::iterator itBottles;
    for( itBottles = _apBottles.begin( ); itBottles != _apBottles.end( ); ++itBottles)
        (*itBottles)->unPaintSprite( );
    
    std::vector< ObjectLetter* >::iterator itLetters;
    for( itLetters = _apLetters.begin( ); itLetters != _apLetters.end( ); ++itLetters)
        (*itLetters)->unPaintSprite( );
    
    std::vector< ObjectLogo* >::iterator itLogos;
    for( itLogos = _apLogos.begin( ); itLogos != _apLogos.end( ); ++itLogos)
        (*itLogos)->unPaintSprite( );
    
    std::vector< ObjectTool* >::iterator itTools;
    for( itTools = _apTools.begin( ); itTools != _apTools.end( ); ++itTools)
        (*itTools)->unPaintSprite( );
    
    std::vector< ObjectKey* >::iterator itKeys;
    for( itKeys = _apKeys.begin( ); itKeys != _apKeys.end( ); ++itKeys)
        (*itKeys)->unPaintSprite( );
        
    _apLetters.clear( );
    _apBottles.clear( );
    _apLogos.clear( );
    _apTools.clear( );
    _apKeys.clear( );
    
    this->removeAllChildren( );
    this->removeFromParent( );
}

void Resource::resetResources( )
{
    std::vector< ObjectBottle* >::iterator itBottles;
    for( itBottles = _apBottles.begin( ); itBottles != _apBottles.end( ); ++itBottles)
        (*itBottles)->resetResourceForRoom( );
    
    std::vector< ObjectLetter* >::iterator itLetters;
    for( itLetters = _apLetters.begin( ); itLetters != _apLetters.end( ); ++itLetters)
        (*itLetters)->resetResourceForRoom( );
    
    std::vector< ObjectLogo* >::iterator itLogos;
    for( itLogos = _apLogos.begin( ); itLogos != _apLogos.end( ); ++itLogos)
        (*itLogos)->resetResourceForRoom( );
    
    std::vector< ObjectTool* >::iterator itTools;
    for( itTools = _apTools.begin( ); itTools != _apTools.end( ); ++itTools)
        (*itTools)->resetResourceForRoom( );
    
    std::vector< ObjectKey* >::iterator itKeys;
    for( itKeys = _apKeys.begin( ); itKeys != _apKeys.end( ); ++itKeys)
        (*itKeys)->resetResourceForRoom( );
}

