//
//  FilosofiaIntroduction.cpp
//  JuegoTequilero
//
//  Created by Max on 12/20/14.
//
//

#include "FilosofiaIntroduction.h"

FilosofiaIntroduction::FilosofiaIntroduction( ) :   
                                                                                _sFirstText( "" ),
                                                                                _sSecondText( "" ),
                                                                                _sThirdText( "" ),
                                                                                _iWindowWidth( 0 ),
                                                                                _iFirstTextX( 0 ),
                                                                                _iSecondTextX( 0 ),
                                                                                _iThirdTextX( 0 ),
                                                                                _bRoomText( 0 ),
                                                                                _bFirst( 0 ),
                                                                                _bSecond( 0 ),
                                                                                _bThird( 0 )
{ }

void FilosofiaIntroduction::InitializeFilosofia( cocos2d::Layer* layer )
{
    _Layer = layer;
    _iWindowWidth = layer->getContentSize( ).width;
    int iWindowDivide = _iWindowWidth / 15;
    _bRoomText = 1;
    _sFirstText = "LA DIGINIDAD HUMANA";
    _iFirstTextX = iWindowDivide;
    
    _sSecondText = "NO ESTÁ POR ENCIMA";
    _iSecondTextX = iWindowDivide * 3;
    
    _sThirdText = "DE CUALQUIER CONSIDERACIÓN ECONÓMICA";
    _iThirdTextX = iWindowDivide * 5;
}

void FilosofiaIntroduction::testFilosofiaText( const float& fPlayerPosition )
{
    float fWindowDivide = _iWindowWidth / 5;
    int yPos = _Layer->getContentSize( ).height;
    
    if( !_bThird && fPlayerPosition > fWindowDivide * 3 )
    {
        createLabel( _sThirdText, _iThirdTextX, yPos - 270 );
        _bThird = 1;
        return;
    }
    else if( !_bSecond && fPlayerPosition > fWindowDivide * 2 )
    {
        createLabel( _sSecondText, _iSecondTextX, yPos - 180 );
        _bSecond = 1;
        return;
    }
    else if( !_bFirst && fPlayerPosition > fWindowDivide )
    {
        createLabel( _sFirstText, _iFirstTextX, yPos - 100 );
        _bFirst = 1;
        return;
    }
}

void FilosofiaIntroduction::createLabel( const std::string& sText, const int& xPosition, const int& yPosition )
{
    auto text = cocos2d::Label::createWithSystemFont( sText, "Helvetica", 30 );
    text->setAlignment( cocos2d::TextHAlignment::LEFT );
    text->setAnchorPoint( cocos2d::Point( 0.0, 0.0 ) );
    text->setColor( cocos2d::Color3B( 210, 95, 45 ) );
    text->setPosition( xPosition, yPosition );
    
    _Layer->addChild( text, 0 );
}

void FilosofiaIntroduction::setFilosofiaCompleteText( )
{
     int yPos = _Layer->getContentSize( ).height;
    
    createLabel( _sFirstText, _iFirstTextX, yPos - 100 );
    createLabel( _sSecondText, _iSecondTextX, yPos - 180 );
    createLabel( _sThirdText, _iThirdTextX, yPos - 270 );
}

bool& FilosofiaIntroduction::testIfItIsTheRoom( )
{
    return _bRoomText;
}

FilosofiaIntroduction::~FilosofiaIntroduction( )
{
    _sFirstText = _sSecondText = _sThirdText = "";
}