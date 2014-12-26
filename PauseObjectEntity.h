//
//  PauseObjectEntity.h
//  JuegoTequilero
//
//  Created by Max on 12/19/14.
//
//

#ifndef JuegoTequilero_PauseObjectEntity_h
#define JuegoTequilero_PauseObjectEntity_h

#include <stdio.h>
#include <vector>
#include "ResourcesBuffer.h"

class PauseObjectEntity
{
public:
    PauseObjectEntity( ) : iWindowWidth( 0 ), iWindowHeight( 0 ), _iObjectWidth( 0 ), _iObjectHeight( 0 ), _bExistence( 0 ) { };
    
    virtual void InitializeObjects( ) = 0;
    virtual void getPauseObjects( cocos2d::Layer* layer, int& xOffset ) = 0;
    virtual void moveObjectBy( const int& iDelta ) = 0;
    
protected:
    cocos2d::Layer* _Layer;
    int iWindowWidth;
    int iWindowHeight;
    int _iObjectWidth;
    int _iObjectHeight;
    bool _bExistence;
    
};

#endif
