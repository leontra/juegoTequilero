//
//  MateEntity.cpp
//  JuegoTequilero
//
//  Created by Max on 11/7/14.
//
//

#include "MateEntity.h"

MateEntity::MateEntity( ) : ObjectEntity(  ), idTool( 0 ), sPopText( "" ), fRadiusDetection( 0 ) { }

MateEntity::MateEntity( const float& _x, const float& _y, const float& _width, const float& _height ) :   ObjectEntity( _x, _y, _width, _height ),
                                                                                                                                                                            sPopText( "" ),
                                                                                                                                                                            sPopRewardText( "" ),
                                                                                                                                                                            idTool( 0 ),
                                                                                                                                                                            fRadiusDetection( 80 )
{ }

void MateEntity::setMateProperties( int _idTool, int _idConexion )
{
    idTool = _idTool;
    
    idConexion = _idConexion;
}

void MateEntity::setMateTexts( std::string _sPopText, std::string _sPopRewardText )
{
    sPopText = _sPopText;
    sPopRewardText = _sPopRewardText;
}

int MateEntity::getCenterX( )
{
    return x + ( width / 2 );
}

int MateEntity::getCenterY( )
{
    return y + ( height / 2 );
}

int& MateEntity::getToolId( )
{
    return idTool;
}

std::string MateEntity::getText( )
{
    return sPopText;
}

std::string MateEntity::getRewardText( )
{
    return sPopRewardText;
}

float MateEntity::getRadiusDetection( )
{
    return fRadiusDetection;
}

MateEntity::~MateEntity( ) { }



