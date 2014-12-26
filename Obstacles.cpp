//
//  Obstacles.cpp
//  JuegoTequilero
//
//  Created by Max on 11/1/14.
//
//

#include "Obstacles.h"

Obstacles::Obstacles( ) : _iSize( 0 )
{
    _oEffect = new Sounds();
}

void Obstacles::initObstacles( cocos2d::TMXTiledMap& _tileMap, cocos2d::Layer* layer )
{
    //Obtener todos los grupos de cada mapa
    cocos2d::Vector< cocos2d::TMXObjectGroup* > tileGroups = _tileMap.getObjectGroups( );
    
    //Iterar sobre cada grupo
    for( cocos2d::TMXObjectGroup* objectGroup : tileGroups )
    {
        //Terminar si el objeto no es un objeto
        if( objectGroup->getGroupName( ) != "Obstaculo" )
            continue;
        
        //Obtener objeto
        cocos2d::ValueVector objects = objectGroup->getObjects( );
        
        //Revisar por cada propiedad del objeto
        for( cocos2d::Value& object : objects )
        {
            cocos2d::ValueMap properties = object.asValueMap( );
            
            std::string name = properties.at( "name" ).asString( );
            std::string nameExtension = "png";
            float x = properties.at( "x" ).asFloat( );
            float y = properties.at( "y" ).asFloat( );
            float width = properties.at( "width" ).asFloat( );
            float height = properties.at( "height" ).asFloat( );
            
            //Evitar errores
            if( !object.isNull( ) )
            {
                ++_iSize;
                MainObstacle mainObstacle( x, y, width ,height );
                mainObstacle.setSpriteName( name, nameExtension );
                mainObstacle.initSprite( );
                layer->addChild( mainObstacle.getSprite( ) );
                _apObstacles.push_back( mainObstacle );
                
            }//if
            
        }//For
        
    }//For
}

bool Obstacles::testObstaclesCollisions( float playerXMax, float playerYMax, float playerXMin, float playerYMin )
{
    std::vector< MainObstacle >::iterator it;
    for( it = _apObstacles.begin( ); it != _apObstacles.end( ); ++it )
    {
        if( ( it->getXMax( ) <= playerXMin && it->getYMax( ) <= playerYMin ) && ( it->getXMin( ) >= playerXMax && it->getYMin( ) >= playerYMax ) )
        {
            _oEffect->GetEffect("picos", ".wav");
            return 1;
        }
    }
    
    return 0;
}

void Obstacles::resetObstacles( )
{
    std::vector< MainObstacle >::iterator it;
    for( it = _apObstacles.begin( ); it != _apObstacles.end( ); ++it )
        it->deleteSprite( );
    
    _apObstacles.clear( );
    _iSize = 0;
}

Obstacles::~Obstacles( )
{
    delete _oEffect;
    this->resetObstacles( );
}
