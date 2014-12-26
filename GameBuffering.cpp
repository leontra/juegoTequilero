//
//  GameBuffering.cpp
//  JuegoTequilero
//
//  Created by Max on 11/4/14.
//
//

#include "GameBuffering.h"

GameBuffering::GameBuffering( ) { }

void GameBuffering::initGameBuffers( )
{
    DoorsBuffer* oDoorsBuffer = DoorsBuffer::GetInstance( );
    ResourcesBuffer* oResourcesBuffer = ResourcesBuffer::GetInstance( );
    MatesBuffer* oMatesBuffer = MatesBuffer::GetInstance( );
    
    RoomsWorld oRoomsWorld;
    
    int iNRooms = oRoomsWorld.iNRooms;
    
    oResourcesBuffer->initResourcesArray( iNRooms );
    
    //Iterar sobre cada cuarto
    for( int iRoom = 0; iRoom < iNRooms; ++iRoom )
    {
        char cEscena [100] = {0};
        
        int iRoomIndex = iRoom;
        
        sprintf ( cEscena, "escena_%04d", iRoomIndex );
        
        std::string sEscena = cEscena;
        
        //Prefijo del nombre de los mapas
        std::string sNameMapa = sEscena;
        
        //Sufijo del mapa a cargar
        std::string sSuffixMapa = ".tmx";
        
        std::string sTextMap = sNameMapa + sSuffixMapa;
        
        //Inicilizar el mapa
        cocos2d::TMXTiledMap* tileMap = cocos2d::TMXTiledMap::create( sTextMap );
        
        oDoorsBuffer->setRoomBuffer( *tileMap, iRoom );
        
        oResourcesBuffer->setRoomBuffer( *tileMap,  iRoom,  oRoomsWorld );
        
        oMatesBuffer->setRoomBuffer( *tileMap,  iRoom );
    }
    oDoorsBuffer = nullptr;
    oResourcesBuffer = nullptr;
    oMatesBuffer = nullptr;
}

GameBuffering::~GameBuffering( )
{ }

