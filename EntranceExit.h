//
//  EntranceExit.h
//  JuegoTequilero
//
//  Created by Max on 10/25/14.
//
//

#ifndef __JuegoTequilero__EntranceExit__
#define __JuegoTequilero__EntranceExit__

#include <stdio.h>

class EntranceExit
{
public:
    EntranceExit( );
    EntranceExit( const float& x, const float& y );
    
    void setTypeConexion( const int& type, const int& idConexion );
    void setSize( const float& width, const float& height );
    
    float& getX( );
    float& getY( );
    
    float& getWidth( );
    float& getHeight( );
    
    int& getType( );
    int& getIdConexion( );
    
    ~EntranceExit( );
    
private:
    
    
private:
    
    float _fX;
    float _fY;
    
    int _iType;
    int _idConexion;
    
    float _fWidth;
    float _fHeight;
    
};

#endif /* defined(__JuegoTequilero__EntranceExit__) */
