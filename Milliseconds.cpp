//
//  Milliseconds.cpp
//  JuegoTequilero
//
//  Created by Max on 7/11/14.
//
//

#include "Milliseconds.h"


Milliseconds::Milliseconds (): _fMillisStart (0),
                                 _iMillisCount (0),
                                 _fMillisCount (0),
                                 _bSeconds (0)
{
}

Milliseconds::~Milliseconds ()
{
}

float Milliseconds::fGetMilliCount ( )
{
    timeval time;
    
    gettimeofday( &time,  0 );
    
    long double millisecs = (time.tv_sec * 1000) + (time.tv_usec  /  1000);
    
    return (float) millisecs;
    
} // float getMilliCount

int Milliseconds::iGetMilliCount ()
{
    timeval curTime;
    gettimeofday (&curTime, NULL);
    unsigned int millis = (curTime.tv_sec * 1000) + (curTime.tv_usec / 1000);

    return millis;
}


bool Milliseconds::getSecCount ()
{
    if (!_bSeconds)
    {
        _fMillisStart = this->fGetMilliCount ();
        _bSeconds = 1;
    }
    
    if ((fGetMilliCount () - _fMillisStart) >= 1000)
    {
        _bSeconds = 0;
        return 1;
    }
    
    return 0;
}


float Milliseconds::getCount ()
{
    if (!_bSeconds)
    {
        _fMillisStart = this->fGetMilliCount ();
        _bSeconds = 1;
    }
    
    if ((this->fGetMilliCount () - _fMillisStart) >= 1000)
        _bSeconds = 0;
    
    return (this->fGetMilliCount () - _fMillisStart);
}

float& Milliseconds::getSecsCounter ()
{
    if (!_bSeconds)
    {
        _fMillisStart = this->fGetMilliCount ();
        _bSeconds = 1;
    }
    
    if ((this->fGetMilliCount () - _fMillisStart) >= 1000)
    {
        ++_iMillisCount;
        _bSeconds = 0;
    }
    
    return (_iMillisCount);
}

void Milliseconds::startCounter ()
{
    _fMillisCount = this->iGetMilliCount ();
}

int Milliseconds::getMillisInterval (int iTimeInterval)
{
    int timeInterval = this->iGetMilliCount ();
    
    timeInterval -= _fMillisCount;
    
    if (timeInterval >= iTimeInterval && _fMillisCount)
    {
        _fMillisCount = 0;
        return 1;
    }
    _fMillisCount = 0;
    return 0;
}


int Milliseconds::getEveryMillis ()
{
    return this->iGetMilliCount ();
}


