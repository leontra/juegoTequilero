//
//  MateEntity.h
//  JuegoTequilero
//
//  Created by Max on 11/7/14.
//
//

#ifndef __JuegoTequilero__MateEntity__
#define __JuegoTequilero__MateEntity__

#include "ObjectEntity.h"

class MateEntity: public ObjectEntity
{
    
public:
    MateEntity( );
    MateEntity( const float& _x, const float& _y, const float& _width, const float& _height );
    
    void setMateProperties( int _idTool, int _idConexion );
    void setMateTexts( std::string _sPopText, std::string _sPopRewardText = "" );
    int getCenterX( );
    int getCenterY( );
    
    int& getToolId( );
    std::string getText( );
    std::string getRewardText( );
    
    float getRadiusDetection( );
    
    ~MateEntity( );
 
protected:
    
    float fRadiusDetection;
    
    int idTool;
    std::string sPopText;
    std::string sPopRewardText;
    
};


#endif /* defined(__JuegoTequilero__MateEntity__) */
