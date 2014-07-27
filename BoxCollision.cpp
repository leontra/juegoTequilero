//
//  BoxCollision.cpp
//  JuegoTequilero
//
//  Created by Max on 7/11/14.
//
//

#include "BoxCollision.h"


BoxCollision::BoxCollision (int& tileWidth, int& tileHeight, int& iMPoints, int& iNPoints, float& fGravedad, int* bCollisionX, int* bCollisionY, int* bTouchFloor, int* bTouchUp):
                        _lTileWidth (tileWidth),
                        _lTileHeight (tileHeight),
                        _iMPoints (iMPoints),
                        _iNPoints (iNPoints),
                        _fGravedad (fGravedad),
                        _bCollisionX (0),
                        _bCollisionY (0),
                        _bTouchFloor (0),
                        _bTouchUp (0),
                        _iTempVy (0),
                        _iContador (0)
{
    _bCollisionX = bCollisionX;
    _bCollisionY = bCollisionY;
    _bTouchFloor = bTouchFloor;
    _bTouchUp = bTouchUp;
    
    _oCronometro = new Milliseconds;
}

BoxCollision::~BoxCollision ()
{
    this->resetValues ();
    delete _oCronometro;
}

void BoxCollision::doCollisionWith (int* iX, int* iY, int& iWidth, int& iHeight, int& iVx, int* iVy, vector* vCollision)
{
    _iTempVy = 0;
    
    for (int i = 0; i < _iMPoints * _iNPoints; ++i)
    {
        if (!vCollision[i].iActivo)
            continue;
        
        //Revisar si el objeto ha entrado en el cuadro de colision
        if ( ((*iX + iWidth + iVx) >= vCollision[i].x) && (*iX - iWidth + iVx) <= ((vCollision[i].x + _lTileWidth)) && (*iY - iHeight - _fGravedad) <= ((vCollision[i].y + _lTileHeight)) && ((*iY + iHeight + *iVy) >= vCollision[i].y) )
        {
            this->checkForCollisions (iX, iY, iVx, iVy, iWidth, iHeight, vCollision [i].x, vCollision [i].y);
        }
        
        //Terminar de revisar al encontrar ambas colisiones
        if ((*_bCollisionY) && *_bCollisionX)
            break;
    }
    
    this->getValues (iVy);
}

void BoxCollision::getValues (int* iVy)
{
    if (*_bTouchUp)
        *iVy = _iTempVy;
}

void BoxCollision::checkForCollisions (int* iX, int* iY, int& iVx, int* iVy, int& iWidth, int& iHeight, int& iVectorX, int& iVectorY)
{
    //Dar un parametro de error por si la colision lo necesita, no queden tan exactas las colisiones
    const int parametroError = 5;
    
    //Revisar si ha colisionado con algun objeto en Y
    if ((*iX + iWidth - parametroError >= iVectorX) && (*iX - iWidth + parametroError <= (iVectorX + _lTileWidth)) )
    {
        if ( *iVy > 0 && (*iY < iVectorY) )
            this->checkForTopCollision (iY, iVy, iHeight, iVectorY);
        else
            if ( (*iVy <= 0) && (*iY >= iVectorY + _lTileHeight) && !*_bCollisionY )
                this->checkForFloorCollision (iY, iVy, iHeight, iVectorY);
    }
    
    int vY = *_bCollisionY ? 0 : *iVy;
    
    //Revisar si ha colisionado con algun objeto en X
    if ( !*_bCollisionX && (*iY - (iHeight - parametroError) <= iVectorY + _lTileHeight) && (*iY + (iHeight + parametroError) + vY  >= iVectorY) )
    {
        if ( iVx > 0 && (*iX <= iVectorX) )
            this->checkForRightCollision (iX, iVx, iWidth, iVectorX);
        else
            if ( iVx < 0 && (*iX >= iVectorX + _lTileWidth) )
                this->checkForLeftCollision (iX, iVx, iWidth, iVectorX);
    }
}

void BoxCollision::checkForFloorCollision (int* iY, int* iVy, int& iHeight, int& iVectorY)
{
    //printf ("\nEntra en el suelo:   %d", *iY);
    if ( (*iY - iHeight == (iVectorY + _lTileHeight) ) )
    {
        //Permitir que vuelva a saltar el player
        *_bTouchFloor = 1;
        *_bCollisionY = 1;
    }
    else
        if ( (*iY - iHeight - _fGravedad) <= (iVectorY + _lTileHeight) )
        {
            int iResta = (iVectorY + _lTileHeight) - (*iY - iHeight - _fGravedad);
            *iY -= _fGravedad;
            *iY += iResta;
            *_bCollisionY = 1;
        }
}

void BoxCollision::checkForTopCollision (int* iY, int* iVy, int& iHeight, int& iVectorY)
{
    //printf ("\nEntra en el techo:   %d", *iY);
    if ( (*iY + iHeight + *iVy ) > iVectorY )
    {
        int iSuma = iVectorY - (*iY + iHeight);
        
        if (_iTempVy)
            _iTempVy = iSuma < _iTempVy ? iSuma : _iTempVy;
        else
            _iTempVy = iSuma;
        
        *_bTouchUp = 1;
    }
}

void BoxCollision::checkForRightCollision (int* iX, int& iVx, int& iWidth, int& iVectorX)
{
    //printf ("\nEntra en el lado derecho:   %d", *iX);
    if ( (*iX + iWidth) == iVectorX )
    {
        *_bCollisionX = 1;
    }
    else
        if ( (*iX + iWidth + iVx) == iVectorX )
        {
            *iX += iVx;
            *_bCollisionX = 1;
        }
        else
        {
            int iResta = (*iX + iWidth + iVx) - iVectorX;
            *iX += iVx;
            *iX -= iResta;
            *_bCollisionX = 1;
        }
    
}

void BoxCollision::checkForLeftCollision (int* iX, int& iVx, int& iWidth, int& iVectorX)
{
    //printf ("\nEntra en el lado izquierdo:   %d", *iX);
    if ( (*iX - iWidth) == (iVectorX + _lTileWidth) )
    {
        *_bCollisionX = 1;
    }
    else
        if ( (*iX - iWidth + iVx) == (iVectorX + _lTileWidth) )
        {
            *iX += iVx;
            *_bCollisionX = 1;
        }
        else
        {
            int iResta = (iVectorX +_lTileWidth) - (*iX - iWidth + iVx);
            *iX += iVx;
            *iX += iResta;
            *_bCollisionX = 1;
        }
}

void BoxCollision::doCollisionWithTransparentPlatform (int* iX, int* iY, int& iWidth, int& iHeight, int& iVx, int* iVy, vector* vCollision)
{
    for (int i = 0; i < (_iMPoints * _iNPoints); ++i)
    {
        if (!vCollision [i].iActivo)
            continue;
        
        if ((*iX  > vCollision [i].x) && (*iX  < vCollision [i].x + _lTileWidth) && (*iY - iHeight - _fGravedad <= vCollision [i].y + _lTileHeight) && ((*iY ) >= vCollision [i].y + _lTileHeight - 20 ) && !vCollision [i].iToB)
        {
            if ((*iVy <= 0) && !*_bCollisionY && _iContador < 3)
				this->checkForFloorTransparentCollision(iX, iY, iVx, iVy, iWidth, iHeight, vCollision[i].x, vCollision[i].y);
        }
		if ((*iX  > vCollision[i].x) && (*iX  < vCollision[i].x + _lTileWidth) && (*iY <= vCollision[i].y + 20) && (*iY + iHeight + *iVy) >= vCollision[i].y && vCollision [i].iToB)
		{
			if (!*_bCollisionY)
				this->checkForTopTransparentCollision(iX, iY, iVx, iVy, iWidth, iHeight, vCollision[i].x, vCollision[i].y);
		}
        
        if (*_bCollisionY)
            break;
    }
    this->sumContador ();
}

void BoxCollision::checkForFloorTransparentCollision(int* iX, int* iY, int& iVx, int* iVy, int& iWidth, int& iHeight, int& iVectorX, int& iVectorY)
{
    //printf ("\nEntra en el suelo:   %d", *iY);
    if ( (*iY - iHeight == (iVectorY + _lTileHeight) ) )
    {
        //Permitir que vuelva a saltar el player
        *_bTouchFloor = 1;
        *_bCollisionY = 1;
        
        if (_oCronometro->getSecCount())
        {
            if (++_iContador == 3)
            {
                
                *_bCollisionY = 0;
            }
        }
        
    }
    else
        if ( (*iY - iHeight - _fGravedad) <= (iVectorY + _lTileHeight))
        {
            int iResta = (iVectorY + _lTileHeight) - (*iY - iHeight - _fGravedad);
            *iY -= _fGravedad;
            *iY += iResta;
            *_bCollisionY = 1;
        }
}

void BoxCollision::checkForTopTransparentCollision(int* iX, int* iY, int& iVx, int* iVy, int& iWidth, int& iHeight, int& iVectorX, int& iVectorY)
{
	if ((*iY + iHeight + *iVy) > iVectorY)
	{
		int iSuma = iVectorY - (*iY + iHeight);
        
		if (_iTempVy)
			_iTempVy = iSuma < _iTempVy ? iSuma : _iTempVy;
		else
			_iTempVy = iSuma;
        
		*_bTouchUp = 1;
	}
}

void BoxCollision::sumContador ()
{
    if (!*_bCollisionY && _iContador < 3)
        _iContador = 0;
    
    //Volver a reinicilizar el contador de las plataformas destructivas
    if (_iContador >= 3 && _oCronometro->getSecCount() && ++_iContador && _iContador == 4)
        _iContador = 0;
    
    printf ("Los segundos =  %d", _iContador);
}

void BoxCollision::resetValues ()
{
    _lTileWidth = 0;
    _lTileHeight = 0;
    _iMPoints = 0;
    _iNPoints = 0;
    _fGravedad = 0;
    _bCollisionX = 0;
    _bCollisionY = 0;
    _bTouchFloor = 0;
    _bTouchUp = 0;
    _iTempVy = 0;
}


