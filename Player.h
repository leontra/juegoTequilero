//
//  Player.h
//  JuegoTequilero
//
//  Created by Max on 7/11/14.
//
//

#ifndef __JuegoTequilero__Player__
#define __JuegoTequilero__Player__

#include <iostream>

#include "Input.h"
#include "cocos2d.h"
#include "RegularPlatform.h"
#include "BoxCollision.h"
#include "CreateAnim.h"
#include "BreakablePlatform.h"
#include "HardTopPlatform.h"
#include "HardBottomPlatform.h"
#include "Obstacles.h"

//#include "Milliseconds.h"


class Player: public cocos2d::Layer
{
    
private:
    
    int* _iX;
    int* _iY;
    int* _iVy;
    
    int _iVx;
    int _iPlayerWidth;
    int _iPlayerHeight;
    
    bool _bOutOfBoundries;
    
    int _iMap;
    int _iWidthTile;
    int _iHeightTile;
    int _iMapWidth;
    int _iMapHeight;
    
    int _bFlip;
    
    int _iAnimState;
    
	int _iFallx;
	int _iFally;
    int _iFallAy;
    
    float _fGravedad;
    float _fG;
    float _fAy;
    float _fTiempo;
    
	float _fcronometro;
    
    bool _bLeftTouch;
    bool _bRightTouch;
    bool _bJumpTouch;
    bool _fbJump;
    bool _bActionTouch;
    
    int* _bCollisionX;
    int* _bCollisionY;
    int* _bTouchFloor;
    int* _bTouchUp;
    
    int _iMapIndex;
    
    RegularPlatform* _oRegularPlatform;
    BreakablePlatform* _oBreakablePlatform;
    HardTopPlatform* _oHardTopPlatform;
    HardBottomPlatform* _oHardBottomPlatform;
    BoxCollision* _oBoxCollisions;
    
    Obstacles* _oObstacles;
    
    Input* _oInput;
    
    CreateAnim* _oCreateAnim;
    
    cocos2d::Sprite* _spritePlayer;
    
private:
    
    void pintarPlayer (float dt);
    void input ();
    void resetValues();
    void movement ();
    void resetJumpValues ();
    void jump ();
    void walk ();
    void checkForJump ();
    void constraint ();
    void constraintXLeft ();
    void constraintXRight ();
    void constraintY ();
    void checkForCollisions ();
    void checkForBoundries( );
    void sumGravity ();
    void checkForFlip ();
    
    void initPlayer (cocos2d::TMXTiledMap& _tileMap, std::string sPuerta);
    void initObjects (cocos2d::TMXTiledMap& _tileMap);
    void initPosition (cocos2d::TMXTiledMap& _tileMap, std::string sPuerta);
    void setInitialValues (int posX, int posY);
    
    void updatePlayerSprite (int& posX, int& posY);
    
    void resetPosition( );
    void destroyObjects( );
    
    void doFlipWith (int& bFlip);
    void setInitScale (std::string sAparicion);
    
    void checkForStateAnim ();
    void runAnimateActions ();
    
	void cronometro();
    
public:
    
    bool init (cocos2d::TMXTiledMap& _tileMap, float& fGravedad, std::string sPuerta, int& iMap);
    
    void destroyPlayer( );
    void getAllValues (int& iX, int& iY, int& iWidth, int& iHeight, bool& bActionTouch, int& iWidthTile);
    
    void setPlayerRoomPosition( const int& _x, const int& _y );
    
    void getPlayerSize( int& _width, int& _height );
    
public:
    
    int* getPosX ();
    int* getPosY ();
    
    float getXMax( );
    float getYMax( );
    float getXMin( );
    float getYMin( );
    
    Player ();
    ~Player ();
};

#endif /* defined(__JuegoTequilero__Player__) */
