//
//  Puertas.h
//  JuegoTequilero
//
//  Created by Max on 7/13/14.
//
//

#ifndef __JuegoTequilero__Puertas__
#define __JuegoTequilero__Puertas__

#include <iostream>

#include "Resources.h"

#include "ResourceObject.h"

class Puertas: public Resource
{
private:
    
    int _iNPuertas;
    
    objectResource* _piMapResourcesPoints;
    
    void initArray ();
    
    void deleteArray ();
    
    objectResource*  initVectorWith (int X, int Y, int width, int height, std::string sPuerta);
    
public:
    
    Puertas ();
    
    ~Puertas ();
    
    int& getINPuertas ();
    
    objectResource* initResources (cocos2d::TMXTiledMap& _tileMap);
    
};

#endif /* defined(__JuegoTequilero__Puertas__) */
