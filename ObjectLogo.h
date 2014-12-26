//
//  ObjectLogo.h
//  JuegoTequilero
//
//  Created by Max on 10/18/14.
//
//

#ifndef __JuegoTequilero__ObjectLogo__
#define __JuegoTequilero__ObjectLogo__

#include <stdio.h>
#include "ObjectEntity.h"

class ObjectLogo : public ObjectEntity
{
    
public:
    ObjectLogo( );
    ObjectLogo( const float& x, const float& y, const float& width, const float& height );

};

#endif /* defined(__JuegoTequilero__ObjectLogo__) */
