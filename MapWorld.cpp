//
//  MapWorld.cpp
//  JuegoTequilero
//
//  Created by Max on 7/11/14.
//
//

#include "MapWorld.h"


#define COCOS2D_DEBUG 1

USING_NS_CC;

MapWorld::MapWorld (): _tileMap (0),
                                    _fGravedad (0)
{ }

MapWorld::~MapWorld ()
{
    _tileMap = 0;
    
    //this->deleteArray ();
}

TMXTiledMap* MapWorld::mapTileXML (float fGravedad, int& iMapIndex)
{
    //std::string sPrefixMapa = "/Escenas/";
    
    //Prefijo del nombre de los mapas
    std::string sNameMapa = this->getEscena (iMapIndex);
    
    //Sufijo del mapa a cargar
    std::string sSuffixMapa = ".tmx";
    
    std::string sTextMap = sNameMapa + sSuffixMapa;
    
    //Inicilizar el mapa
    this->_tileMap = TMXTiledMap::create (sTextMap);
    
    //Inicializar la gravedad del mundo
    this->setMapGravity (fGravedad);
    
    return _tileMap;
}

std::string MapWorld::getEscena (int& iEscena)
{
    char cEscena [100] = {0};
    
    sprintf (cEscena, "escena_%04d", iEscena);
    
    std::string sEscena = cEscena;
    
    return sEscena;
}


void MapWorld::setMapGravity (float& fGravedad)
{
    _fGravedad = fGravedad;
}

float& MapWorld::getFGravedad ()
{
    return _fGravedad;
}


void MapWorld::destroyMap ()
{
    _tileMap = 0;
}

