//
//  ObjectTool.h
//  JuegoTequilero
//
//  Created by Max on 10/18/14.
//
//

#ifndef __JuegoTequilero__ObjectTool__
#define __JuegoTequilero__ObjectTool__

#include <stdio.h>
#include "ObjectEntity.h"

class ObjectTool : public ObjectEntity
{
    
public:
    ObjectTool( );
    ObjectTool( const float& x, const float& y, const float& width, const float& height );
    
};


#endif /* defined(__JuegoTequilero__ObjectTool__) */
