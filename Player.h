//
//  Player.h
//  Game Prototype
//
//  Created by Max on 4/14/14.
//
//

#ifndef __gameTest00__Player__
#define __gameTest00__Player__

#include <iostream>

#include "Input.h"

#include "cocos2d.h"

//#include "Milliseconds.h"




class Player :  public cocos2d::Layer
{
    
private:
    
    void update ( float dt );
    
    void input ();
    
    void resetValues();
    
    void updateValues ();
    
    void movement ();
    
    void collision ();
    
    void jump ();
    
    void walk();
    
    void checkForJump();
    
    void constraint();
    
    void gravity();
    
    void checkForCollisions();
    
    void setValuesForIntsStaticMembers();
    void setValuesForBoolStaticMembers();
    
    float fG;
    
    float fTiempo;
    
    float fX;
    
    float fY;
    
    float fVx;
    
    int fVy;
    
    float fAy;
    
    int iPlayerWidth;
    
    int iPlayerHeight;
    
    bool bEntro;
    
    bool bLeftTouch;
    
    bool bRightTouch;
    
    bool bTouchAction;
    
    bool fbJump;
    
    bool bJump;
    
    bool bGravity;
    
    bool bCustomGravity;
    
    bool bHorizontalLeft;
    
    bool bHorizontalRight;
    
    bool bVerticalPlus;
    
    bool bVerticalMinus;
    
    bool bTouchFloor;
    
    static int *iX;
    static int *iY;
    static int *iWidth;
    static int *iHeight;
    static int *iG;
    static int *iVx;
    static int *iVy;
    static bool *bbTouchFloor;
    static bool *bbVerticalPlus;
    static bool *bbVerticalMinus;
    static bool *bbHorizontalLeft;
    static bool *bbHorizontalRight;
    
    cocos2d::Sprite * player;
    
public:
    
    virtual bool init ();
    
    static void getAllValues( int &_iX, int &_iY, int &_iWidth, int &_iHeight, int &_iG, int &_iVx, int &_iVy);
    
    static void changeBoolAt( bool _bool,  int index);
    
    CREATE_FUNC( Player );
    
    Player ();
    
    virtual ~Player ();
    
};



#endif /* defined(__gameTest00__Player__) */
