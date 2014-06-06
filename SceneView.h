//
//  Scene.h
//  DemoInduccion
//
//  Created by Max on 5/11/14.
//
//

#ifndef __DemoInduccion__Scene__
#define __DemoInduccion__Scene__

#include <iostream>
#include "cocos2d.h"
#include "ViewGame.h"
#include "Input.h"
#include "Player.h"
#include "BackgroundGame.h"

class SceneView: public cocos2d::Layer
{
    
    
private:
    
    
    
public:
    
    static cocos2d::Scene * createScene ();
    
    virtual bool init ();
    
    CREATE_FUNC( SceneView );
    
    
};

#endif /* defined(__DemoInduccion__Scene__) */
