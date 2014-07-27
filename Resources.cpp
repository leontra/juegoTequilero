//
//  Resources.cpp
//  JuegoTequilero
//
//  Created by Max on 7/11/14.
//
//

#include "Resources.h"

USING_NS_CC;

Resource::Resource (): _iNRecursos (0)
{
}

Resource::~Resource ()
{
    deleteArray ();
}

bool Resource::init ()
{
    if (!Layer::init())
        return 0;
    
    return 1;
}

objectResource* Resource::initResources (cocos2d::TMXTiledMap& _tileMap)
{
    //Obtener los diferentes objetos contenidos en el xml
    auto tileGroups = _tileMap.getObjectGroups();
    
    //Obtener la cantidad de recursos por mapa
    _iNRecursos = 4;
    
    int iIndex = 0;
    
    this->initArray ();
    
    //Obtener posiciones del player
    for( auto& objectGroup : tileGroups )
    {
        //Terminar si el objeto no es un recurso
        if (objectGroup->getGroupName() != "Recurso")
            continue;
        
        //Obtener objeto
        auto objects = objectGroup->getObjects();
        
        //Revisar por cada propiedad del objeto
        for (auto& object : objects)
        {
            auto properties = object.asValueMap();
            
            auto type = properties.at ("type");
            
            auto posX = properties.at ("x");
            
            auto posY = properties.at ("y");
            
            auto width = properties.at ("width");
            
            auto height = properties.at ("height");
            
            if (!posX.isNull())
            {
                objectResource* orPosResource = this->initVectorWith (posX.asInt(), posY.asInt(), width.asInt(), height.asInt());
                
                piMapResourcesPoints [iIndex] = *orPosResource;
            }
            
            ++iIndex;
            
        }//For
        
    }//For
    
    return piMapResourcesPoints;
}

objectResource* Resource::initVectorWith (int X, int Y, int width, int height)
{
    objectResource* orPosResource = new objectResource ();
    
    orPosResource->x = X;
    
    orPosResource->y = Y;
    
    orPosResource->width = width;
    
    orPosResource->height = height;
    
    orPosResource->iActivo = 1;
    
    orPosResource->spriteResource = cocos2d::Sprite::create ("BotellaTequila.png");
    
    orPosResource->spriteResource->setAnchorPoint( Point (0, 0) );
    
    orPosResource->spriteResource->setPosition (Point(X, Y));
    
    addChild (orPosResource->spriteResource);
    
    return orPosResource;
}

void Resource::initArray ()
{
    this->piMapResourcesPoints = new objectResource [4] ();
}

int Resource::getNRecursos ()
{
    return _iNRecursos;
}

void Resource::deleteArray ()
{
    delete [] piMapResourcesPoints;
    
    _iNRecursos = 0;
    
    piMapResourcesPoints = 0;
    
    this->removeAllChildren ();
    
    this->removeFromParent ();
}

