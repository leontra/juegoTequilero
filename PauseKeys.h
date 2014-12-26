//
//  PauseKeys.h
//  JuegoTequilero
//
//  Created by Max on 12/18/14.
//
//

#ifndef __JuegoTequilero__PauseKeys__
#define __JuegoTequilero__PauseKeys__

#include "PauseObjectEntity.h"

class PauseKeys : public PauseObjectEntity
{
public:
    PauseKeys( );
    ~PauseKeys( );
    
    void InitializeObjects( );
    void getPauseObjects( cocos2d::Layer* layer, int& xOffset );
    void moveObjectBy( const int& iDelta );
    
private:
    std::vector< ObjectKey* > _apObjects;
};

#endif /* defined(__JuegoTequilero__PauseKeys__) */
