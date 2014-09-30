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

ViewGame::ViewGame():
                        _piResourcePoints (0),
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
                        _iMapWidth (0),
                        _fPauseLeft( 0 ),
                        _fPauseRight( 0 ),
                        _bPauseLeft( 0 ),
                        _bPauseRight( 0 ),
                        _bStartTouchLeft( 0 ),
                        _bStartTouchRight( 0 ),
                        _bPause( 0 )
{
    _oMap = new MapWorld ();
    _oResource = new Resource ();
    _oPlayer = new Player ();
    _oPuertas = new Resource ();
    _oDrawRecursos = new DrawRecursos ();
    _oBarraMision = new BarraMision ();
    _oMilliseconds = new Milliseconds;
    _oAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance( );
    
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
    delete _oMilliseconds;
    delete _oBarraMision;
}

bool ViewGame::init ()
{
    if (!Layer::init())
        return 0;
    
    //Escalar el tile map
    //_tileMap->setScale(1);
    
    _oAudioEngine->preloadEffect ("GoDogeGo.wav");
    
    _iMapIndex = 0;
    
    this->roomConstructor ();
    
    this->pauseGameInput ();
    
    this->schedule (schedule_selector (ViewGame::update));
    
    return 1;
}

void ViewGame::roomConstructor ()
{
   //if (!_iMapIndex)
        _oAudioEngine->playBackgroundMusic( "GoDogeGo.wav" );
    /*
    if (_iMapIndex == 1)
        _oAudioEngine->playBackgroundMusic ("astralObservatory.mp3");
    if (_iMapIndex == 2)
        _oAudioEngine->playBackgroundMusic ("oathToOrder.mp3");
	*/
    
    //Inicializar la gravedad para el mundo
    float fGravedad = 9.0;
    
    //Asignar xml y darle un valor a la gravedad del mundo
    this->_tileMap = _oMap->mapTileXML (fGravedad, _iMapIndex);
    
    //Inicializar al player
    _oPlayer->init (*_tileMap, _oMap->getFGravedad(), _sPuerta, _iMapIndex);
    
    //Obtener los puntos de colision para los recursos
    _piResourcePoints = _oResource->initResources ( *_tileMap );
    
    //Obtener los puntos de las puertas en el mapa
    //_orPuertasPoints = _oPuertas->initResources (*_tileMap);
    
    //Inicializar las colisiones para las puertas
	_oPuertasBoxCollision = new PuertasBoxCollision(_iMapIndex, _oResource->getNRecursos(), _bInicio);
    
    //Inilizar la barra de mision
    _oBarraMision->init (*_tileMap);
    
    //Inicilizar el layer de los recursos
    _oResource->init ();
    
    //Obtener el numero de recursos por mapa para hacer la iteracion
    int iNRecursos = _oResource->getNRecursos ();
    
    //Pasar el numero de recursos por mapa para las colisiones y pintarlos
    _oDrawRecursos->setNRecursos (iNRecursos);
    
    addChild (_tileMap, 0, 0);
    
    addChild (_oBarraMision, 0, 0);
    
    addChild (_oPlayer, 0, 0);
    
    addChild (_oResource, 0, 0);
    
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
    
    _oBarraMision->deleteBarra( );
    
    delete _oPuertasBoxCollision;
    
    removeAllChildren ();
}

void ViewGame::update( float dt )
{
    _bPause = 0;
    
    if( _bPauseLeft || _bPauseRight )
    {
        _bPauseLeft = _bPauseRight = 0;
        this->resetPauseValues( );
        _bPause = 1;
        this->doPause( );
    }
    
    _bPauseLeft = _bPauseRight = 0;
    
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
    
    
    //Hacer las colisiones para el principio, hasta que el jugador salga de la puerta
    if (*_bInicio)
		_oPuertasBoxCollision->doStartCollisionsWith (_iPx, _iPy, _iPWidth, _iPHeight, _piResourcePoints, _sPuerta);
    
    else
        //Obtener el numero de mapa que sigue
		iTempMapIndex = _oPuertasBoxCollision->doCollisionsWith (_iPx, _iPy, _iPWidth, _iPHeight, _piResourcePoints, _iMapIndex, _bActionTouch,_sPuerta);
    
	if (iTempMapIndex >= 0)
		this->changeScene(iPrevMapIndex);
    
	/*if (_sPuerta == ("PuertaSalida")){
     _iMapIndex = 2;
     }
     if (_sPuerta == ("PuertaEntrada")){
     _iMapIndex = 0;
     }*/
    //Revisar que haya alcanzado una puerta
	
    //Obtener el numero de mapa que sigue
	iTempMapIndex = _oPuertasBoxCollision->doCollisionWithSidesToExit (_iPx, _iPy, _iPWidth, _iPHeight, _piResourcePoints, _iMapIndex, _sPuerta, _iMapWidth);
	
    if (iTempMapIndex >= 0 )
        this->changeScene (iPrevMapIndex);
}

//Revisar las colisiones con los recursos ademas de pintarlos en la pantalla
void ViewGame::checkForCollisionWithRecursosAndPaintThem( )
{
    int iUpgrade = 20;
    
    if ( _oDrawRecursos->doCollisionsWith( _iPx, _iPy, _iPWidth, _iPHeight, _piResourcePoints ) == 1 )
        _oBarraMision->upgradeBarraWith( iUpgrade );
}

//Metodo para cambiar de escena una vez alcanzado la puerta
void ViewGame::changeScene(int& iPrevMapIndex)
{
	this->roomDeconstructor();
	_bChangeScene = 1;
	if (_sPuerta == ("Entrada"))
        _sPuerta = this->chooseADoor(iPrevMapIndex);
	
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



void ViewGame::pauseGameInput( )
{
    auto listenerPause = this->createInputForPause( );
    
    //Inicializar los diferentes tipos de eventos del input
    this->beganTouch( listenerPause );
    //this->movedTouch( listenerPause );
    this->endedTouch( listenerPause );
    this->cancelledTouch( listenerPause );
    
    //Agregar el input a los eventos del juego
    //_eventDispatcher->addEventListenerWithFixedPriority( listenerPause, 5 );
    //_eventDispatcher->addEventListenerWithFixedPriority( listenerPause, 4 );
    _eventDispatcher->addEventListenerWithFixedPriority( listenerPause, 4 );

}

EventListenerTouchOneByOne* ViewGame::createInputForPause( )
{
    auto listenerPause = EventListenerTouchOneByOne::create( );
    
    listenerPause->setSwallowTouches( 0 );
    
    this->resetPauseValues( );
    
    return listenerPause;
}

void ViewGame::resetPauseValues( )
{
    _bStartTouchLeft = _bStartTouchRight = 0;
    _bPauseLeft = _bPauseRight = _bPause = 0;
    _fPauseLeft = _fPauseRight = 0;
}

void ViewGame::beganTouch( cocos2d::EventListenerTouchOneByOne* listenerPause )
{
    listenerPause->onTouchBegan = [ & ]( cocos2d::Touch* touch, cocos2d::Event* event )
    {
        Point locationInNode = touch->getLocation( );
        
        if( _bPause ) return 0;
        
         //std::cout << "Touch Pause Begin" << std::endl;
        
        Size visibleSize = Director::getInstance( )->getVisibleSize( );
        
        Rect rectPauseLeft = Rect( 0, 0, visibleSize.width / 2, visibleSize.height );
        Rect rectPauseRight = Rect( visibleSize.width / 2, 0, visibleSize.width / 2, visibleSize.height );
        
        if( rectPauseLeft.containsPoint( locationInNode ) && !_bStartTouchLeft && ( _bStartTouchLeft = 1 ) )
        {
            //printf ("\nTouch Pausa Left\n");
            touch->_ID = 11;
            _bPauseLeft = 0;
            _fPauseLeft = locationInNode.x;
            return 1;
        }
        else
        if( rectPauseRight.containsPoint( locationInNode ) && !_bStartTouchRight && ( _bStartTouchRight = 1 ) )
        {
            //printf ("\nTouch Pausa Right\n");
            touch->_ID = 12;
            _bPauseRight = 0;
            _fPauseRight = locationInNode.x;
            return 1;
        }
        
        return 0;
    }; // onTouchBegan
}

void ViewGame::endedTouch( cocos2d::EventListenerTouchOneByOne* listenerPause )
{
    listenerPause->onTouchEnded = [ & ]( cocos2d::Touch* touch, cocos2d::Event* event )
    {
        Point locationInNode = touch->getLocation( );
        
        int iTouchId = touch->_ID;
        
        //std::cout << "Touch Pause End:        " << iTouchId << std::endl;
        
        if( iTouchId == 11 && _bStartTouchLeft )
        {
            _bStartTouchLeft = 0;
            _bPauseLeft = 0;
            touch->_ID = 14;
            //printf( "\nTouch PausaLeft ended :      %f  \n", locationInNode.x - _fPauseLeft  );
            if( locationInNode.x  - _fPauseLeft >= 250 )
                _bPauseLeft = 1;
            _fPauseLeft = 0;
        }
        else
        if( iTouchId == 12 && _bStartTouchRight )
        {
            _bStartTouchRight = 0;
            _bPauseRight = 0;
            touch->_ID = 14;
            //printf ("\nTouch PausaRight ended :      %f  \n",   _fPauseRight - locationInNode.x  );
            if( _fPauseRight - locationInNode.x >= 250 )
                _bPauseRight = 1;
            _fPauseRight = 0;
        }
        
        if( _bStartTouchLeft && !( _fPauseLeft = 0 ) ) _bStartTouchLeft = 0;
        if( _bStartTouchRight && !( _fPauseRight = 0 ) ) _bStartTouchRight = 0;
        
    }; //onTouchEnded
}

void ViewGame::movedTouch (cocos2d::EventListenerTouchOneByOne* listenerPause)
{
    //Revisar si movio el dedo sin despegarlo de la pantalla
    listenerPause->onTouchMoved = [&] (cocos2d::Touch* touch,  cocos2d::Event* event)
    {
        Point locationInNode = touch -> getLocation ();
        Size visibleSize = Director::getInstance ()->getVisibleSize();
        Rect rectPause = Rect (0, visibleSize.height - 150, visibleSize.width, 150);
        
       // int iTouchId = touch->_ID;
        
    }; //Touch Moved
}

void ViewGame::cancelledTouch( cocos2d::EventListenerTouchOneByOne* listenerPause )
{
    //Revisar si se cancelo el touch
    listenerPause->onTouchCancelled = [ & ]( cocos2d::Touch* touch, cocos2d::Event* event )
    {
        Point locationInNode = touch->getLocation( );
        
        int iTouchId = touch->_ID;
        
        if( iTouchId == 11 && _bStartTouchLeft )
        {
            _bStartTouchLeft = 0;
            _bPauseLeft = 0;
            //printf( "\nTouch PausaLeft cancelled :      %f  \n", locationInNode.x  - _fPauseLeft  );
            _fPauseLeft = 0;
        }
        else
            if( iTouchId == 12 && _bStartTouchRight )
            {
                _bStartTouchRight = 0;
                _bPauseRight = 0;
                //printf ("\nTouch PausaRight cancelled :      %f  \n", _fPauseRight - locationInNode.x  );
                _fPauseRight = 0;
            }
        
    }; //Touch Cancelled
}


void ViewGame::doPause( )
{
    auto director = Director::getInstance( );
    auto layerPause = PauseGame::create( );
    director->getRunningScene( )->addChild( layerPause, 6 );
    director->pause( );
    
    //Director::getInstance( )->pushScene( PauseGame::createScene( ) );
}


