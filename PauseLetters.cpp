//
//  PauseLetters.cpp
//  JuegoTequilero
//
//  Created by Max on 12/18/14.
//
//

#include "PauseLetters.h"

PauseLetters::PauseLetters( ) : PauseObjectEntity( ), iLinesX( 0 ), _bTestLetters( 0 ), _iNTotalCorrectLetters( 1 ) { }

void PauseLetters::InitializeObjects( )
{
    int iObjectsSize = 0;
    iObjectsSize = ResourcesBuffer::GetInstance( )->getTotalLetters( );
    
    InitializeLetters( );
    ResourcesBuffer* resourceBuffer = ResourcesBuffer::GetInstance( );
    _bTestLetters = resourceBuffer->testLetters( );
 
    for( int i = 0; i < iObjectsSize; ++i )
    {
        ObjectLetter* object = resourceBuffer->testLetterCollected( i );
        if( object != nullptr && ( _bExistence = 1 ) )
        {
            bool bFound = 0;
            
            if( _bTestLetters )
                bFound = testCorrectLetter( object );
            
            if( !bFound )
                _apObjects.push_back( object );
        }
    }
}

bool PauseLetters::testCorrectLetter( ObjectLetter* letter )
{
    std::vector< std::pair<int, bool> >::iterator it;
    bool bReturn = 0;
    int idConexion = letter->getIdConexion( );
    for( it = _aLettersToCheck.begin( ); it != _aLettersToCheck.end( ); ++it )
    {
        if( idConexion == (*it).first )
        {
            (*it).second = 1;
            ++_iNTotalCorrectLetters;
            bReturn = 1;
        }
    }
    
    return 0;
}

void PauseLetters::InitializeLetters( )
{
    /*
    int aiLetters[ 17 ] =
    {
        1, 5, 18, 12, 1, 13, 1, 24, 15, 18, 5, 13, 16, 18, 5, 19, 1
    };
     */
    
    _aLettersToCheck.push_back( std::pair< int, int> { 19, 0 } );
    _aLettersToCheck.push_back( std::pair< int, int> { 5, 0 } );
    _aLettersToCheck.push_back( std::pair< int, int> { 18, 0 } );
    _aLettersToCheck.push_back( std::pair< int, int> { 12, 0 } );
    _aLettersToCheck.push_back( std::pair< int, int> { 1, 0 } );
    _aLettersToCheck.push_back( std::pair< int, int> { 13, 0 } );
    _aLettersToCheck.push_back( std::pair< int, int> { 1, 0 } );
    _aLettersToCheck.push_back( std::pair< int, int> { 24, 0 } );
    _aLettersToCheck.push_back( std::pair< int, int> { 15, 0 } );
    _aLettersToCheck.push_back( std::pair< int, int> { 18, 0 } );
    _aLettersToCheck.push_back( std::pair< int, int> { 5, 0 } );
    _aLettersToCheck.push_back( std::pair< int, int> { 13, 0 } );
    _aLettersToCheck.push_back( std::pair< int, int> { 16, 0 } );
    _aLettersToCheck.push_back( std::pair< int, int> { 18, 0 } );
    _aLettersToCheck.push_back( std::pair< int, int> { 5, 0 } );
    _aLettersToCheck.push_back( std::pair< int, int> { 19, 0 } );
    _aLettersToCheck.push_back( std::pair< int, int> { 1, 0 } );
}

void PauseLetters::getPauseObjects( cocos2d::Layer* layer, int& xOffset )
{
    if( !_bExistence )
        return;
    
    iWindowHeight = layer->getContentSize( ).height;
    iWindowWidth = layer->getContentSize( ).width;
    _Layer = layer;
    
    float y = 30;
    
    setPauseWordLine( xOffset );
    
    std::vector< ObjectLetter* >::iterator it;
    for( it = _apObjects.begin( ); it != _apObjects.end( ); ++it )
    {
        cocos2d::Sprite* spriteResource = (*it)->getSpriteForPause( xOffset, y );
        
        spriteResource->setScale( 0.5 );
        
        if( it == _apObjects.begin( ) )
            _iObjectWidth = spriteResource->getContentSize( ).width;
        
        spriteResource->setPositionY( y );
        layer->addChild( spriteResource );
        
        xOffset += _iObjectWidth + 10;
    }
    xOffset = iLinesX > xOffset ? iLinesX : xOffset;
    xOffset += _iObjectWidth + 50;
}

void PauseLetters::setPauseWordLine( const int& xOffset )
{
    int iNLine[ 3 ] = { 17, 14, 13 };
    int y = 350;
    int x = xOffset;
    int iNSpaces[ 8 ] = { 2, 4, 9, 16, 18, 28, 30, 37 };
    int index = 0;
    
    for( int i = 0; i <  3; ++ i )
    {
        for( int j = 0; j < iNLine[ i ]; ++j )
        {
            cocos2d::Sprite* spriteResource = cocos2d::Sprite::create( "BarraLetra.png" );
            spriteResource->setScale( 1 );
            spriteResource->setAnchorPoint( cocos2d::Point( 0, 0 ) );
            spriteResource->setPosition( x, y );
            _Layer->addChild( spriteResource );
            _apSprites.push_back( spriteResource );
            
            if( !i && !j )
            {
                setLetterSprite( x, y, 19 );
            }
            
            if( _bTestLetters && !i )
            {
                if( _aLettersToCheck[ j ].second )
                {
                    setLetterSprite( x, y, _aLettersToCheck[ j ].first );
                }
            }
            
             x += 45;
            for( int k = 0; k < 8; ++k )
            {
                if( index == iNSpaces[ k ] )
                {
                    x += 15;
                    break;
                }
            }
            ++index;
        }
        iLinesX = x > iLinesX ? x : iLinesX;
        x = xOffset;
        y -= 80;
    }
}

void PauseLetters::setLetterSprite( const int& x, const int& y, const int& idLetter )
{
    std::string sText = "Letra_";
    sText += idLetter < 10 ? "0" : "";
    sText += std::to_string( idLetter );
    cocos2d::Sprite* spriteLetter = cocos2d::Sprite::create( sText + ".png" );
    spriteLetter->setScale( 0.3 );
    spriteLetter->setAnchorPoint( cocos2d::Point( 0, 0 ) );
    spriteLetter->setPosition( x - 5, y + 7 );
    _Layer->addChild( spriteLetter );
    _apSprites.push_back( spriteLetter );
}

void PauseLetters::moveObjectBy( const int& iDelta )
{
    std::vector< ObjectLetter* >::iterator it;
    for( it = _apObjects.begin( ); it != _apObjects.end( ); ++it )
    {
        (*it)->getSprite( )->setPositionX( iDelta + (*it)->getSprite( )->getPositionX( ) );
    }
    
    std::vector< cocos2d::Sprite* >::iterator itSprite;
    for( itSprite = _apSprites.begin( ); itSprite != _apSprites.end( ); ++itSprite )
    {
        (*itSprite)->setPositionX( iDelta + (*itSprite)->getPositionX( ) );
    }
}

int PauseLetters::getTotalLettersCollected( )
{
    return _iNTotalCorrectLetters;
}

PauseLetters::~PauseLetters( )
{
    _apObjects.clear( );
    _apSprites.clear( );
}

