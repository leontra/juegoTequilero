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

ViewGame::ViewGame( ):
                        _bfStart( 0 ),
                        _iPx( 0 ),
                        _iPy( 0 ),
                        _iPWidth( 0 ),
                        _iPHeight( 0 ),
                        _bChangeScene( 0 ),
                        _bInicio( 0 ),
                        _iAvanzoRetrocedio( 0 ),
                        _sPuerta( "Entrada" ),
                        _bActionTouch( 0 ),
                        _iMapWidth( 0 ),
                        _fPauseLeft( 0 ),
                        _fPauseRight( 0 ),
                        _bPauseLeft( 0 ),
                        _bPauseRight( 0 ),
                        _bStartTouchLeft( 0 ),
                        _bStartTouchRight( 0 ),
                        _bPause( 0 ),
                        _bDoorCollision( 0 ),
                        _bText( 0 ),
                        _bFilosofiaInitialText( 0 ),
                        _bDoorMissText( 0 )
{
    _oMap = new MapWorld( );
    _oResource = new Resource( );
    _oPlayer = new Player( );
    _oPuertas = new Resource( );
    _oBarraMision = new BarraMision( );
    _oMilliseconds = new Milliseconds;
    _oAudioEngine = CocosDenshion::SimpleAudioEngine::getInstance( );
    _oRoomExit = new RoomExit( );
    _oDoors = new Doors( );
    _oMates = new Mates( );
    _oFilosofia = new FilosofiaIntroduction( );
    
    _bInicio = new int( 1 );
}

ViewGame::~ViewGame( )
{
    this->roomDeconstructor( );
    delete _oMap;
    delete _oResource;
    delete _oPuertas;
    delete _oPlayer;
    delete _bInicio;
    delete _oMilliseconds;
    delete _oBarraMision;
    delete _oRoomExit;
    delete _oDoors;
    delete _oFilosofia;
    delete _oMates;
}

bool ViewGame::init( )
{
    if ( !Layer::init( ) )
        return 0;
    
    _oAudioEngine->preloadEffect( "BackGround_00.wav" );
    
    this->roomConstructor( );
    this->pauseGameInput( );
    this->schedule( schedule_selector( ViewGame::update ) );
    
    return 1;
}

void ViewGame::roomConstructor ()
{
    //Inicializar la gravedad para el mundo
    float fGravedad = 7.0f;
    
    int mapIndex = 0;
    //Obtener el numero de mapa
    if( _bDoorCollision )
        mapIndex = _oDoors->getNextRoomIndex( );
    
    else
        mapIndex = _oRoomExit->getMapIndex( );
    
    if( mapIndex ) _bFilosofiaInitialText = 1;
    
    
    if( mapIndex % 2 == 0 )
        _oAudioEngine->playBackgroundMusic( "BackGround_00.wav", 1 );
    else
        _oAudioEngine->playBackgroundMusic( "BackGround_02.wav", 1 );
    
    
    //Asignar TileMap y darle un valor a la gravedad del mundo
    this->_tileMap = _oMap->mapTileXML( fGravedad, mapIndex );
    
    if( !mapIndex )
    {
        _oFilosofia->InitializeFilosofia( this );
    
        if( _bFilosofiaInitialText )
            _oFilosofia->setFilosofiaCompleteText( );
    }
    
    if( mapIndex )
        ResourcesBuffer::GetInstance( )->setLettersTest( 1 );
    
    _oRoomExit->initExits( *_tileMap );
    
    _oPlayer->init( *_tileMap, _oMap->getFGravedad( ), _sPuerta, mapIndex );
    _oPlayer->getPlayerSize( _iPWidth, _iPHeight );
    
    _oDoors->initDoors( mapIndex, this );
    _oMates->initMates( mapIndex, this );
    
    //Obtener la posicion inicial, ya sea de una puerta o de la continuacion del mapa
    if( _bDoorCollision )
        _oDoors->getPlayerInitialPosition( _iPx,  _iPy, _iPWidth, _iPHeight );
    else
        _oRoomExit->getPlayerInitialPosition( _iPx,  _iPy, _iPWidth, _iPHeight );
    
    _oPlayer->setPlayerRoomPosition( _iPx, _iPy );
    
    _oResource->init( );
    

    
    _oBarraMision->init( *_tileMap );
    
    _oResource->initResourcesRoom( mapIndex );
    
    addChild( _tileMap, 0, 0 );
    addChild( _oBarraMision, 0, 0 );
    addChild( _oResource, 0, 0 );
    addChild( _oPlayer, 0, 0 );
    _bDoorCollision = 0;
}

//Resetear valores para volverlos a construir
void ViewGame::roomDeconstructor( )
{
    _bChangeScene = 1;
    _oAudioEngine->stopBackgroundMusic( );
    _oMap->destroyMap( );
    _oPlayer->destroyPlayer( );
    _oResource->resetArrays( );
    _oBarraMision->deleteBarra( );
    _oRoomExit->resetRoom( );
    _oDoors->resetDoors( );
    _oMates->resetMates( );
    
    removeAllChildren( );
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
    if( _bChangeScene )
        this->createScene( );
    else
        this->updatePuertasRecursos( );
}

void ViewGame::createScene( )
{
    _bChangeScene = 0;
    *_bInicio = 1;
    this->roomConstructor ( );
}

void ViewGame::updatePuertasRecursos( )
{
    _oPlayer->getAllValues( _iPx, _iPy, _iPWidth, _iPHeight, _bActionTouch, _iMapWidth );
    this->testObjectsCollisions( );
    this->checkForCollisionWithPuertas( );
}

void ViewGame::checkForCollisionWithPuertas( )
{
    //Entero temporal, para saber si se movio de escena
    //int iTempMapIndex = -1;
    
    //int iPrevMapIndex = _iMapIndex;
    
    /*
    //Hacer las colisiones para el principio, hasta que el jugador salga de la puerta
    if (*_bInicio)
		_oPuertasBoxCollision->doStartCollisionsWith (_iPx, _iPy, _iPWidth, _iPHeight, _piResourcePoints, _sPuerta);
    
    else
        //Obtener el numero de mapa que sigue
		iTempMapIndex = _oPuertasBoxCollision->doCollisionsWith (_iPx, _iPy, _iPWidth, _iPHeight, _piResourcePoints, _iMapIndex, _bActionTouch,_sPuerta);
    
	if (iTempMapIndex >= 0)
		this->changeScene(iPrevMapIndex);
    */
    
	/*if (_sPuerta == ("PuertaSalida")){
     _iMapIndex = 2;
     }
     if (_sPuerta == ("PuertaEntrada")){
     _iMapIndex = 0;
     }*/
    
    //Revisar que haya alcanzado una puerta
	
    //Obtener el numero de mapa que sigue
	/*
    iTempMapIndex = _oPuertasBoxCollision->doCollisionWithSidesToExit ( _iPx, _iPy, _iPWidth, _iPHeight, _piResourcePoints, _iMapIndex, _sPuerta, _iMapWidth );
	
    if (iTempMapIndex >= 0 )
        this->changeScene (iPrevMapIndex);
    */
    
    if( _oFilosofia->testIfItIsTheRoom( ) && !_bFilosofiaInitialText )
    {
        _oFilosofia->testFilosofiaText( _iPx );
    }
    
    if( _oRoomExit->testExitCollision( _iPx, _iPy, _iPWidth, _iPHeight ) )
        this->roomDeconstructor( );
    
}

void ViewGame::testObjectsCollisions( )
{
    if( testResourcesCollisions( ) ) return;
    if( testMatesCollision( ) ) return;
    if( testDoorsCollision( ) ) return;
}

//Revisar las colisiones con los recursos ademas de pintarlos en la pantalla
bool ViewGame::testResourcesCollisions( )
{
    int iUpgrade = 0;
    
    iUpgrade = _oResource->testResourcesCollisions( _oPlayer->getXMax( ), _oPlayer->getYMax( ), _oPlayer->getXMin( ), _oPlayer->getYMin( ) );
    if( iUpgrade )
    {
        _oBarraMision->upgradeBarraWith( iUpgrade );
        return 1;
    }

    return 0;
}

bool ViewGame::testMatesCollision( )
{
    if( _bActionTouch )
    {
        if( !_bText )
        {
            int iUpgrade = _oMates->testMatesCollisions( _iPx, _iPy, this );
            if( iUpgrade != 0 ) _bText = 1;
            if( iUpgrade > 0 )
            {
                _oBarraMision->upgradeBarraWith( iUpgrade );
                return 1;
            }
            
            if( iUpgrade == -2 ) return 1;
        }
    }
    
    if( _bText )
    {
        if( _oMates->testRemoveText( _iPx, _iPy,  this ) )
            _bText = 0;
    }
    
    return 0;
}

bool ViewGame::testDoorsCollision( )
{
    if( _bActionTouch && !_bDoorMissText )
    {
        int iUpgradeDoor = _oDoors->testDoorsCollisions( _oPlayer->getXMax( ), _oPlayer->getYMax( ), _oPlayer->getXMin( ), _oPlayer->getYMin( ) );
        
        if( iUpgradeDoor == -2 )
        {
            _bDoorMissText = 1;
            return 1;
        }
        
        if( iUpgradeDoor > 0 ) _oBarraMision->upgradeBarraWith( iUpgradeDoor );
        
        if( iUpgradeDoor != 0 && iUpgradeDoor != -2 )
        {
            _bDoorCollision = 1;
            //Cambiar de mapa, por la puerta
            this->roomDeconstructor( );
            return 1;
        }

    }
    
    if( _bDoorMissText )
    {
        if( _oDoors->testRemoveText( _iPx, _iPy ) )
            _bDoorMissText = 0;
    }
    return 0;
}

//Metodo para cambiar de escena una vez alcanzado la puerta
void ViewGame::changeScene( int& iPrevMapIndex )
{
	this->roomDeconstructor();
	_bChangeScene = 1;
	if (_sPuerta == ("Entrada"))
        _sPuerta = this->chooseADoor( iPrevMapIndex );
	
    iPrevMapIndex = 0;
}

std::string ViewGame::chooseADoor( int& iPrevMapIndex )
{
    std::string sReturn = "Entrada";
    
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


