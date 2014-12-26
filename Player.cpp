//
//  Player.cpp
//  JuegoTequilero
//
//  Created by Max on 7/11/14.
//
//

#include "Player.h"


USING_NS_CC;


Player::Player ():  _iX (0),
                    _iY (0),
                    _iVx (0),
                    _iVy (0),
                    _iPlayerHeight (0),
                    _iPlayerWidth (0),
                    _fGravedad (0),
                    _fG (0),
                    _fAy (0),
                    _fTiempo (2),
                    _fcronometro(0),
                    _bActionTouch (0),
                    _bLeftTouch (0),
                    _bRightTouch (0),
                    _bJumpTouch (0),
                    _fbJump (0),
                    _bTouchFloor (0),
                    _bCollisionX (0),
                    _bCollisionY (0),
                    _bTouchUp (0),
                    _spritePlayer (0),
                    _iMap (0),
                    _iWidthTile (0),
                    _iHeightTile (0),
                    _iMapWidth (0),
                    _bFlip (1),
                    _iAnimState (0),
                    _bOutOfBoundries( 0 ),
                    _iMapHeight( 0 ),
                    _iFallAy( 0 )
{
    _oRegularPlatform = new RegularPlatform( );
    _oBreakablePlatform = new BreakablePlatform( );
    _oHardTopPlatform = new HardTopPlatform( );
    _oHardBottomPlatform = new HardBottomPlatform( );
    
    _oCreateAnim = new CreateAnim( );
    _oObstacles = new Obstacles( );
    
    //Inicializar los apuntadores de las posiciones en X y Y
    _iX = new int (1);
    _iY = new int (1);
    _iVy = new int (1);
    
    //Inicializar los boolean para las colisiones
    _bCollisionY = new int (0);
    _bCollisionX = new int (0);
    _bTouchFloor = new int (0);
    _bTouchUp = new int (0);
}


Player::~Player ()
{
    delete _iX;
    delete _iY;
    delete _bTouchFloor;
    delete _bCollisionY;
    delete _bCollisionX;
    delete _bTouchUp;
    delete _iVy;
    delete _oBoxCollisions;
    delete _oRegularPlatform;
    delete _oObstacles;
    delete _oCreateAnim;
    delete _oBreakablePlatform;
    delete _oHardTopPlatform;
    delete _oHardBottomPlatform;
    this->destroyPlayer ();
}


bool Player::init( cocos2d::TMXTiledMap& _tileMap, float& fGravedad, std::string sPuerta, int& iMap )
{
    if( !Layer::init( ) )
        return 0;
    
    this->initPlayer( _tileMap, sPuerta );
    
    this->initObjects( _tileMap );
    
    this->addChild( _spritePlayer,  0 );
    
    this->_fG = fGravedad;
    
    this->_iMap = iMap;
    
    //Hacer el update en milisegundos
    this->schedule( schedule_selector( Player::pintarPlayer ) );
    
    return 1;
}

void Player::initPlayer( cocos2d::TMXTiledMap& _tileMap, std::string sPuerta )
{
    //Inicializar la imagen del sprite del personaje
    _spritePlayer = Sprite::create( "DonCuco_Idle.png" );
    
    //Obtener el ancho y alto del sprite
    _iPlayerWidth = _spritePlayer->getContentSize( ).width / 2;
    _iPlayerHeight = _spritePlayer->getContentSize( ).height / 2;
    
    _iMapHeight = _tileMap.getContentSize( ).height;
    _iMapWidth = _tileMap.getContentSize( ).width;
    
    //printf( "Mediad del tile map:  %d  --  %d\n", _iMapWidth, _iMapHeight );
    
    //Colocar el centro del player en el centro del sprite
    _spritePlayer->setAnchorPoint( Point( 0.5f, 0.5f ) );
    
    //Inicilizar la animacion junto el numero de sprites y el numero de cuadros por segundo
    
    //Inicializar las animaciones del personaje
    _oCreateAnim->initAnimations( _spritePlayer );
    
    _oCreateAnim->runIdleAction( _spritePlayer );
    
}

void Player::initObjects (cocos2d::TMXTiledMap& _tileMap)
{
    //Obtener los puntos de colision para las plataformas normales
    _oRegularPlatform->initPlatforms( _tileMap );
    _oBreakablePlatform->initPlatforms( _tileMap );
    _oHardBottomPlatform->initPlatforms( _tileMap );
    _oHardTopPlatform->initPlatforms( _tileMap  );
    
    _oObstacles->initObstacles( _tileMap, this );
    
    //Obtener el objeto estatico de la clase
    _oInput = new Input ();
    
    //Obtener el width de los tile
    _iWidthTile = _oRegularPlatform->getIWidth( );
    
    _iHeightTile = _oRegularPlatform->getIHeight( );
    
    //Inicializar la clase para las colisiones
    _oBoxCollisions = new BoxCollision ( _iWidthTile, _iHeightTile, _oRegularPlatform->getMPoints( ), _oRegularPlatform->getNPoints( ), _fGravedad, _bCollisionX, _bCollisionY, _bTouchFloor, _bTouchUp);
}

//Update del objeto 60 por segundo
void Player::pintarPlayer (float dt)
{
    this->resetValues( );
    this->input( );
    this->checkForBoundries( );
    this->walk( );
    this->resetJumpValues( );
    this->checkForJump( );
    this->checkForCollisions( );
    this->constraint( );
    this->sumGravity( );
    this->checkForStateAnim( );
    this->checkForFlip( );
    
    this->movement( );
} // void update

//Resetear los valores cada cuadro por segundo
void Player::resetValues( )
{
    *_bCollisionX = 0;
    *_bCollisionY = 0;
    _iAnimState = 0;
    _iVx = 0;
    *_iVy = 0;
    _fGravedad = _fG;
    _bJumpTouch = 0;
    _bLeftTouch = 0;
    _bRightTouch = 0;
    _bActionTouch = 0;
    _bOutOfBoundries = 0;
}

//Input del player
void Player :: input( )
{
    if( _oInput->touchLeft( ) )
        _bLeftTouch = 1;
    
    if( _oInput->touchRight( ) )
        _bRightTouch = 1;
    
    if( _oInput->touchAction( ) )
        _bActionTouch = 1;
    
    if( _oInput->touchJump( ) )
        _bJumpTouch = 1;
    
} // void input

//Revisar si apreto la tecla de salto
void Player::checkForJump( )
{
    //Revisar si el jugador está en el piso de nuevo, para que pueda volver a saltar
    if( *_bCollisionY )
        *_bTouchFloor = 1;
    
    //Iniciar los valores para el brinco
    if( !_fbJump && _bJumpTouch && *_bTouchFloor )
    {
        _fAy = 160;
        _fbJump = 1;
        *_bTouchFloor = 0;
    }
    
    //Revisar si se apreto el botón de salto
    if( _fbJump )
        this->jump( );
}

//Colocar los valores para realizar el brinco
void Player::jump( )
{
    _fAy -= ( 6 * _fTiempo );
    _fAy = ( ( _fAy / 4 ) ) > 0 ? _fAy : 0;
    *_iVy = _fAy / 4;
    //printf ("\nLa desaceleracion es:   %f\n", _fAy);
}

//Resetear los valores al tocar techo
void Player::resetJumpValues( )
{
    if( *_bTouchUp || _fAy <= 0 )
    {
        *_bTouchUp = 0;
        _fbJump = 0;
        _fAy = 0;
    }
}

//Metodo para hacerle la suma a la velocidad en caso de haber apretado los botones de movimiento
void Player::walk( )
{
    //Definir la velocidad
    int iVx = 6;
    
    if( _bLeftTouch )
        _iVx = -iVx;
    
    if( _bRightTouch )
        _iVx =  iVx;
    
    if( _bLeftTouch && _bRightTouch )
        _iVx = 0;
}

//Metodo para mantener al jugador dentro de la pantalla, hace un constrain en X y Y
void Player::constraint( )
{
    if( !_iMap )
        this->constraintXLeft( );
    //this->constraintXRight ();
    this->constraintY( );
}

void Player::constraintXLeft( )
{
    //Hacer el constraint del lado izquierdo de la pantalla
    if( ( *_iX - _iPlayerWidth + _iVx ) < 0 )
    {
        int iResta = ( *_iX - _iPlayerWidth + _iVx );
        *_iX += _iVx;
        *_iX -= iResta;
        *_bCollisionX = 1;
    }
}

void Player::constraintXRight( )
{
    Size visibleSize = Director::getInstance( )->getVisibleSize( );
    
    //Hacer el constraint del lado derecho de la pantalla
    if( ( *_iX + _iPlayerWidth + _iVx ) > _iMapWidth )
    {
        int iResta = ( *_iX + _iPlayerWidth + _iVx ) - visibleSize.width;
        *_iX += _iVx;
        *_iX -= iResta;
        *_bCollisionX = 1;
    }
}

//Hcer el constrain hacia abajo de la pantalla
void Player::constraintY( )
{
	if( *_iY <= -_iPlayerHeight && !_fbJump )
    {
		Player::setInitialValues( _iFallx, _iFally );
    }
}

void Player::checkForBoundries( )
{
    if( *_iY <= -_iPlayerHeight || *_iY + _iPlayerHeight > _iMapHeight )
        _bOutOfBoundries = 1;
    
    if( *_iX - _iPlayerWidth < 0 || *_iX + _iPlayerWidth > _iMapWidth )
        _bOutOfBoundries = 1;
}

//Metodo para restarle la gravedad a la posicion en Y
void Player::sumGravity( )
{
    if( *_bCollisionY || _fAy > 0 )
    {
        _fGravedad = 0;
    }
}

void Player::checkForFlip( )
{
    if( _bRightTouch )
        _bFlip = 1;
    else if( _bLeftTouch )
        _bFlip = 0;
    
    this->doFlipWith( _bFlip );
}

//Sumar las velocidades en Y y X, hacer el update al sprite con las nuevas posiciones
void Player::movement( )
{
    *_iY += *_iVy;
    
    *_iY -= _fGravedad;
    
    if( !*_bCollisionX )
    {
        *_iX += _iVx;
    }
    
    //Actualizar la posicion del sprite del player
    this->updatePlayerSprite (*_iX, *_iY);
}

//Inicializar la posicion del jugador en un principio
void Player::setInitialValues (int posX, int posY)
{
    *_iX = posX;
    *_iY = posY;
    _fAy = _iFallAy;
    if( _fAy > 0 )
    {
        _fbJump = 1;
    }
    else
        *_bTouchFloor = 1;
    
    this->updatePlayerSprite (*_iX, *_iY);
}

//Metodo para actualizar la posicion del player
void Player::updatePlayerSprite (int& posX, int& posY)
{
    _spritePlayer->setPosition (Point (posX,  posY));
}

//Obtener la posicion en X, desde afuera
int* Player::getPosX ()
{
    return _iX;
}

//Obtener la posicion en Y, desde afuera
int* Player::getPosY ()
{
    return _iY;
}

float Player::getXMax( )
{
    return *_iX - _iPlayerWidth;
}

float Player::getYMax( )
{
    return *_iY - _iPlayerHeight;
}

float Player::getXMin( )
{
    return *_iX + _iPlayerWidth;
}

float Player::getYMin( )
{
    return *_iY + _iPlayerHeight;
}

//Obtener los valores desde afuera
void Player::getAllValues (int& iX, int& iY, int& iWidth, int& iHeight, bool& bActionTouch, int& iWidthTile)
{
    iX = *_iX;
    iY = *_iY;
    iWidth = _iPlayerWidth;
    iHeight = _iPlayerHeight;
    bActionTouch = _bActionTouch;
    iWidthTile = _iMapWidth;
}

void Player::checkForCollisions ()
{
    _oBoxCollisions->doMapping( *_iX, *_iY );
    
    _oBoxCollisions->doCollisionWithRegularPlatforms( _iX, _iY, _iPlayerWidth, _iPlayerHeight, _iVx, _iVy, _oRegularPlatform->getPlatformsPoints( ) );
    
    if( _oBreakablePlatform->getSize( ) )
        _oBoxCollisions->doCollisionWithBreakablePlatforms( _iY, _iPlayerHeight, _iVy, _oBreakablePlatform->getPlatformsPoints( ) );
    
    if( _oHardTopPlatform->getSize( ) )
        _oBoxCollisions->doCollisionWithHardTopPlatforms( _iY, _iPlayerHeight, _iVy, _oHardTopPlatform->getPlatformsPoints( ) );
    
   if( _oHardBottomPlatform->getSize( ) )
      _oBoxCollisions->doCollisionWithHardBottomPlatforms( _iY, _iPlayerHeight, _iVy, _oHardBottomPlatform->getPlatformsPoints( ) );
    
    if( _oObstacles->testObstaclesCollisions( getXMax( ), getYMax( ), getXMin( ), getYMin( ) ) )
        setInitialValues( _iFallx, _iFally );
}

//Posicion inicial al entrar a un nuevo cuarto
void Player::setPlayerRoomPosition( const int& _x, const int& _y )
{
    this->setInitialValues( _x, _y );
    _iFallx = _x;
    _iFally = _y;
    //_iFallAy = _fAy;
}

void Player::getPlayerSize( int& _width, int& _height )
{
    _width = _iPlayerWidth;
    _height = _iPlayerHeight;
}

//Inicilizar posicion del jugador, de acuerdo al tile map
void Player::initPosition( cocos2d::TMXTiledMap& _tileMap, std::string sPuerta )
{
    //Obtener los diferentes objetos contenidos en el xml
    auto tileGroups = _tileMap.getObjectGroups ();
    
    this->setInitScale (sPuerta);
    
    //Obtener posiciones del player
    for (auto& objectGroup:tileGroups)
    {
        //Terminar si el objeto no es un recurso
		if (objectGroup->getGroupName() != "Aparicion" && objectGroup->getGroupName() != "Recurso")
            continue;
        
        //Obtener objeto
        auto objects = objectGroup->getObjects();
        
        //Revisar por cada propiedad del objeto
		for (auto& object : objects)
		{
			auto properties = object.asValueMap();
            
			auto name = properties.at("name");
			auto posX = properties.at("x");
			auto posY = properties.at("y");
			auto width = properties.at("width");
			auto height = properties.at("height");
            
			int X = posX.asInt() + _iPlayerWidth;
			int Y = posY.asInt() + _iPlayerHeight;
            
			//Mandar las posiciones para inicializar
			if (name.asString() == sPuerta)
            {
				Player::setInitialValues(X, Y);
				_iFallx = X;
				_iFally = Y;
			}
			/*if (name.asString() == sPuerta&& ("PuertaSalida") == sPuerta){
             Player::setInitialValues(X, Y);
             _iFallx = X;
             _iFally = Y;
             }
             if (name.asString() == sPuerta && ("PuertaEntrada") == sPuerta){
             Player::setInitialValues(X, Y);
             _iFallx = X;
             _iFally = Y;
             }*/
            
        }//For
        
    }//For
    
}

void Player::doFlipWith (int& _bFlip)
{
    if (_bFlip)
    {
        _spritePlayer->setScaleX( 1 );
    }
    else
    {
        _spritePlayer->setScaleX( -1 );
    }
}

void Player::setInitScale (std::string sAparicion)
{
    if (sAparicion == "Entrada")
        _bFlip = 1;
    else
        _bFlip = 0;
    
    this->doFlipWith (_bFlip);
    
}

void Player::checkForStateAnim ()
{
    if (_bRightTouch || _bLeftTouch)
        _iAnimState = 1;
    
    if (!*_bCollisionY)
        _iAnimState = 2;
    
    this->runAnimateActions ();
}

void Player::runAnimateActions ()
{
    if (_iAnimState == 2)
    {
        //_spritePlayer->setSpriteFrame ("Don");
        _oCreateAnim->runJumpAction (_spritePlayer);
    }
    if (_iAnimState == 1)
        _oCreateAnim->runWalkAction (_spritePlayer);
    
    if (!_iAnimState)
        _oCreateAnim->runIdleAction (_spritePlayer);
}

//Destruir al jugador y sus objetos, variables
void Player::destroyPlayer ()
{
    this->resetValues ();
    
    _spritePlayer = 0;
    
    this->resetPosition ();
    
    this->destroyObjects ();
    
    this->removeAllChildren ();
}

//Resetear los valores de los apuntadores
void Player::resetPosition ()
{
    *_iX = 0;
    *_iY = 0;
    *_iVy = 0;
    *_bTouchUp = 0;
    *_bTouchFloor = 0;
    *_bCollisionY = 0;
    *_bCollisionX = 0;
    _bFlip = 1;
    _iFallAy = _fAy;
}

//Destruir los objetos
void Player::destroyObjects ()
{
    _oRegularPlatform->resetArray( );
    _oBoxCollisions->resetValues( );
    _oBreakablePlatform->resetArray( );
    _oHardBottomPlatform->resetArray( );
    _oHardTopPlatform->resetArray( );
    _oObstacles->resetObstacles( );
    
    _oInput = 0;
}

void Player::cronometro()
{
	_fcronometro ++;
	if (_fcronometro == 1250){
		Player::setInitialValues(_iFallx, _iFally); _fcronometro = 0; }
}


