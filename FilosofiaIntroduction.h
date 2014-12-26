//
//  FilosofiaIntroduction.h
//  JuegoTequilero
//
//  Created by Max on 12/20/14.
//
//

#ifndef __JuegoTequilero__FilosofiaIntroduction__
#define __JuegoTequilero__FilosofiaIntroduction__

#include <stdio.h>
#include "cocos2d.h"

class FilosofiaIntroduction
{
public:
    FilosofiaIntroduction( );
    ~FilosofiaIntroduction( );
    
    void InitializeFilosofia( cocos2d::Layer* layer );
    void testFilosofiaText( const float& fPlayerPosition );
    
    void setFilosofiaCompleteText( );
    bool& testIfItIsTheRoom( );
    
private:
    void createLabel( const std::string& sText, const int& xPosition, const int& yPosition );
    
private:
    
    cocos2d::Layer* _Layer;
    
    std::string _sFirstText;
    std::string _sSecondText;
    std::string _sThirdText;
    
    int _iWindowWidth;
    
    int _iFirstTextX;
    int _iSecondTextX;
    int _iThirdTextX;
    
    bool _bFirst;
    bool _bSecond;
    bool _bThird;
    
    bool _bRoomText;
};

#endif /* defined(__JuegoTequilero__FilosofiaIntroduction__) */
