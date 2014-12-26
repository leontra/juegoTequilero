//
//  BreakablePlatform.cpp
//  JuegoTequilero
//
//  Created by Max on 10/31/14.
//
//

#include "BreakablePlatform.h"

BreakablePlatform::BreakablePlatform( ): PlatformEntity( )
{
    this->setLayerName( );
}

void BreakablePlatform::setLayerName( )
{
    this->sLayerName = "BreakablePlatform";
}


BreakablePlatform::~BreakablePlatform( ){ }