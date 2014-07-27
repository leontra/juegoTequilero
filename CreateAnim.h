//
//  CreateAnim.h
//  JuegoTequilero
//
//  Created by Max on 7/22/14.
//
//

#ifndef __JuegoTequilero__CreateAnim__
#define __JuegoTequilero__CreateAnim__

#include <iostream>

#include "cocos2d.h"

#include "Animation.h"

class CreateAnim
{
    
private:
    
    Anim* _oAnim;
    
    bool _bIdle;
    
    bool _bJump;
    
    bool _bWalk;
    
    void createAnimations ();
    
    cocos2d::Animate* _animateWalk;
    
    cocos2d::Animate* _animateIdle;
    
    cocos2d::Animate* _animateJump;
    
    cocos2d::RepeatForever* _animateWalkAction;
    
public:
    
    CreateAnim ();
    
    ~CreateAnim ();
    
    bool initAnimations (cocos2d::Sprite* sprite);
    
    void runWalkAction (cocos2d::Sprite* sprite);
    
    void runIdleAction (cocos2d::Sprite* sprite);
    
    void runJumpAction (cocos2d::Sprite* sprite);
    
    
};

#endif /* defined(__JuegoTequilero__CreateAnim__) */
