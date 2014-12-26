//
//  ObjectLetter.h
//  JuegoTequilero
//
//  Created by Max on 10/18/14.
//
//

#ifndef __JuegoTequilero__ObjectLetter__
#define __JuegoTequilero__ObjectLetter__

#include <stdio.h>
#include "ObjectEntity.h"

class ObjectLetter : public ObjectEntity
{
    
public:
    ObjectLetter( );
    ObjectLetter( const float& x, const float& y, const float& width, const float& height );
    
    void setLetra( const std::string sLetra );
    
private:
    std::string _sLetra;
    
};

#endif /* defined(__JuegoTequilero__ObjectLetter__) */
