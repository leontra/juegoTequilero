//
//  Milliseconds.cpp
//  gamePrototype
//
//  Created by Max on 4/20/14.
//
//

#include "Milliseconds.h"

#define COCOS2D_DEBUG 1

USING_NS_CC;



float Milliseconds::fGetMilliCount ( )
{
    
    timeval time;
    
    gettimeofday( &time,  NULL );
    
    unsigned long millisecs = ( time.tv_sec * 1000 ) + ( time.tv_usec  /  1000 );
    
    return ( float ) millisecs;
    
    
} // float getMilliCount


bool Milliseconds::getSecCount ()
{
    
    if( ! bSeconds )
    {
        
        fMillisStart = Milliseconds::fGetMilliCount ();
        
        bSeconds = true;
        
    }
    
    if( ( fGetMilliCount () - fMillisStart ) >= 1000 )
    {
        
        bSeconds = false;
        
        fMillisCount ++;
        
        return true;
        
    }
    
    
    return false;
    
}

float Milliseconds::getCount ()
{
    
    if( ! bSeconds )
    {
        
        fMillisStart = Milliseconds::fGetMilliCount ();
        
        bSeconds = true;
        
    }
    
    if( ( Milliseconds::fGetMilliCount () - fMillisStart ) >= 1000 )
        
        bSeconds = false;
    
    
    
    return ( Milliseconds::fGetMilliCount () - fMillisStart );
    
}