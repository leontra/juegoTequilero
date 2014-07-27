//
//  ViewGame.cpp
//  JuegoTequilero
//
//  Created by Max on 7/11/14.
//
//

#include "ViewGame.h"



#define COCOS2D_DEBUG 1

USING_NS_CC;

ViewGame::ViewGame(): _piResourcePoints (0),
                        _bfStart (0),
                        _iMapIndex (0),
                        _orPuertasPoints (0),
                        _iPx (0),
                        _iPy (0),
                        _iPWidth (0),
                        _iPHeight (0),
                        _bChangeScene (0),
                        _bInicio (0),
                        _iAvanzoRetrocedio (0),
                        _sPuerta ("Entrada"),
                        _bActionTouch (0),
                        _iMapWidth (0)
{
    _oMap = new MapWorld ();
    _oResource = new Resource ();
    _oPlayer = new Player ();
    _oPuertas = new Puertas ();
    _oDrawRecursos = new DrawRecursos ();
    _oBarraMision = new BarraMision ();
    
    _oAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance ();
    
    _bInicio = new int (1);
}

ViewGame::~ViewGame()
{
    this->roomDeconstructor ();
    delete _oMap;
    delete _oResource;
    delete _oPuertas;
    delete _oPlayer;
    delete _oDrawRecursos;
    delete _bInicio;
}

bool ViewGame::init ()
{
    if (!Layer::init())
        return 0;
   
    //Escalar el tile map
    //_tileMap->setScale(1);
    
    _oAudioEngine->preloadEffect ("zeldaShop.mp3");
    
    _iMapIndex = 0;
    
    this->roomConstructor ();
    
    this->schedule (schedule_selector (ViewGame::update));
    
    return 1;
}

void ViewGame::roomConstructor ()
{
    if (!_iMapIndex)
        _oAudioEngine->playBackgroundMusic ("zeldaShop.mp3");
    if (_iMapIndex == 1)
        _oAudioEngine->playBackgroundMusic ("astralObservatory.mp3");
    if (_iMapIndex == 2)
        _oAudioEngine->playBackgroundMusic ("oathToOrder.mp3");
    
    //Inicializar la gravedad para el mundo
    float fGravedad = 9.0;
    
    //Asignar xml y darle un valor a la gravedad del mundo
    this->_tileMap = _oMap->mapTileXML (fGravedad, _iMapIndex);
    
    //Inicializar al player
    _oPlayer->init (*_tileMap, _oMap->getFGravedad(), _sPuerta, _iMapIndex);
    
    //Obtener los puntos de colision para los recursos
    _piResourcePoints = _oResource->initResources ( *_tileMap );
    
    //Obtener los puntos de las puertas en el mapa
    _orPuertasPoints = _oPuertas->initResources (*_tileMap);
    
    //Inicializar las colisiones para las puertas
    _oPuertasBoxCollision = new PuertasBoxCollision (_iMapIndex, _oPuertas->getINPuertas(), _bInicio);
    
    _oBarraMision->init ();
    
    //Inicilizar el layer de los recursos
    _oResource->init ();
    
    //Obtener el numero de recursos por mapa para hacer la iteracion
    int iNRecursos = _oResource->getNRecursos ();
    
    //Pasar el numero de recursos por mapa para las colisiones y pintarlos
    _oDrawRecursos->setNRecursos (iNRecursos);
    
    addChild (_tileMap, 0, 0);
    
    addChild (_oPlayer, 0, 0);
    
    addChild (_oResource, 0, 0);
    
    addChild (_oBarraMision, 0, 0);
}

//Resetear valores para volverlos a construir
void ViewGame::roomDeconstructor ()
{
    _oMap->destroyMap ();
    
    _oPlayer->destroyPlayer ();
    
    _oResource->deleteArray ();
    
    _piResourcePoints = 0;
    
    _oPuertasBoxCollision->resetValues();
    
    _orPuertasPoints = 0;
    
    delete _oPuertasBoxCollision;
    
    removeAllChildren ();
}

void ViewGame::update (float dt)
{
    //Pausar juego
    //this->getActionManager()->pauseAllRunningActions();
    
    //Revisar si se cambio de escena para construirla
    if (_bChangeScene)
        this->createScene ();
    else
        this->updatePuertasRecursos ();
    
}

void ViewGame::createScene ()
{
    _bChangeScene = 0;
    *_bInicio = 1;
    this->roomConstructor ();
}

void ViewGame::updatePuertasRecursos ()
{
    _oPlayer->getAllValues (_iPx, _iPy, _iPWidth, _iPHeight, _bActionTouch, _iMapWidth);
    this->checkForCollisionWithRecursosAndPaintThem ();
    this->checkForCollisionWithPuertas ();
}

void ViewGame::checkForCollisionWithPuertas ()
{
    //Entero temporal, para saber si se movio de escena
    int iTempMapIndex = -1;
    
    int iPrevMapIndex = _iMapIndex;
    
    /*
    //Hacer las colisiones para el principio, hasta que el jugador salga de la puerta
    if (*_bInicio)
        _oPuertasBoxCollision->doStartCollisionsWith (_iPx, _iPy, _iPWidth, _iPHeight, _orPuertasPoints, _sPuerta);
    
    else
        //Obtener el numero de mapa que sigue
        iTempMapIndex = _oPuertasBoxCollision->doCollisionsWith (_iPx, _iPy, _iPWidth, _iPHeight, _orPuertasPoints, _iMapIndex, _bActionTouch);
    */
    //Revisar que haya alcanzado una puerta
    
    //Obtener el numero de mapa que sigue
    iTempMapIndex = _oPuertasBoxCollision->doCollisionWithSidesToExit (_iPx, _iPy, _iPWidth, _iPHeight, _orPuertasPoints, _iMapIndex, _sPuerta, _iMapWidth);
    
    if (iTempMapIndex >= 0 )
        this->changeScene (iPrevMapIndex);
}

//Revisar las colisiones con los recursos ademas de pintarlos en la pantalla
void ViewGame::checkForCollisionWithRecursosAndPaintThem ()
{
    _oDrawRecursos->doCollisionsWith (_iPx, _iPy, _iPWidth, _iPHeight, _piResourcePoints);
}

//Metodo para cambiar de escena una vez alcanzado la puerta
void ViewGame::changeScene (int& iPrevMapIndex)
{
    this->roomDeconstructor ();
    _bChangeScene = 1;
    _sPuerta = this->chooseADoor (iPrevMapIndex);
    iPrevMapIndex = 0;
}

std::string ViewGame::chooseADoor (int& iPrevMapIndex)
{
    std::string sReturn = "Entrada";
    
    if (iPrevMapIndex > _iMapIndex)
        sReturn = "Salida";
    
    if (iPrevMapIndex < _iMapIndex)
        sReturn = "Entrada";
    
    return sReturn;
}

