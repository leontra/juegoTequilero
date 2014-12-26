//
//  PauseLetters.h
//  JuegoTequilero
//
//  Created by Max on 12/18/14.
//
//

#ifndef __JuegoTequilero__PauseLetters__
#define __JuegoTequilero__PauseLetters__

#include <stdio.h>
#include "PauseObjectEntity.h"
#include <vector>

class PauseLetters : public PauseObjectEntity
{
public:
    PauseLetters( );
    ~PauseLetters( );
    
    void InitializeObjects( );
    void InitializeLetters( );
    void getPauseObjects( cocos2d::Layer* layer, int& xOffset );
    void setPauseWordLine( const int& xOffset );
    void moveObjectBy( const int& iDelta );
    
    int getTotalLettersCollected( );
    
private:
    
    void setLetterSprite( const int& x, const int& y, const int& idLetter );
    bool testCorrectLetter( ObjectLetter* letter );
    
private:
    std::vector< ObjectLetter* > _apObjects;
    std::vector< cocos2d::Sprite* > _apSprites;
    std::vector< std::pair< int, bool > > _aLettersToCheck;
    
    int iLinesX;
    int _iNTotalCorrectLetters;
    bool _bTestLetters;
};

#endif /* defined(__JuegoTequilero__PauseLetters__) */
