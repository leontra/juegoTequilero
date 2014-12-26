//
//  ObjectLetter.cpp
//  JuegoTequilero
//
//  Created by Max on 10/18/14.
//
//

#include "ObjectLetter.h"

ObjectLetter::ObjectLetter( ) : _sLetra( " " ) { }

ObjectLetter::ObjectLetter( const float& x, const float& y, const float& width, const float& height ) :
                                        ObjectEntity( x, y, width, height ),
                                        _sLetra( " " )
{ }

void ObjectLetter::setLetra( const std::string sLetra )
{
    _sLetra = sLetra;
}