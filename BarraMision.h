//
//  BarraMision.h
//  JuegoTequilero
//
//  Created by Max on 7/19/14.
//
//

#ifndef __JuegoTequilero__BarraMision__
#define __JuegoTequilero__BarraMision__

#include <iostream>

#include "cocos2d.h"

class BarraMision: public cocos2d::Layer
{
    
private:
    
    int _iBarraWidth;
    int _iBarraHeight;
    int _iBarraFill;
    
    
public:
    
    BarraMision ();
    
    ~BarraMision ();
    
    bool init ();
    
    
    
    
    
};

#endif /* defined(__JuegoTequilero__BarraMision__) */
