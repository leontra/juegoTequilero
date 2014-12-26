//
//  CreateAnim.cpp
//  JuegoTequilero
//
//  Created by Max on 7/22/14.
//
//

#include "CreateAnim.h"


CreateAnim::CreateAnim (): _animateIdle (0),
                             _animateJump (0),
                             _animateWalk (0),
                             _oAnim (0),
                             _animateWalkAction (0),
                             _bIdle (0),
                             _bJump (0),
                             _bWalk (0)
{
    _oAnim = new Anim ();
}


CreateAnim::~CreateAnim ()
{
    delete _oAnim;
}


bool CreateAnim::initAnimations (cocos2d::Sprite* sprite)
{
    _animateIdle = _oAnim->startAnimation ("DonCuco_Idle_", sprite, 25, 10.0);
    
    _animateIdle->retain ();
    
    _animateWalk = _oAnim->startAnimation ("DonCuco_Walk_", sprite, 8, 8.0);
    
    _animateWalk->retain ();
    
    _animateJump = _oAnim->startAnimation ("DonCuco_Jump_", sprite, 2, 3.0);
    
    _animateJump->retain ();
    
    return 1;
}


void CreateAnim::runWalkAction (cocos2d::Sprite* sprite)
{
    if (!_bWalk)
    {
        sprite->getActionManager()->removeAllActions();

        _bWalk = 1;
        _bJump = 0;
        _bIdle = 0;
        
        printf ("\nCamina");

        cocos2d::RepeatForever* rForever = cocos2d::RepeatForever::create (_animateWalk);
    
        sprite->runAction (rForever);
    }
}

//
void CreateAnim::runIdleAction (cocos2d::Sprite* sprite)
{
    if (!_bIdle)
    {
        sprite->getActionManager()->removeAllActions ();
        
        printf ("\nIdle");
        
        _bIdle = 1;
        _bWalk = 0;
        _bJump = 0;
        
        cocos2d::Action* rForever = cocos2d::RepeatForever::create (_animateIdle);
    
        sprite->runAction (rForever);
    }
}

void CreateAnim::runJumpAction (cocos2d::Sprite* sprite)
{
    if (!_bJump)
    {
        printf ("\nBrinca");
        _bJump = 1;
        _bWalk = 0;
        _bIdle = 0;
        
        sprite->getActionManager()->removeAllActions ();
        //cocos2d::RepeatForever* rForever = cocos2d::RepeatForever::create (_animateJump);
        sprite->runAction(_animateJump);
    }
}

