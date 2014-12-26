//
//  ViewPause.h
//  JuegoTequilero
//
//  Created by Max on 12/18/14.
//
//

#ifndef __JuegoTequilero__ViewPause__
#define __JuegoTequilero__ViewPause__

#include <stdio.h>
#include "cocos2d.h"
#include "PauseBottles.h"
#include "PauseKeys.h"
#include "PauseTools.h"
#include "PauseLogo.h"
#include "PauseLetters.h"

class ViewPause: public cocos2d::Layer
{
public:
    
    ViewPause( );
    virtual ~ViewPause( );
    
    void moveTopScroll( const int& iDelta );
    void moveMainScroll( const int& iDelta );
    void clean( );
    
    bool init( );
    
    CREATE_FUNC( ViewPause );
    
private:
    
    void InitDisplay( );
    void moveObjectsBy( const int& iDelta );
    
private:
    PauseBottles* _oPauseBottles;
    PauseKeys* _oPauseKeys;
    PauseTools* _oPauseTools;
    PauseLogo* _oPauseLogo;
    PauseLetters* _oPauseLetters;
    
    int _iLeftX;
    int _iRightX;
    
    int _iStartLeftX;
    int _iStartRightX;
};

#endif /* defined(__JuegoTequilero__ViewPause__) */
