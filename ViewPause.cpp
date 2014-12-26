//
//  ViewPause.cpp
//  JuegoTequilero
//
//  Created by Max on 12/18/14.
//
//

#include "ViewPause.h"
#define COCOS2D_DEBUG 1
USING_NS_CC;

ViewPause::ViewPause( ) : _iRightX( 0 ), _iLeftX( 0 ), _iStartLeftX( 0 ), _iStartRightX( 0 ) { }

bool ViewPause::init( )
{
    if( !Layer::init( ) )
        return 0;
    
    _oPauseBottles = new PauseBottles( );
    _oPauseKeys = new PauseKeys( );
    _oPauseTools = new PauseTools( );
    _oPauseLogo = new PauseLogo( );
    _oPauseLetters = new PauseLetters( );
    
    this->InitDisplay( );
    
    return 1;
}

void ViewPause::InitDisplay( )
{
    _oPauseBottles->InitializeBottles( );
    _oPauseBottles->getPauseBottles( this );
    
    _iLeftX = _iRightX = _iStartLeftX =  50;
    
    _oPauseKeys->InitializeObjects( );
    _oPauseKeys->getPauseObjects( this, _iRightX );
    
    _oPauseTools->InitializeObjects( );
    _oPauseTools->getPauseObjects( this, _iRightX );
    
    _oPauseLogo->InitializeObjects( );
    _oPauseLogo->getPauseObjects( this, _iRightX );
    
    _oPauseLetters->InitializeObjects( );
    _oPauseLetters->getPauseObjects( this, _iRightX );
    
    _iStartRightX = _iRightX;
}

void ViewPause::moveTopScroll( const int& iDelta )
{
    if( _oPauseBottles->testIfItIsScrollable( ) )
        _oPauseBottles->moveBottlesBy( iDelta );
}

void ViewPause::moveMainScroll( const int& iDelta )
{
     //if( _iRightX <= this->getContentSize( ).width - 50 )
     //return;
     
    //if( iDelta > 0 && _iLeftX <= _iStartLeftX )
       // moveObjectsBy( iDelta );
    
    //if( iDelta < 0 && _iRightX >= _iStartRightX )
        moveObjectsBy( iDelta );

}

void ViewPause::moveObjectsBy( const int& iDelta )
{
    _oPauseKeys->moveObjectBy( iDelta );
    _oPauseTools->moveObjectBy( iDelta );
    _oPauseLogo->moveObjectBy( iDelta );
    _oPauseLetters->moveObjectBy( iDelta );
    
    _iLeftX += iDelta;
    _iRightX += iDelta;
}

void ViewPause::clean( )
{
    //printf( "~Clean\n" );
    removeAllChildren( );
    delete _oPauseBottles;
    delete _oPauseKeys;
}

ViewPause::~ViewPause( )
{
    //printf( "~ViewPause\n" );
}

