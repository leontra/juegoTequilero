//
//  ObjectKey.h
//  JuegoTequilero
//
//  Created by Max on 10/18/14.
//
//

#ifndef __JuegoTequilero__ObjectKey__
#define __JuegoTequilero__ObjectKey__

#include <stdio.h>
#include "ObjectEntity.h"

class ObjectKey : public ObjectEntity
{
    
public:
    ObjectKey( );
    ObjectKey( const float& x, const float& y, const float& width, const float& height );
    
};

#endif /* defined(__JuegoTequilero__ObjectKey__) */
