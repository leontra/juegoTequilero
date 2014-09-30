//
//  BarraMision.cpp
//  JuegoTequilero
//
//  Created by Max on 7/19/14.
//
//

#include "BarraMision.h"

USING_NS_CC;

BarraMision::BarraMision ():
                               _posX (0),
                               _posY (0),
                               _iBarraFill (0),
                               _iBarraWidth (0),
                               _iBarraHeight (0),
                               _barraSpriteFrame (0),
                               _iBarraPorcentaje (0)
{
    
}

BarraMision::~BarraMision ()
{
}

bool BarraMision::init (cocos2d::TMXTiledMap& _tileMap)
{
    if (!Layer::create())
        return 0;
    
    this->initBarraMisionObject (_tileMap);
    
    this->initBarraFill ();
    
    this->drawRectForBarra ();

    sprite = cocos2d::Sprite::createWithSpriteFrame( _barraSpriteFrame );
    
    sprite->setPosition(_posX, _posY);
    
    sprite->setAnchorPoint (Point (0, 0));
    
    this->addChild (sprite, 0, 0);
    
    return 1;
}

void BarraMision::initBarraFill( )
{
    _iBarraPorcentaje = 10;
    
    _iBarraFill = ( _iBarraPorcentaje * _iBarraWidth ) / 100;
}

void BarraMision::initBarraMisionObject( cocos2d::TMXTiledMap& _tileMap )
{
    //Obtener los diferentes objetos contenidos en el xml
    auto tileGroups = _tileMap.getObjectGroups( );
    
    //Obtener posiciones del player
    for( auto& objectGroup : tileGroups )
    {
        //Terminar si el objeto no es un recurso
        if( objectGroup->getGroupName( ) != "BarraMision" )
            continue;
        
        this->initVariablesBarra( objectGroup );
        
    }//For
}

void BarraMision::initVariablesBarra( cocos2d::TMXObjectGroup* group )
{
    //Obtener objeto
    auto objects = group->getObjects( );
    
    //Revisar por cada propiedad del objeto
    for (auto& object : objects)
    {
        auto properties = object.asValueMap( );
        
        _posX = properties.at( "x" ).asInt( );
        
        _posY = properties.at( "y" ).asInt( );
        
        _iBarraWidth = properties.at( "width" ).asInt();
        
        _iBarraHeight = properties.at( "height" ).asInt();
    }
}

void BarraMision::upgradeBarraWith( int& iUpgrade )
{
    _iBarraPorcentaje += iUpgrade;
    
    if( _iBarraPorcentaje > 100 ) _iBarraPorcentaje = 100;
    
    _iBarraFill = ( _iBarraPorcentaje * _iBarraWidth ) / 100;
    
    this->drawRectForBarra( );
    this->updateBarra( );
}

void BarraMision::drawRectForBarra( )
{
    Rect rectBarra = Rect( _posX, _posY, _iBarraFill, _iBarraHeight );
    
    _barraSpriteFrame = cocos2d::SpriteFrame::create( "barraFill.png", rectBarra );
}

void BarraMision::reverseBarraWith( int& iReverse )
{
    _iBarraFill -= ( iReverse * _iBarraWidth ) / 100;
    this->drawRectForBarra( );
    this->updateBarra( );
}

void BarraMision::updateBarra( )
{
    std::cout << "Update Barra:     " << _iBarraFill << std::endl;
    sprite->setSpriteFrame( _barraSpriteFrame );
}

int& BarraMision::getBarraFill( )
{
    return _iBarraFill;
}

void BarraMision::deleteBarra( )
{
    _barraSpriteFrame = 0;
    this->removeChild( sprite, 1 );
}

