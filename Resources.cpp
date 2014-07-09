//
//  Resources.cpp
//  DemoInduccion
//
//  Created by Administrador on 7/6/14.
//
//

#include "Resources.h"

Resource::Resource ()
{
    initArray ();
}

Resource::~Resource ()
{
    deleteArray ();
    piMapResourcesPoints = 0;
}

vector* Resource::initResources (cocos2d::TMXTiledMap& _tileMap)
{
    //Obtener los diferentes objetos contenidos en el xml
    auto tileGroups = _tileMap.getObjectGroups();
    
    //Obtener posiciones del player
    for( auto& objectGroup : tileGroups )
    {
        //Terminar si el objeto no es un recurso
        if (objectGroup->getGroupName() != "Recurso01")
            continue;
        
        //Obtener objeto
        auto objects = objectGroup->getObjects();
        
        int iIndex = 0;
        
        //Revisar por cada propiedad del objeto
        for( auto& object : objects )
        {
            auto properties = object.asValueMap();
            
            auto type = properties.at ("type");
            
            auto posX = properties.at ("x");
            
            auto posY = properties.at ("y");
            
            if( !posX.isNull() )
            {
                vector* vPosResource = this->initVectorWith( posX.asInt(), posY.asInt() );
            
                piMapResourcesPoints [iIndex] = *vPosResource;
            }
            
            ++iIndex;
        
        }//For
        
    }//For
    
    return piMapResourcesPoints;
}

vector* Resource::initVectorWith ( int X, int Y )
{
    vector* vPosResource = new vector ();
    
    vPosResource->x = X;
    
    vPosResource->y = Y;
    
    return vPosResource;
}

void Resource::initArray ()
{
    this->piMapResourcesPoints = new vector [10] ();
    
}

void Resource::deleteArray ()
{
    for (int i = 0; i < 10; ++i)
    {
        //vector vDelete = piMapResourcesPoints [i];
    }
}
