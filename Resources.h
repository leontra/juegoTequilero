//
//  Resources.h
//  JuegoTequilero
//
//  Created by Max on 7/11/14.
//
//

#ifndef __JuegoTequilero__Resources__
#define __JuegoTequilero__Resources__

#include <iostream>

#include "ResourceObject.h"

#include "cocos2d.h"

#include "ResourcesBuffer.h"
#include "Sounds.h"


class Resource: public cocos2d::Layer
{
    
public:
    
    Resource( );
    
    ~Resource( );
    
    int& getNRecursos( );
    
    void initResourcesRoom( const int& iRoomIndex );
    
    bool init( );
    
    int testResourcesCollisions( float playerXMax, float playerYMax, float playerXMin, float playerYMin );
    
    void resetArrays( );
    
    void resetResources( );
    
private:
    
    void initArray( );
    
    void  setResourcesToArray( const int& iRoomIndex );
    
    void ResourceType( ObjectResource* piMRP, int X, int Y, std::string name );
    
private:
    
    ResourcesBuffer* _osResourceBuffer;
    
    std::vector< ObjectKey* > _apKeys;
    std::vector< ObjectBottle* > _apBottles;
    std::vector< ObjectTool* > _apTools;
    std::vector< ObjectLogo* > _apLogos;
    std::vector< ObjectLetter* > _apLetters;
    
    int _iNRoomResources;
    int _iRoomIndex;
    
    int _iLastLetterCollected;
    bool _bLetterCollected;
    
    int* _aiResourcesCollected;
    
    Sounds* _oEffect;
    
};


#endif /* defined(__JuegoTequilero__Resources__) */
