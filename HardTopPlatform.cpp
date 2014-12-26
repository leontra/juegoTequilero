//
//  HardTopPlatform.cpp
//  JuegoTequilero
//
//  Created by Max on 10/31/14.
//
//

#include "HardTopPlatform.h"

HardTopPlatform::HardTopPlatform( ): PlatformEntity( )
{
    this->setLayerName( );
}

void HardTopPlatform::setLayerName( )
{
    this->sLayerName = "HardTopPlatform";
}


HardTopPlatform::~HardTopPlatform( ){ }