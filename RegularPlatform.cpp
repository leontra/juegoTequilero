//
//  RegularPlatform.cpp
//  JuegoTequilero
//
//  Created by Max on 10/31/14.
//
//

#include "RegularPlatform.h"

RegularPlatform::RegularPlatform( ) : PlatformEntity(  )
{
    this->setLayerName( );
}

void RegularPlatform::setLayerName( )
{
    this->sLayerName = "NormalPlatform";
}


RegularPlatform::~RegularPlatform( ){ }