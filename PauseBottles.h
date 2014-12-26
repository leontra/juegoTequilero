//
//  PauseBottles.h
//  JuegoTequilero
//
//  Created by Max on 12/18/14.
//
//

#ifndef __JuegoTequilero__PauseBottles__
#define __JuegoTequilero__PauseBottles__

#include <stdio.h>
#include <vector>
#include "ResourcesBuffer.h"

class PauseBottles
{
    
public:
    
    PauseBottles( );
    ~PauseBottles( );
    
    void InitializeBottles( );
    
    void getPauseBottles( cocos2d::Layer* layer );
    
    void moveBottlesBy( const int& iDelta );
    
    bool& testIfItIsScrollable( );
    
private:
    
    cocos2d::Layer* _Layer;
    std::vector< ObjectBottle* > _apBottles;
    int iWindowWidth;
    int iWindowHeight;
    int _iRightX;
    int _iLeftX;
    int _iBottleWidth;
    bool _bExistence;
    bool _bScroll;
};

#endif /* defined(__JuegoTequilero__PauseBottles__) */
