//
//  SceneView.h
//  JuegoTequilero
//
//  Created by Max on 7/11/14.
//
//

#ifndef __JuegoTequilero__SceneView__
#define __JuegoTequilero__SceneView__

#include <iostream>

#include "cocos2d.h"
#include "ViewGame.h"
#include "Input.h"
#include "BackgroundGame.h"

class SceneView: public cocos2d::Layer
{
    
    
private:
    
    
    
public:
    
    static cocos2d::Scene * createScene ();
    
    virtual bool init ();
    
    CREATE_FUNC( SceneView );
    
    
};



#endif /* defined(__JuegoTequilero__SceneView__) */
