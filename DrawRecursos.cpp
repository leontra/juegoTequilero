//
//  DrawRecursos.cpp
//  JuegoTequilero
//
//  Created by Max on 7/17/14.
//
//

#include "DrawRecursos.h"


DrawRecursos::DrawRecursos (): _iNRecursos (0)
{
    
}

DrawRecursos::~DrawRecursos ()
{
    
}

void DrawRecursos::setNRecursos (int& iNRecursos)
{
    _iNRecursos = iNRecursos;
}

void DrawRecursos::doCollisionsWith (int& iX, int& iY, int& iWidth, int& iHeight, objectResource* orResourcePoints)
{
    for (int i = 0; i < _iNRecursos; ++i)
    {
        if (!orResourcePoints [i].iActivo)
            continue;
        
        if ((iX + iWidth >= orResourcePoints[i].x) && (iX - iWidth <= orResourcePoints[i].x + orResourcePoints[i].width) && (iY - iHeight <= orResourcePoints[i].y + orResourcePoints[i].height) && (iY + iHeight >= orResourcePoints[i].y))
        {
            //Desactivar el recurso
            orResourcePoints [i].iActivo = 0;
            
            //Quitar la imagen de la pantalla y volver nulo el sprite
            this->despintarRecurso (orResourcePoints [i].spriteResource);
        }
    }
}

void DrawRecursos::despintarRecurso (cocos2d::Sprite* spriteRecurso)
{
    spriteRecurso->removeFromParent ();
    spriteRecurso = 0;
}

void DrawRecursos::resetValues ()
{
    _iNRecursos = 0;
}

