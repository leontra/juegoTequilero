//
//  BoxCollision.cpp
//  gameTest00
//
//  Created by Max on 4/16/14.
//
//

#include "BoxCollision.h"

#include <CCGeometry.h>

#define COCOS2D_DEBUG 1

USING_NS_CC;


void BoxCollision::checkCollision ( cocos2d::Sprite * platform, int &x, int &y, int &sumX, int &sumY, int &_pWidth, int &_pHeight, int &g, bool &horizontalLeft, bool &horizontalRight, bool &verticalPlus, bool &verticalMinus )
{
    
    
    float platformPos[] = { platform -> getPosition().x, platform -> getPosition().y };
    
    float platformSize[] = { platform -> getContentSize().width, platform -> getContentSize().height };
    
    int playerSize[] = { _pWidth, _pHeight };
    
    
    //CCLOG( "%f el otro es %f", y, platformPos[1] + platformSize[1] );
    
    
    horizontalRight = false;
    
    horizontalLeft = false;
    
    verticalPlus = false;
    
    verticalMinus = false;
    
    /*
    if ( x + ( playerSize[0] / 2 ) >= platformPos[0] && x - ( playerSize[0] / 2 ) <= platformPos[0] + platformSize[0] )
    {
        
        if( y - ( playerSize[1] / 2 ) + sumY <= platformPos[1] + platformSize[1] && y - ( playerSize[1] / 2 ) >= platformPos[1] )
        {
            x = 120;
            horizontal = true;
            
            
            printf( "\n llego 01 %f", sumY );
            
        } 
        
        
        if( y - ( playerSize[1] / 2 ) + ( sumY / 10 ) <= platformPos[1] + platformSize[1] && y - ( playerSize[1] / 2 ) > platformPos[1]  + ( platformSize[1] / 2 ) )
        {
            
            verticalMinus = true;
            
            horizontal = false;
            
            printf( "\n llego " );
            
        }
        else
        
        if( y + ( playerSize[1] / 2 ) + ( sumY / 10 ) >= platformPos[1] && y - ( playerSize[1] / 2 ) <= platformPos[1] + ( platformSize[1] / 2 ) )
        {
            
            verticalPlus = true;
            
            horizontal = false;
            
            //verticalMinus = true;
            
            printf( "\n llego 02 = \t %f \t y \t %f", y + ( playerSize[1] / 2 ) + ( sumY / 10 ) , platformPos[1] );
            
        }
        
    }
    */
    //if ( y - playerSize[1] + sumY > )
    
    int fTempY = y - _pHeight - g + (sumY / 5);
    if ( fTempY <=  platformPos[1] + platformSize[1] && x - _pWidth - sumX > platformPos[0] && x + sumX + _pWidth < platformPos[0] + platformSize[0]  )
    {
        //printf ( "aqui tambien\n" );
        verticalMinus = 1;
    }
    
}