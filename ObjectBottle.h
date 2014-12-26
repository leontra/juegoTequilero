//
//  ObjectBottle.h
//  JuegoTequilero
//
//  Created by Max on 10/18/14.
//
//

#ifndef __JuegoTequilero__ObjectBottle__
#define __JuegoTequilero__ObjectBottle__

#include <stdio.h>
#include "ObjectEntity.h"

class ObjectBottle : public ObjectEntity
{
    
public:
    ObjectBottle( );
    ObjectBottle( const float& x, const float& y, const float& width, const float& height );
    
};

#endif /* defined(__JuegoTequilero__ObjectBottle__) */
