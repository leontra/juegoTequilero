//
//  HardBottomPlatform.cpp
//  JuegoTequilero
//
//  Created by Max on 10/31/14.
//
//

#include "HardBottomPlatform.h"

HardBottomPlatform::HardBottomPlatform( ): PlatformEntity( )
{
    this->setLayerName( );
}

void HardBottomPlatform::setLayerName( )
{
    this->sLayerName = "HardBottomPlatform";
}


HardBottomPlatform::~HardBottomPlatform( ){ }