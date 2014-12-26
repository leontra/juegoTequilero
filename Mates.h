//
//  Mates.h
//  JuegoTequilero
//
//  Created by Max on 11/7/14.
//
//

#ifndef __JuegoTequilero__Mates__
#define __JuegoTequilero__Mates__

#include "MatesBuffer.h"
#include "math.h"
#include "ResourcesBuffer.h"
#include "Sounds.h"

class Mates
{
public:
    Mates( );
    
    void initMates( const int& indexRoom, cocos2d::Layer* layer );
    
    int testMatesCollisions( const int& x, const int& y, cocos2d::Layer* layer );
    
    int testRemoveText( const int& x, const int& y, cocos2d::Layer* layer );
    
    void resetMates( );
    
    void setText( cocos2d::Layer* layer, std::string text );
    
    ~Mates( );
    
private:
    
    int _iSize;
    
    bool _bText;
    
    int _iActualMate;
    
    std::vector< MateEntity* > _apMates;
    
    std::vector< MateEntity* >::iterator _it;
    
    MatesBuffer* _oMatesBuffer;
    ResourcesBuffer* _oResourcesBuffer;
    Sounds* _oEffect;
    
};

#endif /* defined(__JuegoTequilero__Mates__) */
