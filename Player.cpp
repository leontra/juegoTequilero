//
//
//  Player.cpp
//  Game Prototype
//
//  Created by Max on 4/14/14.
//
//

#include "Player.h"
#include <CCGeometry.h>

#define COCOS2D_DEBUG 1

USING_NS_CC;


Player::Player()
{
    fX = 0;
    
    fY = 0;
    
    fVx = 0;
    
    fVy = 0;
    
    fAy = 800;
    
    fTiempo = 2;
    
    fG = 0;
    
    iPlayerHeight = 0;
    
    iPlayerWidth = 0;
    
    
    bLeftTouch = false;
    
    bRightTouch = false;
    
    bTouchAction = false;
    
    fbJump = false;
    
    bJump = false;
    
    bGravity = true;
    
    bCustomGravity = false;
    
    bHorizontalLeft = false;
    
    bHorizontalRight = false;
    
    bVerticalPlus = false;
    
    bVerticalMinus = false;
    
    bEntro = false;
    
    // m_millisCount = new Milliseconds();
    
}


Player::~Player()
{
    //delete X;
}


bool Player :: init ()
{
    if( ! Layer :: init())
        return false;
    
    Size visibleSize = Director::getInstance () -> getVisibleSize ();
    //Point origin = Director::getInstance () -> getVisibleOrigin ();
    
    //this -> setOpacity( 255 );
    
    
    
    fX = 100;
    
    fY = 300;
    
    player = Sprite :: create( "bolas.png" );
    
    iPlayerWidth = player -> getContentSize().width / 2;
    
    iPlayerHeight = player -> getContentSize().height / 2;
    
	player -> setPosition( Point( fX,  fY ) );
    
    player -> setAnchorPoint( Point ( 0.5, 0.5 ) );
    
    this -> addChild( player,  0 );
    
    /*
    Image *image = new Image ();
    
    image -> initWithImageFile ( "cuadro.png" );
    
    printf( " \n es 	\t %d ", image -> getBitPerPixel());
     */
    
    //const uint32_t pixels = (const uint32_t * )CFDataGetBytePtr(image);
    
    //printf( " \n es 	\t %d ", image -> getMipmaps() );
    
    
    /*
     // CCLOG ( "%f" , player -> getPosition().x);
     Color4B * buffer = (Color4B *)malloc ( sizeof(Color4B) * 10000 );
     
     glReadPixels(fX, fY, 25, 25, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
     
     unsigned int numPixels = 25 * 25;
     
     // Read buffer
     unsigned int step = 1;
     
     for(unsigned int i=0; i<numPixels; i+=step) {
     
     Color4B color = buffer[i];
     // Here we check if a single pixel has both RED and BLUE pixels
     
     
     printf( "  %d  ", (int) color.r );
     }
     */
    
    this->schedule( schedule_selector ( Player :: update ) );
    
    
    
    return true;
    
}

int *(Player::iX) = new int();
int *(Player::iY) = new int();
int *(Player::iWidth) = new int();
int *(Player::iHeight) = new int();
int *(Player::iG) = new int();
int *(Player::iVx) = new int();
int *(Player::iVy) = new int();


bool *Player::bbTouchFloor = new bool(0);
bool *Player::bbVerticalPlus = new bool(0);
bool *Player::bbVerticalMinus = new bool(0);
bool *Player::bbHorizontalLeft = new bool(0);
bool *Player::bbHorizontalRight = new bool(0);

void Player :: update ( float dt )
{
    this -> resetValues();
    this -> input ();
    //this -> checkForCollisions();
    this -> checkForJump();
    this -> walk();
    this -> constraint();
    this -> gravity();
    this -> movement ();
    this -> setValuesForIntsStaticMembers();
    this -> setValuesForBoolStaticMembers();
} // void update

void Player::resetValues()
{
    fVx = 0;
    bJump = false;
    bLeftTouch = false;
    bRightTouch = false;
    bTouchAction = false;
    bCustomGravity = false;
}

void Player :: input ()
{
    
    if( Input :: touchLeft () )
        bLeftTouch = true;
    
    //fVx = - 7;
    
    if( Input::touchRight () )
        bRightTouch = true;
    
    //fVx = 7;
    
    if( Input :: touchAction () )
        bTouchAction = true;
    
    
    if( Input :: touchJump () )
        bJump = true;
    
} // void input

void Player::checkForJump()
{
    if( !fbJump && bJump )
    {
        fVy = 200;
        fbJump = true;
        bTouchFloor = false;
        bGravity = true;
    }
    
    //Revisar si se apreto el botón de salto
    if( fbJump )
        this -> jump ();
    
    //Revisar si el jugador está en el piso de nuevo, para que pueda volver a saltar
    if( bTouchFloor || bVerticalMinus )
    {
        printf( "entra:\t%d\n", bVerticalMinus);
        fVy = 0;
        fbJump = false;
        bGravity = 0;
    }
}

void Player::jump()
{
    if ( fVy > 0)
    {
        fVy = fVy - (10 * fTiempo);
        bGravity = 1;
    }
    
    if ( bVerticalPlus )
    {
        fVy = 0;
        bGravity = 1;
    }
}

void Player::walk()
{
    
    if (bLeftTouch)
        fVx = - 7;
    
    if (bRightTouch)
        fVx =  7;
    
    if (bHorizontalLeft)
        fVx = 0;

    if (bHorizontalRight)
        fVy = 0;
}


void Player::constraint()
{
    Size visibleSize = Director::getInstance () -> getVisibleSize ();
    if ( fX + iPlayerWidth + fVx > visibleSize.width)
    {
        if (!bEntro)
        {
            bEntro = true;
            fVx = visibleSize.width - (fX + iPlayerWidth);
        } else
            fVx = 0;
    }
    else if ( fX - iPlayerWidth + fVx < 0)
    {
       if (fX > iPlayerWidth)
    
            fVx = fX - (iPlayerWidth - fVx);
        else
            fVx = 0;
    }
    else
    {
        bEntro = false;
    }
    int fTempY = fY - iPlayerHeight - fG + (fVy / 5);
    if ( fTempY <=  0 )
    {
        fY += (fTempY * -1) - fG;
        fVy = 0;
        bGravity = 0;
        fbJump = false;
        bCustomGravity = false;
    }
}

void Player::gravity()
{
    if (bGravity)
    {
        if (!bCustomGravity)
            fG = 9;
    }
    else
        fG = 0;
}

void Player::movement ()
{
    fY += fVy / 5;
    fY -= fG;
    fX += fVx;
    
    player -> setPosition ( fX, fY );
}


void Player::setValuesForIntsStaticMembers()
{
    *(Player::iX) = fX;
    *(Player::iY) = fY;
    *(Player::iWidth) = iPlayerWidth;
    *(Player::iHeight) = iPlayerHeight;
    *(Player::iG) = fG;
    *(Player::iVx) = fVx;
    *(Player::iVy) = fVy;
}

void Player::setValuesForBoolStaticMembers()
{
    (Player::bbTouchFloor) = &bTouchFloor;
    (Player::bbVerticalMinus) = &bVerticalMinus;
    (Player::bbVerticalPlus) = &bVerticalPlus;
    (Player::bbHorizontalLeft) = &bHorizontalLeft;
    (Player::bbHorizontalRight) = &bHorizontalRight;
}

void Player::getAllValues( int &_iX, int &_iY, int &_iWidth, int &_iHeight, int &_iG, int &_iVx, int &_iVy)
{
    _iX = *(iX) ? *iX : 0;
    _iY = (iY) ? *iY : 0;
    _iWidth = *(iWidth) ? *iWidth : 0;
    _iHeight = *(iHeight) ? *iHeight : 0;
    _iG = *(iG) ? *iG : 0;
    _iVx = *(iVx) ? *iVx : 0;
    _iVy = *(iVy) ? *iVy : 0;
}


void Player::changeBoolAt( bool _bool,  int index)
{
    switch (index) {
        case 0:
            *bbTouchFloor = _bool;
            break;
        case 1:
            *bbVerticalMinus = _bool;
            break;
        case 2:
            *bbVerticalPlus = _bool;
            break;
        case 3:
            *bbHorizontalLeft = _bool;
            break;
        case 4:
            *bbHorizontalRight = _bool;
            break;
            
        default:
            break;
    }
}




/*

void Player::collision ()
{
    
    if (!bVerticalMinus)
        bGravity = 1;
    else
        bTouchFloor = true;
    
} // void collision

void Player :: updateValues ()
{
    this -> collision ();
} // void updateValues

void Player::checkForCollisions()
{
    for ( int i = 0; i < 3; i ++ )
    {
        //BoxCollision :: checkCollision( platformArray[ i ] -> platform, player, fX, fY, fVx, fVy, bHorizontal, bVerticalPlus, bVerticalMinus );
        
        this -> collision();
        
        if( bHorizontal || bVerticalMinus || bVerticalPlus )
            break;
    }  //For
}
*/
