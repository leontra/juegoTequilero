//
//  PauseLogo.h
//  JuegoTequilero
//
//  Created by Max on 12/18/14.
//
//

#ifndef __JuegoTequilero__PauseLogo__
#define __JuegoTequilero__PauseLogo__

#include <stdio.h>
#include "PauseObjectEntity.h"

class PauseLogo : public PauseObjectEntity
{
public:
    PauseLogo( );
    ~PauseLogo( );
    
    void InitializeObjects( );
    void getPauseObjects( cocos2d::Layer* layer, int& xOffset );
    void moveObjectBy( const int& iDelta );
    
private:
    void setLogoPosition( ObjectLogo* logo, const int& xOffset );
    
private:
    std::vector< ObjectLogo* > _apObjects;
    int _iLogoSize;
};

#endif /* defined(__JuegoTequilero__PauseLogo__) */
