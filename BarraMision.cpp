//
//  BarraMision.cpp
//  JuegoTequilero
//
//  Created by Max on 7/19/14.
//
//

#include "BarraMision.h"

USING_NS_CC;

BarraMision::BarraMision (): _iBarraFill (0),
                               _iBarraWidth (0),
                               _iBarraHeight (0)
{
    
}

BarraMision::~BarraMision ()
{
    
}


bool BarraMision::init ()
{
    if (!Layer::create())
        return 0;
    
    glLineWidth (1);
    
    DrawPrimitives::setDrawColor4B (180, 180, 180, 255);
    
    DrawPrimitives::setPointSize (1);
    
    glLineWidth (1);
    
    Point filledVertices [] = {Point (10,120), Point (50,120), Point (50,170), Point (25,200), Point (10,170)};
    
    DrawPrimitives::drawSolidPoly (filledVertices, 5, Color4F (0.5f, 0.5f, 1, 1));
    
    return 1;
}