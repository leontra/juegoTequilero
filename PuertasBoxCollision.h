//
//  PuertasBoxCollision.h
//  JuegoTequilero
//
//  Created by Max on 7/18/14.
//
//

#ifndef __JuegoTequilero__PuertasBoxCollision__
#define __JuegoTequilero__PuertasBoxCollision__

#include <iostream>
#include "ResourceObject.h"

class PuertasBoxCollision
{
private:
    
    int* _bInicio;
    
    int _iPuertaIndex;
    int _iNPuertas;
    
    int checkPuerta (int& iMapIndex, std::string sPuerta);
    
public:
    PuertasBoxCollision (int& iPuertaIndex, int& iNPuertas, int* bInicio);
    
    ~PuertasBoxCollision ();
    
    int doCollisionsWith (int& iX, int& iY, int& iWidth, int& iHeight, objectResource* orPuertasPoints, int& iMapIndex, bool& bActionTouch);
    
    void doStartCollisionsWith (int& iX, int& iY, int& iWidth, int& iHeight, objectResource* orPuertasPoints, std::string sPuerta);
    
    int doCollisionWithSidesToExit (int& iX, int& iY, int& iWidth, int& iHeight, objectResource* orPuertasPoints, int& iMapIndex, std::string sAparicion, int& iMapWidth);
    
    void resetValues ();
    
};

#endif /* defined(__JuegoTequilero__PuertasBoxCollision__) */
