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

#include "cocos2d.h"

#include "Vector.h"

#include "Milliseconds.h"

class BoxCollision
{
    
private:
    
    int& _lTileWidth;
    int& _lTileHeight;
    int& _iMPoints;
    int& _iNPoints;
    
    int* _bCollisionX;
    int* _bCollisionY;
    int* _bTouchFloor;
    int* _bTouchUp;
    
    int _iContador;
    
    int _iTempVy;
    
    float& _fGravedad;
    
    void checkForCollisions (int* iX, int* iY, int& iVx, int* iVy, int& iWidth, int& iHeight, int& iVectorX, int& iVectorY);
    
    void getValues (int* iVy);
    
    void checkForRightCollision (int* iX, int& iVx, int& iWidth, int& iVectorX);
    void checkForLeftCollision (int* iX, int& iVx, int& iWidth, int& iVectorX);
    
    void checkForFloorCollision (int* iY, int* iVy, int& iHeight, int& iVectorY);
	void checkForFloorTransparentCollision(int* iX, int* iY, int& iVx, int* iVy, int& iWidth, int& iHeight, int& iVectorX, int& iVectorY);
    void checkForTopCollision (int* iY, int* iVy, int& iHeight, int& iVectorY);
	void checkForTopTransparentCollision(int* iX, int* iY, int& iVx, int* iVy, int& iWidth, int& iHeight, int& iVectorX, int& iVectorY);
    
    void sumContador ();
    
    Milliseconds* _oCronometro;
    
public:
    
    BoxCollision (int& tileWidth, int& tileHeight, int& iMPoints, int& iNPoints, float& fGravedad, int* bCollisionX, int* bCollisionY, int* bTouchFloor, int* bTouchUp);
    
    ~BoxCollision ();
    
    void doCollisionWith (int* iX, int* iY, int& iWidth, int& iHeight, int& iVx, int* iVy, vector* vCollision);
    
	void doCollisionWithTransparentPlatform(int* iX, int* iY, int& iWidth, int& iHeight, int& iVx, int* iVy, vector* vCollision);
    
    void resetValues ();
};




#endif /* defined(__JuegoTequilero__BoxCollision__) */
