//
//  ObjectEntity.h
//  JuegoTequilero
//
//  Created by Max on 10/18/14.
//
//

#ifndef JuegoTequilero_ObjectEntity_h
#define JuegoTequilero_ObjectEntity_h

#include <iostream>
#include "cocos2d.h"

class ObjectEntity
{
    
public:
    
    void initSprite( );
    void initSpriteWithNoScale( );
    void deleteSprite( );
    
    void setObject( const int& _hash, const int& _type, const int& _indexRoom );
    void setSpriteName( std::string& _name, std::string& _extension );
    void setStateUpgrade( const int& _state, const float& _upgrade );
    void setConexion( const int& _conexion );
    
    float getXMax( );
    float getYMax( );
    float getXMin( );
    float getYMin( );
    
    int getCenterX( );
    int getCenterY( );
    
    int& getRoomIndex( );
    int& getIdConexion( );
    
    int& getState( );
    int& getHash( );
    int& getType( );
    
    void setState( const int& _state );
    
    float& getUpgrade( );
    
    void unPaintSprite( );
    
    void resetResourceForRoom( );
    
    cocos2d::Sprite* getSprite( );
    cocos2d::Sprite* getSpriteForPause( float _x, float _y );
    
protected:
    
    ObjectEntity( );
    ObjectEntity( const float& _x, const float& _y, const float& _width, const float& _height );
    
    ~ObjectEntity( );
    
protected:
    
    float x;
    float y;
    float width;
    float height;
    
    int hash;
    int type;
    int indexRoom;
    int idConexion;
    
    int state;
    float upgrade;
    
    std::string name;
    std::string spriteExtension;
    
    cocos2d::Sprite* spriteResource; 
    
};

#endif





