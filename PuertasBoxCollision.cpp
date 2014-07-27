//
//  PuertasBoxCollision.cpp
//  JuegoTequilero
//
//  Created by Max on 7/18/14.
//
//

#include "PuertasBoxCollision.h"


PuertasBoxCollision::PuertasBoxCollision (int& iPuertaIndex, int& iNPuertas, int* bInicio):  _iPuertaIndex (iPuertaIndex),
                                                                                               _iNPuertas (iNPuertas),
                                                                                               _bInicio (bInicio)
{
    _bInicio = bInicio;
}

PuertasBoxCollision::~PuertasBoxCollision ()
{
}

//Al inicio el jugador tendra que salir de la puerta, para volverla a habilitar
void PuertasBoxCollision::doStartCollisionsWith (int& iX, int& iY, int& iWidth, int& iHeight, objectResource* orPuertasPoints, std::string sPuerta)
{
    //Revisar para saber que el jugador ha salido de la puerta en el inicio de la escena, para que pueda volver a entrar en esta
    for (int i = 0; i < _iNPuertas; ++i)
    {
        printf ("\nEntras con la puerta:   %s", orPuertasPoints [i].sPuerta.c_str());
        
        //Revisar que haga la colision con la puerta correspondiente
        if (sPuerta != orPuertasPoints [i].sPuerta)
            continue;
        
        //Colision para saber que el jugador salio de la caja de la puerta
        if ((iX + iWidth < orPuertasPoints [i].x) || (iX - iWidth > (orPuertasPoints [i].x + orPuertasPoints [i].width)) || (iY - iHeight > (orPuertasPoints [i].y + orPuertasPoints [i].height)) || (iY + iHeight < orPuertasPoints [i].y))
        {
            *_bInicio = 0;
        }
    }
}

int PuertasBoxCollision::doCollisionsWith (int& iX, int& iY, int& iWidth, int& iHeight, objectResource* orPuertasPoints, int& iMapIndex, bool& bActionTouch)
{
    int iReturn = -1;
    
    for (int i = 0; i < _iNPuertas; ++i)
    {
        if ((iX - iWidth > orPuertasPoints[i].x) && (iX + iWidth < orPuertasPoints[i].x + orPuertasPoints[i].width) && (iY + iHeight <= orPuertasPoints[i].y + orPuertasPoints[i].height) && (iY - iHeight >= orPuertasPoints[i].y))
        {
            printf ("\nEntras con la puertax:   %s", orPuertasPoints [i].sPuerta.c_str());
            
            //Obtener el numero de mapa que sigue
            if (bActionTouch) iReturn  = this->checkPuerta (iMapIndex, orPuertasPoints [i].sPuerta);
            
            return iReturn;
        }
    }
    return -1;
}

int PuertasBoxCollision::doCollisionWithSidesToExit(int& iX, int& iY, int& iWidth, int& iHeight, objectResource* orPuertasPoints, int& iMapIndex, std::string sAparicion, int& iMapWidth)
{
    int iReturn = -1;
    
    if (iX - iWidth > iMapWidth)
        iReturn = ++iMapIndex;
    else
    if (iX + iWidth < 0)
        iReturn = --iMapIndex;
    
    return iReturn;
}

void PuertasBoxCollision::resetValues ()
{
    _iPuertaIndex = 0;
    _iNPuertas = 0;
}

int PuertasBoxCollision::checkPuerta (int& iMapIndex, std::string sPuerta)
{
    if (sPuerta == ("Entrada"))
        return --iMapIndex;
    
    if (sPuerta == "Salida")
        return ++iMapIndex;
    
    return 0;
}
