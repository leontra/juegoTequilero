//
//  EntranceExit.cpp
//  JuegoTequilero
//
//  Created by Max on 10/25/14.
//
//

#include "EntranceExit.h"

EntranceExit::EntranceExit( ) :    _fX( 0 ),
                                                _fY( 0 ),
                                                _iType( 0 ),
                                                _idConexion( 0 ),
                                                _fWidth( 0 ),
                                                _fHeight( 0 )
{ }

EntranceExit::EntranceExit( const float& x, const float& y  ) :
                                        _fX( x ),
                                        _fY( y ),
                                        _iType( 0 ),
                                        _idConexion( 0 ),
                                        _fWidth( 0 ),
                                        _fHeight( 0 )
{ }

void EntranceExit::setTypeConexion( const int& type, const int& idConexion )
{
    _iType = type;
    _idConexion = idConexion;
}

void EntranceExit::setSize( const float& width, const float& height )
{
    _fWidth = width;
    _fHeight = height;
}

float& EntranceExit::getX( )
{
    return _fX;
}

float& EntranceExit::getY( )
{
    return _fY;
}

int& EntranceExit::getType( )
{
    return _iType;
}

int& EntranceExit::getIdConexion( )
{
    return _idConexion;
}

float& EntranceExit::getWidth( )
{
    return _fWidth;
}

float& EntranceExit::getHeight( )
{
    return _fHeight;
}

EntranceExit::~EntranceExit( )
{
    _fX = 0;
    _fY = 0;
    _iType = 0;
    _idConexion = 0;
    _fWidth = 0;
    _fHeight = 0;
}


