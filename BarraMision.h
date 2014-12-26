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
    
    int _posX;
    int _posY;
    int _iBarraWidth;
    int _iBarraHeight;
    int _iBarraFill;
    
    int _iBarraPorcentaje;
    
    void initBarraFill ();
    
    cocos2d::SpriteFrame* _barraSpriteFrame;
    
    cocos2d::Sprite* sprite;
    
    void initBarraMisionObject (cocos2d::TMXTiledMap& _tileMap);
    
    void initVariablesBarra (cocos2d::TMXObjectGroup* group);
    
    void drawRectForBarra ();
    
    void updateBarra ();
public:
    
    BarraMision ();
    
    ~BarraMision ();
    
    bool init (cocos2d::TMXTiledMap& _tileMap);
    
    void upgradeBarraWith (int& iUpgrade);
    
    void reverseBarraWith (int& iReverse);
    
    int& getBarraFill ();
    
    void deleteBarra ();
    
    
    
};

#endif /* defined(__JuegoTequilero__BarraMision__) */
