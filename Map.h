//
//  Map.h
//  DemoInduccion
//
//  Created by Administrador on 7/4/14.
//
//

#ifndef __DemoInduccion__Map__
#define __DemoInduccion__Map__

#include <iostream>
#include "cocos2d.h"
#include "Vector.h"

class MapWorld
{
    
private:
    
    cocos2d::TMXTiledMap* _tileMap;
    
public:
    
    MapWorld ();
    
    ~MapWorld ();
    
    cocos2d::TMXTiledMap* mapTileXML ();
    
};

#endif /* defined(__DemoInduccion__Map__) */
