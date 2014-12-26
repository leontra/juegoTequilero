//
//  MainObstacle.h
//  JuegoTequilero
//
//  Created by Max on 11/1/14.
//
//

#ifndef __JuegoTequilero__MainObstacle__
#define __JuegoTequilero__MainObstacle__

#include "ObjectEntity.h"

class MainObstacle : public ObjectEntity
{
    
public:
    MainObstacle( );
    MainObstacle( const float& x, const float& y, const float& width, const float& height );
    
    ~MainObstacle( );
    
};

#endif /* defined(__JuegoTequilero__MainObstacle__) */
