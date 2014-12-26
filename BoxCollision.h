//
//  BoxCollision.h
//  JuegoTequilero
//
//  Created by Max on 7/11/14.
//
//

#ifndef __JuegoTequilero__BoxCollision__
#define __JuegoTequilero__BoxCollision__

#include <iostream>
#include <vector>

#include "cocos2d.h"
#include "Vector.h"
#include "Milliseconds.h"

class BoxCollision
{
    
public:
    
    BoxCollision( );
    BoxCollision( int& tileWidth, int& tileHeight, int& iMPoints, int& iNPoints, float& fGravedad, int* bCollisionX, int* bCollisionY, int* bTouchFloor, int* bTouchUp );
    
    void doMapping( const int& x, const int& y );
    
    void doCollisionWithRegularPlatforms( int* iX, int* iY, int& iWidth, int& iHeight, int& iVx, int* iVy, vector* vCollision );
    void doCollisionWithBreakablePlatforms( int* iY, int& iHeight, int* iVy, vector* vCollision );
    void doCollisionWithHardTopPlatforms( int* iY, int& iHeight, int* iVy, vector* vCollision );
    void doCollisionWithHardBottomPlatforms( int* iY, int& iHeight, int* iVy, vector* vCollision );
    
    void resetValues( );
    
    ~BoxCollision( );
    
private:
    
	//void checkForCollisions( int* iX, int* iY, int& iVx, int* iVy, int& iWidth, int& iHeight, int& iVectorX, int& iVectorY );
    
	void getValues( int* iVy );
    
	void checkForRightCollision( int* iX, int& iVx, int& iWidth, int& iVectorX );
	void checkForLeftCollision( int* iX, int& iVx, int& iWidth, int& iVectorX );
	void checkForFloorCollision( int* iY, int* iVy, int& iHeight, int& iVectorY );
    void checkForTopCollision( int* iY, int* iVy, int& iHeight, int& iVectorY );
    
	void testBreakablePlatformsCollisions( int* iY, int* iVy, int& iHeight, int& iVectorY );

	void sumContador( );
    
	Milliseconds* _oCronometro;
    
private:
    
    int _iMapping;
    int _iLastMapping;
    int _iTotalPoints;
    int _aiSumaParaEncontrarTile[ 4 ];
    int _iBreakPlatform;
    
    int& _lTileWidth;
    int& _lTileHeight;
    int& _iMPoints;
    int& _iNPoints;
    float _fGravedad;
    
    int* _bCollisionX;
    int* _bCollisionY;
    int* _bTouchFloor;
    int* _bTouchUp;
    
    int _iDuracionPlataforma;
    int _iContador;
    
    int _iTempVy;
    
};





#endif /* defined(__JuegoTequilero__BoxCollision__) */
