//
//  MapWorld.h
//  JuegoTequilero
//
//  Created by Max on 7/11/14.
//
//

#ifndef __JuegoTequilero__MapWorld__
#define __JuegoTequilero__MapWorld__

#include <iostream>

#include "cocos2d.h"
#include "Vector.h"

class MapWorld
{
    
private:
    
    cocos2d::TMXTiledMap* _tileMap;
    
    float _fGravedad;
    
    void setMapGravity (float& fGravedad);
    
    std::string getEscena (int& iEscena);
    
public:
    
    MapWorld ();
    
    ~MapWorld ();
    
    void destroyMap ();
    
    cocos2d::TMXTiledMap* mapTileXML (float fGravedad, int& iMapIndex);
    
    float& getFGravedad ();
    
};

#endif /* defined(__JuegoTequilero__MapWorld__) */
