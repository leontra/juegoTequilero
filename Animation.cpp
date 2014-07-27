//
//  Animation.cpp
//  JuegoTequilero
//
//  Created by Max on 7/14/14.
//
//

#include "Animation.h"

USING_NS_CC;


Anim::Anim ()
{
    
}

Anim::~Anim ()
{
}


cocos2d::Animate* Anim::startAnimation (std::string sName, cocos2d::Sprite* sprite, int nSprites, float nFramesPerSecond)
{
    cocos2d::Vector<SpriteFrame*> animFrames(nSprites);
    
    char str[100] = {0};
    
    cocos2d::Sprite* sSprite = cocos2d::Sprite::create(sName + "0000.png");
    
    for(int i = 0; i < nSprites; ++i)
    {
        sprintf(str, "%s%04d.png", sName.c_str(),i);
        
        auto frame = cocos2d::SpriteFrame::create(str,Rect (0, 0, sSprite->getContentSize().width, sSprite->getContentSize().height));
        
        animFrames.pushBack (frame);
        
        //sprite->setSpriteFrame (frame);
    }

    //Crear la animacion con la imagen de cada cuadro y el numero de frames a la que correra
    auto animation = cocos2d::Animation::createWithSpriteFrames (animFrames, (nFramesPerSecond / 60.0f));
    
    auto animate = cocos2d::Animate::create (animation);
    
    return animate;
}