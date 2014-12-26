

//  BoxCollision.cpp
//  JuegoTequilero
//
//  Created by Max on 7/11/14.
//
//

#include "BoxCollision.h"

BoxCollision::BoxCollision( ) :       _iMapping( 0 ),
                                                _iMPoints( _iMapping ),
                                                _iNPoints( _iMapping ),
                                                _lTileWidth( _iMapping ),
                                                _lTileHeight( _iMapping ),
                                                _fGravedad( 0 ),
                                                _bCollisionX( 0 ),
                                                _bCollisionY( 0 ),
                                                _bTouchFloor( 0 ),
                                                _bTouchUp( 0 ),
                                                _iTempVy( 0 ),
                                                _iContador( 0 ),
                                                _iDuracionPlataforma( 0 ),
                                                _iTotalPoints( 0 ),
                                                _iLastMapping( 0 ),
                                                _iBreakPlatform( 0 )
{ }

BoxCollision::BoxCollision(int& tileWidth, int& tileHeight, int& iMPoints, int& iNPoints, float& fGravedad, int* bCollisionX, int* bCollisionY, int* bTouchFloor, int* bTouchUp) :
                                                    _lTileWidth( tileWidth ),
                                                    _lTileHeight( tileHeight ),
                                                    _iMPoints( iMPoints ),
                                                    _iNPoints( iNPoints ),
                                                    _fGravedad( fGravedad ),
                                                    _bCollisionX( 0 ),
                                                    _bCollisionY( 0 ),
                                                    _bTouchFloor( 0 ),
                                                    _bTouchUp( 0 ),
                                                    _iTempVy( 0 ),
                                                    _iContador( 0 ),
                                                    _iDuracionPlataforma( 2 ),
                                                    _iMapping( -1 ),
                                                    _iTotalPoints( iNPoints * iMPoints ),
                                                    _iLastMapping( 0 ),
                                                    _iBreakPlatform( 0 )
{
	_bCollisionX = bCollisionX;
	_bCollisionY = bCollisionY;
	_bTouchFloor = bTouchFloor;
	_bTouchUp = bTouchUp;
    
    _aiSumaParaEncontrarTile[ 0 ] =  -1;
    _aiSumaParaEncontrarTile[ 1 ] = -_iMPoints;
    _aiSumaParaEncontrarTile[ 2 ] = 1;
    _aiSumaParaEncontrarTile[ 3 ] = _iMPoints;
    
	_oCronometro = new Milliseconds;
    _oCronometro->setPlatformDuration( _iDuracionPlataforma );
}

void BoxCollision::doMapping( const int& x, const int& y )
{
    int yMap = y  / _lTileHeight;
    yMap = ( yMap * -1 ) + ( _iNPoints - 1 );
    int xMap = x / _lTileWidth;
    _iMapping = ( yMap * _iMPoints ) + xMap;
}

void BoxCollision::doCollisionWithRegularPlatforms( int* iX, int* iY, int& iWidth, int& iHeight, int& iVx, int* iVy, vector* vCollision )
{
	//_iTempVy = 0;
    
    //printf( "\nTotal de puntos en X  =  %d", _iMPoints );
	
    //int iMapeo = doMapeo( *iX, *iY );
	//int iMapeoCollision = iMapeo;
    
    //Agregar al arreglo, los cuatro puntos del cuadrado del personaje
    //IzquierdaArriba, DerechaArriba, IzquierdaAbajo, DerechaAbajo
    //std::vector< int > mapeoPoints = { doMapeo( *iX, *iY ) }; //, doMapeo( *iX + iWidth, *iY + iHeight ), doMapeo( *iX - iWidth, *iY - iHeight ), doMapeo( *iX + iWidth, *iY - iHeight ) };
    
    //Sumar para encontrar el tile del lado derecho, izquierdo, arriba y abajo
    //int sumaParaEncontrarTile[ 8 ] = { -1, -_iMPoints, -_iMPoints, 1, -1, _iMPoints, _iMPoints, 1 };
    
    if( _iMapping < 0 || _iMapping > _iTotalPoints )
    {
        printf( "\nSe salio:   %d", _iLastMapping );
        if( !*_bCollisionY && ( *iVy <= 0 ) && ( *iY >= vCollision[ _iLastMapping +_iMPoints ].y + _lTileHeight ) )
            this->checkForFloorCollision( iY, iVy, iHeight, vCollision[ _iLastMapping +_iMPoints ].y );
        return;
    }
    //Acomodar los arreglos por orden
    //std::sort( mapeoPoints.begin( ), mapeoPoints.end( ) );
    
    //int index = 0;
    //int indexSumaMapeo = 0;
    //Revisar cuantos diferentes puntos hay de mapeo
    //std::vector< int >::iterator it;
    //for( it = mapeoPoints.begin( ); it != mapeoPoints.end( ); ++it, ++index )
    //{
        //if( *it < 0 || *it > _iTotalPoints )
           // continue;
        
        for( int i = 0; i < 4; ++i )
        {
            int actualMapeo = 0;
            
            //Obtener el mapeo del tile a probar; Izquierda, arriba, derecha, abajo
            actualMapeo = _iMapping + _aiSumaParaEncontrarTile[ i ];
            
            //Revisar que este dentro de los limites
            if( actualMapeo < 0 || actualMapeo > _iTotalPoints )
            {
                continue;
            }
            
            //Revisar que no se este saltando de fila hacia atras
            if( _aiSumaParaEncontrarTile[ i ] == -1 && _iMapping % _iMPoints == 0 )
                continue;
            
            //Revisar que no se este saltando de fila hacia adelante
            if( _aiSumaParaEncontrarTile[ i ] == 1 && actualMapeo % _iMPoints == 0 )
                continue;
            
            //Revisar si está activo
            if( vCollision[ actualMapeo ].iActivo != 1 )
                continue;
            
            if( i == 3 )
            {
                if( !*_bCollisionY && ( *iVy <= 0 ) && ( *iY >= vCollision[ actualMapeo ].y + _lTileHeight ) )
                    this->checkForFloorCollision( iY, iVy, iHeight, vCollision[ actualMapeo ].y );
            }
            else if( i == 2 )
            {
                if( !*_bCollisionX && iVx > 0 && ( *iX <= vCollision[ actualMapeo ].x ) )
                    this->checkForRightCollision( iX, iVx, iWidth, vCollision[ actualMapeo ].x);
            }
            else if( i )
            {
                if( !*_bCollisionY && *iVy > 0 && ( *iY < vCollision[ actualMapeo ].y ) )
                    this->checkForTopCollision( iY, iVy, iHeight, vCollision[ actualMapeo ].y );
            }
            else if( !i )
            {
                if( !*_bCollisionX && iVx < 0 && ( *iX >= vCollision[ actualMapeo ].x + _lTileWidth ) )
                    this->checkForLeftCollision( iX, iVx, iWidth, vCollision[ actualMapeo ].x );
            }
        }
    _iLastMapping = _iMapping;
        
        /*
        //Revisar para los cuatro coordenadas
        for( int i = 0; i < 2; ++i , ++indexSumaMapeo )
        {
            int actualMapeo = 0;
            
            //Sumar para encontrar el tile a colisionar
            actualMapeo = *it + sumaParaEncontrarTile[ indexSumaMapeo ];
            
            if( sumaParaEncontrarTile[ indexSumaMapeo ] == -1 && *it % _iMPoints == 0 )
                continue;
            
            if( sumaParaEncontrarTile[ indexSumaMapeo ] == 1 && actualMapeo % _iMPoints == 0 )
                continue;
            
            //Revisar si se sale de los limites
            if( actualMapeo < 0 || actualMapeo > iTotalPoints )
                continue;
            
            //Revisar si está activo
            if( vCollision[ actualMapeo ].iActivo != 1 )
                continue;
            
            printf( "\nColisionando =  %d", actualMapeo );
            */
            /*
            this->getValues( iVy );
                
            checkForCollisions( iX, iY, iVx, iVy, iWidth, iHeight, vCollision[ actualMapeo ].x, vCollision[ actualMapeo ].y );
             */
            /*
            if( index == 3 )
            {
                if( !*_bCollisionY && ( *iVy <= 0 ) && ( *iY >= vCollision[ actualMapeo ].y + _lTileHeight ) )
                    this->checkForFloorCollision( iY, iVy, iHeight, vCollision[ actualMapeo ].y );
                
                if( !*_bCollisionX && iVx > 0 && ( *iX <= vCollision[ actualMapeo ].x ) )
                    this->checkForRightCollision( iX, iVx, iWidth, vCollision[ actualMapeo ].x);
            }
            else if( index == 2 )
            {
                if( !*_bCollisionX && iVx < 0 && ( *iX >= vCollision[ actualMapeo ].x + _lTileWidth ) )
                    this->checkForLeftCollision( iX, iVx, iWidth, vCollision[ actualMapeo ].x );
                
                if( !*_bCollisionY && ( *iVy <= 0 ) && ( *iY >= vCollision[ actualMapeo ].y + _lTileHeight ) )
                    this->checkForFloorCollision( iY, iVy, iHeight, vCollision[ actualMapeo ].y );
            }
            else if( index )
            {
                if( !*_bCollisionY && *iVy > 0 && ( *iY < vCollision[ actualMapeo ].y ) )
                    this->checkForTopCollision( iY, iVy, iHeight, vCollision[ actualMapeo ].y );
                
                if( !*_bCollisionX && iVx > 0 && ( *iX <= vCollision[ actualMapeo ].x ) )
                    this->checkForRightCollision( iX, iVx, iWidth, vCollision[ actualMapeo ].x);
            }
            else if( !index )
            {
                if( !*_bCollisionY && *iVy > 0 && ( *iY < vCollision[ actualMapeo ].y ) )
                    this->checkForTopCollision( iY, iVy, iHeight, vCollision[ actualMapeo ].y );
                
                if( !*_bCollisionX && iVx < 0 && ( *iX >= vCollision[ actualMapeo ].x + _lTileWidth ) )
                    this->checkForLeftCollision( iX, iVx, iWidth, vCollision[ actualMapeo ].x );
            }
             
        }
        */
    //}
}



void BoxCollision::getValues(int* iVy)
{
	if (*_bTouchUp)
		*iVy = _iTempVy;
}

/*
void BoxCollision::checkForCollisions(int* iX, int* iY, int& iVx, int* iVy, int& iWidth, int& iHeight, int& iVectorX, int& iVectorY)
{
	//Dar un parametro de error por si la colision lo necesita, no queden tan exactas las colisiones
	const int parametroError = 0;
    
	//Revisar si ha colisionado con algun objeto en Y
	if( !*_bCollisionY && (*iX  - parametroError >= iVectorX) && (*iX  + parametroError <= (iVectorX + _lTileWidth)))
	{
		if (*iVy > 0 && (*iY < iVectorY))
			this->checkForTopCollision(iY, iVy, iHeight, iVectorY);
		else
            if ((*iVy <= 0) && (*iY >= iVectorY + _lTileHeight) && !*_bCollisionY)
                this->checkForFloorCollision(iY, iVy, iHeight, iVectorY);
	}
    
	int vY = *_bCollisionY ? 0 : *iVy;
    
	//Revisar si ha colisionado con algun objeto en X
	if( !*_bCollisionX && (*iY - (iHeight - parametroError) <= iVectorY + _lTileHeight) && (*iY + (iHeight + parametroError) + vY >= iVectorY))
	{
		if (iVx > 0 && (*iX <= iVectorX))
			this->checkForRightCollision(iX, iVx, iWidth, iVectorX);
		else
            if (iVx < 0 && (*iX >= iVectorX + _lTileWidth))
                this->checkForLeftCollision(iX, iVx, iWidth, iVectorX);
	}
}
*/

void BoxCollision::checkForFloorCollision(int* iY, int* iVy, int& iHeight, int& iVectorY)
{
	//printf ("\nEntra en el suelo:   %d", *iY);
	if ((*iY - iHeight == (iVectorY + _lTileHeight)))
	{
		//Permitir que vuelva a saltar el player
		*_bTouchFloor = 1;
		*_bCollisionY = 1;
	}
	else
        if ((*iY - iHeight - _fGravedad) <= (iVectorY + _lTileHeight))
        {
            int iResta = (iVectorY + _lTileHeight) - (*iY - iHeight - _fGravedad);
            *iY -= _fGravedad;
            *iY += iResta;
            *_bCollisionY = 1;
        }
}

void BoxCollision::checkForTopCollision(int* iY, int* iVy, int& iHeight, int& iVectorY)
{
	//printf ("\nEntra en el techo:   %d", *iY);
	if ((*iY + iHeight + *iVy) > iVectorY)
	{
		int iSuma = iVectorY - (*iY + iHeight);
        
		if (_iTempVy)
			_iTempVy = iSuma < _iTempVy ? iSuma : _iTempVy;
		else
		{
			_iTempVy = iSuma;
		}
        
		*_bTouchUp = 1;
	}
}

void BoxCollision::checkForRightCollision( int* iX, int& iVx, int& iWidth, int& iVectorX )
{
	//printf ("\nEntra en el lado derecho:   %d", *iX);
	if( ( *iX + iWidth) == iVectorX )
	{
		*_bCollisionX = 1;
	}
	else
        if( ( *iX + iWidth + iVx ) == iVectorX )
        {
            *iX += iVx;
            *_bCollisionX = 1;
        }
        else if( ( *iX + iWidth + iVx ) > iVectorX )
        {
            int iResta = (*iX + iWidth + iVx) - iVectorX;
            *iX += iVx;
            *iX -= iResta;
            *_bCollisionX = 1;
        }
    
}

void BoxCollision::checkForLeftCollision( int* iX, int& iVx, int& iWidth, int& iVectorX )
{
	//printf ("\nEntra en el lado izquierdo:   %d", *iX);
	if( ( *iX - iWidth ) == ( iVectorX + _lTileWidth ) )
	{
		*_bCollisionX = 1;
	}
	else
        if( ( *iX - iWidth + iVx ) == ( iVectorX + _lTileWidth ) )
        {
            *iX += iVx;
            *_bCollisionX = 1;
        }
        else if( ( *iX - iWidth + iVx ) < ( iVectorX + _lTileWidth ) )
        {
            int iResta = ( iVectorX + _lTileWidth ) - ( *iX - iWidth + iVx );
            *iX += iVx;
            *iX += iResta;
            *_bCollisionX = 1;
        }
}

void BoxCollision::doCollisionWithBreakablePlatforms( int* iY, int& iHeight, int* iVy, vector* vCollision )
{
    if( _iMapping < 0 || _iMapping > _iTotalPoints )
        return;
    
    int actualMapeo = _iMapping + _iMPoints;
    
    //Revisar que este dentro de los limites
    if( actualMapeo < 0 || actualMapeo > _iTotalPoints )
        return;
    
    //Revisar si está activo
    if( vCollision[ actualMapeo ].iActivo != 1 )
        return;
    
    if( !*_bCollisionY && ( *iVy <= 0 ) && ( *iY >= vCollision[ actualMapeo ].y + _lTileHeight ) )
        this->testBreakablePlatformsCollisions( iY, iVy, iHeight, vCollision[ actualMapeo ].y );
        //this->checkForFloorCollision( iY, iVy, iHeight, vCollision[ actualMapeo ].y );

    
    /*
	for (int i = 0; i < (_iMPoints * _iNPoints); ++i)
	{
		if (!vCollision[i].iActivo)
			continue;
     
		if ((*iX  > vCollision[i].x) && (*iX  < vCollision[i].x + _lTileWidth) && (*iY - iHeight - _fGravedad <= vCollision[i].y + _lTileHeight) && ((*iY) >= vCollision[i].y + _lTileHeight - 20) && !vCollision[i].iToB)
		{
			if ((*iVy <= 0) && !*_bCollisionY && _iContador < _iDuracionPlataforma)
				this->checkForFloorTransparentCollision(iX, iY, iVx, iVy, iWidth, iHeight, vCollision[i].x, vCollision[i].y);
		}
		if ((*iX  > vCollision[i].x) && (*iX  < vCollision[i].x + _lTileWidth) && (*iY <= vCollision[i].y + 20) && (*iY + iHeight + *iVy) >= vCollision[i].y && vCollision[i].iToB)
		{
			if (!*_bCollisionY)
				this->checkForTopTransparentCollision(iX, iY, iVx, iVy, iWidth, iHeight, vCollision[i].x, vCollision[i].y);
		}
        
		if (*_bCollisionY)
			break;
	}
	this->sumContador();
     */
}

void BoxCollision::testBreakablePlatformsCollisions( int* iY, int* iVy, int& iHeight, int& iVectorY )
{
	//printf ("\nEntra en el suelo:   %d", *iY);
	if( !_iBreakPlatform && ( *iY - iHeight == ( iVectorY + _lTileHeight ) ) )
	{
		//Permitir que vuelva a saltar el player
        if( _oCronometro->getSecCount( ) && ++_iContador )
        {
            if( _iContador >= _iDuracionPlataforma )
            {
                _iBreakPlatform = 1;
                *_bCollisionY = 0;
            }
        }
    
        if( _iContador < _iDuracionPlataforma )
        {
            *_bTouchFloor = 1;
            *_bCollisionY = 1;
        }
        
	}
    else if( _iBreakPlatform && _iContador >= _iDuracionPlataforma )
    {
        sumContador( );
    }
	else if( ( *iY - iHeight - _fGravedad ) <= ( iVectorY + _lTileHeight ) )
    {
        _iContador = 0;
        int iResta = ( iVectorY + _lTileHeight ) - ( *iY - iHeight - _fGravedad );
        *iY -= _fGravedad;
        *iY += iResta;
        *_bCollisionY = 1;
    }
}

void BoxCollision::sumContador( )
{
    
    //Volver a reinicilizar el contador de las plataformas destructivas
    if( _iBreakPlatform && _oCronometro->getSecCount( ) && ++_iContador && _iContador >= _iDuracionPlataforma + 1 )
    {
        _iBreakPlatform = 0;
        _iContador = 0;
    }
    printf( "\nLos segundos = %d  y la duracion = %d", _iContador, _iDuracionPlataforma );
}


void BoxCollision::doCollisionWithHardTopPlatforms( int* iY, int& iHeight, int* iVy, vector* vCollision )
{
    if( _iMapping < 0 || _iMapping > _iTotalPoints )
        return;
    
    int actualMapeo = _iMapping + _iMPoints;
    
    //Revisar que este dentro de los limites
    if( actualMapeo < 0 || actualMapeo > _iTotalPoints )
        return;
    
    //Revisar si está activo
    if( vCollision[ actualMapeo ].iActivo != 1 )
        return;
    
    if( !*_bCollisionY && ( *iVy <= 0 ) && ( *iY >= vCollision[ actualMapeo ].y +  _lTileHeight ) )
        this->checkForFloorCollision( iY, iVy, iHeight, vCollision[ actualMapeo ].y );
}

void BoxCollision::doCollisionWithHardBottomPlatforms( int* iY, int& iHeight, int* iVy, vector* vCollision )
{
    if( _iMapping < 0 || _iMapping > _iTotalPoints )
        return;
    
    int actualMapeo = _iMapping - _iMPoints;
    
    //Revisar que este dentro de los limites
    if( actualMapeo < 0 || actualMapeo > _iTotalPoints )
        return;
    
    //Revisar si está activo
    if( vCollision[ actualMapeo ].iActivo != 1 )
        return;
    
    if( !*_bCollisionY && *iVy > 0 && ( *iY < vCollision[ actualMapeo ].y ) )
        this->checkForTopCollision( iY, iVy, iHeight, vCollision[ actualMapeo ].y );
}

void BoxCollision::resetValues( )
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

BoxCollision::~BoxCollision( )
{
    this->resetValues( );
    delete _oCronometro;
}


