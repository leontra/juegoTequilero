//
//  BackgroundGame.h
//  JuegoTequilero
//
//  Created by Max on 7/11/14.
//
//

#ifndef __JuegoTequilero__BackgroundGame__
#define __JuegoTequilero__BackgroundGame__

#include <iostream>
#include "cocos2d.h"

class BackgroundGame  :  public cocos2d::LayerColor
{
    
private:
    int _iBackgroundWidth;
    
public:
    
    virtual bool init ();
    
    int getBackgroundWidth ();
    
    CREATE_FUNC( BackgroundGame );
};

#endif /* defined(__JuegoTequilero__BackgroundGame__) */
