//
//  Animation.h
//  JuegoTequilero
//
//  Created by Max on 7/14/14.
//
//

#ifndef __JuegoTequilero__Animation__
#define __JuegoTequilero__Animation__

#include <iostream>

#include "cocos2d.h"

class Anim
{
private:
    
    
public:
    Anim ();
    ~Anim ();
    
    cocos2d::Animate* startAnimation (std::string sName, cocos2d::Sprite* sprite, int nSprites, float nFramesPerSecond);
    
};

#endif /* defined(__JuegoTequilero__Animation__) */
