//
//  Map.cpp
//  DemoInduccion
//
//  Created by Administrador on 7/4/14.
//
//

#include "Map.h"

#define COCOS2D_DEBUG 1

USING_NS_CC;

MapWorld::MapWorld (): _tileMap (0)
{
    
}

MapWorld::~MapWorld ()
{
    _tileMap = 0;
    
    //this->deleteArray ();
}

TMXTiledMap* MapWorld::mapTileXML ()
{
    this->_tileMap = TMXTiledMap::create("map02.tmx");
    
    return _tileMap;
}


