//
//  Puertas.cpp
//  JuegoTequilero
//
//  Created by Max on 7/13/14.
//
//

#include "Puertas.h"

Puertas::Puertas (): _iNPuertas (0)
{
}

Puertas::~Puertas ()
{
    this->deleteArray ();
    _piMapResourcesPoints = 0;
}

objectResource* Puertas::initResources (cocos2d::TMXTiledMap& _tileMap)
{
    _iNPuertas = 0;
    
    this->initArray ();
    
    //Obtener los diferentes objetos contenidos en el xml
    auto tileGroups = _tileMap.getObjectGroups();
    
    int iIndex = 0;
    
    //Obtener posiciones del player
    for( auto& objectGroup : tileGroups )
    {
        //Terminar si el objeto no es una puerta
        if (objectGroup->getGroupName() != "Aparicion")
            continue;
        
        //Obtener objeto
        auto objects = objectGroup->getObjects();
        
        //Revisar por cada propiedad del objeto
        for (auto& object : objects)
        {
            auto properties = object.asValueMap();
            
            auto posX = properties.at ("x");
            
            auto posY = properties.at ("y");
            
            auto width = properties.at ("width");
            
            auto height = properties.at ("height");
            
            auto puerta = properties.at ("name");
            
            if( !posX.isNull() )
            {
                ++_iNPuertas;
                
                objectResource* orPosResource = this->initVectorWith (posX.asInt(), posY.asInt(), width.asInt(), height.asInt(), puerta.asString());
                
                _piMapResourcesPoints [iIndex] = *orPosResource;
            }
            
            ++iIndex;
            
        }//For
        
    }//For
    
    return _piMapResourcesPoints;
}

objectResource* Puertas::initVectorWith (int X, int Y, int width, int height, std::string sPuerta)
{
    objectResource* orPosResource = new objectResource ();
    
    orPosResource->x = X;
    
    orPosResource->y = Y;
    
    orPosResource->width = width;
    
    orPosResource->height = height;
    
    orPosResource->name = sPuerta;
    
    return orPosResource;
}

void Puertas::initArray ()
{
    this->_piMapResourcesPoints = new objectResource [2] ();
}

void Puertas::deleteArray ()
{
    delete [] _piMapResourcesPoints;
}

int& Puertas::getINPuertas ()
{
    return _iNPuertas;
}