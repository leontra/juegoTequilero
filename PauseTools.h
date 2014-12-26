//
//  PauseTools.h
//  JuegoTequilero
//
//  Created by Max on 12/18/14.
//
//

#ifndef __JuegoTequilero__PauseTools__
#define __JuegoTequilero__PauseTools__

#include "PauseObjectEntity.h"

class PauseTools : public PauseObjectEntity
{
public:
    PauseTools( );
    ~PauseTools( );
    
    void InitializeObjects( );
    void getPauseObjects( cocos2d::Layer* layer, int& xOffset );
    void moveObjectBy( const int& iDelta );
    
private:
    std::vector< ObjectTool* > _apObjects;
    
    cocos2d::Sprite* spriteResource;
    bool _bBadge;
};

#endif /* defined(__JuegoTequilero__PauseTools__) */
