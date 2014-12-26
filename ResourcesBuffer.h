//
//  ResourcesBuffer.h
//  JuegoTequilero
//
//  Created by Max on 10/17/14.
//
//

#ifndef JuegoTequilero_ResourcesBuffer_h
#define JuegoTequilero_ResourcesBuffer_h

#include <iostream>
#include <vector>
#include <exception>

#include "ObjectEntity.h"
#include "RoomsWorld.h"
#include "ResourceObject.h"

/*
struct BadScenesInitializer: public std::exception
{
    std::string sReturn;
    
    BadScenesInitializer( const std::string& sText )
    {
        sReturn = sText;
    }
    virtual const char* what(  ) const throw(  )
    {
        return sReturn.c_str( );
    }
    
} typedef badSceneResourcesInitializer;
*/

class ResourcesBuffer
{
    
private:
    
    ResourcesBuffer( );
    
    ~ResourcesBuffer( );
    
    void addResourceMemoryDirection( const int& type, ObjectResource* oLevel );
    void removeResourceMemoryDirection( const int& type, const int& hash );
    void addKey( const int& type, ObjectResource* oLevel );
    
public:
    
    void setRoomBuffer( cocos2d::TMXTiledMap& tileMap, const int& roomIndex, RoomsWorld& roomsWorld );
    
    static ResourcesBuffer* GetInstance( );
    
    bool setResourceObtenidoAtHash( const int& hash, std::string _name, const int& type, const int& room );
    
    const int& getNResources( );
    
    void setNResources( const int& iSum );
    
    void resetToNewRoom( );
    
    void initResourcesArray( int totalResources );
    
    bool testResourceToDraw( const int& hash, const int& room );
    
    int getTotalRoomResources( const int& indexRoom );
    
    bool testLetters( );
    
    void setLettersTest( bool bTestLetters );
    
    ObjectResource& getRoomResourcesBuffer( const int& indexRoom, const int& index );
    
    int& getTotalKeysCollected( );
    int& getTotalToolsCollected( );
    
    bool testKeysCollected( );
    bool testToolsCollected( );
    
    void sumKeysCollectedBy( const int& sum, int keyIndex );
    void sumToolsCollectedBy( const int& sum, int toolIndex );
    
    int respawnLastKey( const int& _iRoomIndex );
    int respawnLastTool( const int& _iRoomIndex );
    
    void sumLogos( );
    
    bool testKeyForDoor( const int& idKey );
    bool testToolForMate( const int& idTool );
    
    int getTotalBottles( );
    int getTotalKeys( );
    int getTotalTools( );
    int getTotalLogos( );
    int getTotalLetters( );
    
    ObjectBottle* testBottleCollected( const int& index );
    ObjectKey* testKeyCollected( const int& index );
    ObjectTool* testToolCollected( const int& index );
    ObjectLogo* testLogoCollected( const int& index );
    ObjectLetter* testLetterCollected( const int& index );
    
protected:
    
    int iKey;
    int iLetter;
    int iLogo;
    int iBottle;
    int iTool;
    
private:
    
    static int _InstanceFlag;
    static ResourcesBuffer* singResourcesBuffer;
    
    std::vector< std::vector< ObjectResource* > > _apBuffer;
    
    std::vector< ObjectKey* > _apKeys;
    std::vector< ObjectBottle* > _apBottles;
    std::vector< ObjectTool* > _apTools;
    std::vector< ObjectLogo* > _apLogos;
    std::vector< ObjectLetter* > _apLetters;
    
    int keysCollectedIndex[ 2 ];
    int toolsCollectedIndex[ 2 ];
    
    int* _aiNResourcesRoom;
    
    int _iNMaxResources;
    int _iNTotalKeysRoom;
    
    int _iNTotalLogos;
    
    int _iNTotalKeys;
    int _iNTotalTools;
    
    bool _bfInit;
    
    int _iMaxTotalKeys;
    int _iMaxTotalTools;
    
    bool _bTestLetters;
    
};

#endif
