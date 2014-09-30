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
    _iNRecursos = 7;
    
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
            
			auto name = properties.at("name");
            
            auto type = properties.at ("type");
            
            auto posX = properties.at ("x");
            
            auto posY = properties.at ("y");
            
            auto width = properties.at ("width");
            
            auto height = properties.at ("height");
            
            if (!posX.isNull())
            {
				objectResource* orPosResource = this->initVectorWith(posX.asInt(), posY.asInt(), width.asInt(), height.asInt(), type.asInt(), name.asString());
                
                piMapResourcesPoints [iIndex] = *orPosResource;
            }
            
            ++iIndex;
            
        }//For
        
    }//For
    
    return piMapResourcesPoints;
}

objectResource* Resource::initVectorWith(int X, int Y, int width, int height, int type, std::string name)
{
    objectResource* orPosResource = new objectResource ();
    
    orPosResource->x = X;
    
    orPosResource->y = Y;
    
    orPosResource->width = width;
    
    orPosResource->height = height;
    
    orPosResource->iActivo = 1;
    
	orPosResource->iType = type;
    
	orPosResource->name = name;
	this->ResourceType(orPosResource, X, Y, name);
    
    return orPosResource;
}

void Resource::ResourceType(objectResource* piMRP, int X, int Y, std::string name){
    
	if (name == ("Botella"))
		piMRP->spriteResource = cocos2d::Sprite::create("BotellaTequila.png");
    
	if (name == ("Llave" ))
		piMRP->spriteResource = cocos2d::Sprite::create("Llave.png");
    
	if (name == ("PuertaEntrada"))
		piMRP->spriteResource = cocos2d::Sprite::create("puertac.png");
    
	if (name == ("PuertaSalida"))
		piMRP->spriteResource = cocos2d::Sprite::create("PuertaS.png");
    
	if (name == ("Picos"))
		piMRP->spriteResource = cocos2d::Sprite::create("picos.png");
    
	if (name == ("Personaje"))
		piMRP->spriteResource = cocos2d::Sprite::create("Personaje.png");
    
	if (name == ("Nube"))
		piMRP->spriteResource = cocos2d::Sprite::create("nube.png");
    
	if (name == ("Logo1"))
		piMRP->spriteResource = cocos2d::Sprite::create("logo1.png");
    
	if (name == ("Logo2"))
		piMRP->spriteResource = cocos2d::Sprite::create("logo2.png");
    
	if (name == ("Logo3"))
		piMRP->spriteResource = cocos2d::Sprite::create("logo3.png");
    
	if (name == ("Logo4"))
		piMRP->spriteResource = cocos2d::Sprite::create("logo4.png");
    
	piMRP->spriteResource->setAnchorPoint(Point(0, 0));
    
	piMRP->spriteResource->setPosition(Point(X, Y));
    
	addChild(piMRP->spriteResource);
    
}

void Resource::initArray ()
{
    this->piMapResourcesPoints = new objectResource [7] ();
}

int& Resource::getNRecursos ()
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

