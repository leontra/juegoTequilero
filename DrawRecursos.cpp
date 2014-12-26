//
//  DrawRecursos.cpp
//  JuegoTequilero
//
//  Created by Max on 7/17/14.
//
//

#include "DrawRecursos.h"


DrawRecursos::DrawRecursos() : _iNRecursos(0)
{
    
}


DrawRecursos::~DrawRecursos ()
{
    
}

void DrawRecursos::setNRecursos (int& iNRecursos)
{
    _iNRecursos = iNRecursos;
}

void DrawRecursos::doCollisionsWithEnemies(int& iX, int& iY, int& iWidth, int& iHeight, objectResource* orResourcePoints)
{
	for (int i = 0; i < _iNRecursos; ++i)
	{
		if (!orResourcePoints[i].iActivo)
			continue;
        
		if (orResourcePoints[i].iType == 5){
			if ((iX + iWidth >= orResourcePoints[i].x) && (iX - iWidth <= orResourcePoints[i].x + orResourcePoints[i].width) && (iY - iHeight <= orResourcePoints[i].y + orResourcePoints[i].height) && (iY + iHeight >= orResourcePoints[i].y))
			{
                
			}
		}
	}
}
int DrawRecursos::doCollisionsWith (int& iX, int& iY, int& iWidth, int& iHeight, objectResource* orResourcePoints)
{
    int iReturn = 0;
    
	for (int i = 0; i < _iNRecursos; ++i)
	{
		if (!orResourcePoints[i].iActivo)
			continue;
		if (orResourcePoints[i].iType == 7)
		{
			if ((iX + iWidth < orResourcePoints[i].x) || (iX - iWidth >(orResourcePoints[i].x + orResourcePoints[i].width)) || (iY - iHeight > (orResourcePoints[i].y + orResourcePoints[i].height)) || (iY + iHeight < orResourcePoints[i].y))
			{
				orResourcePoints[i].iActivo = 0;
				this->esconderRecurso(orResourcePoints[i].spriteResource);
			}
		}
        
		if (orResourcePoints[i].iType == 6)
		{
			if ((iX + iWidth >= orResourcePoints[i].x) && (iX - iWidth <= orResourcePoints[i].x + orResourcePoints[i].width) && (iY - iHeight <= orResourcePoints[i].y + orResourcePoints[i].height) && (iY + iHeight >= orResourcePoints[i].y))
			{
				orResourcePoints[5].iActivo = 1;
				this->verRecurso(orResourcePoints[5].spriteResource);
                iReturn = 1;
			}
		}
        
		if (orResourcePoints[i].iType == 8 || orResourcePoints[i].iType == 9 || orResourcePoints[i].iType == 10 || orResourcePoints[i].iType == 11)
		{
			if ((iX + iWidth >= orResourcePoints[i].x) && (iX - iWidth <= orResourcePoints[i].x + orResourcePoints[i].width) && (iY - iHeight <= orResourcePoints[i].y + orResourcePoints[i].height) && (iY + iHeight >= orResourcePoints[i].y))
			{
				this->moverRecurso(orResourcePoints[i].spriteResource, orResourcePoints[i].name, orResourcePoints[i].x, orResourcePoints[i].y);
                iReturn = 1;
			}
		}
        
		if (orResourcePoints[i].iType == 3 || orResourcePoints[i].iType == 4 || orResourcePoints[i].iType == 5 || orResourcePoints[i].iType == 6 || orResourcePoints[i].iType == 7 || orResourcePoints[i].iType == 8 || orResourcePoints[i].iType == 9 || orResourcePoints[i].iType == 10 || orResourcePoints[i].iType == 11)
			continue;
        
        if ((iX + iWidth >= orResourcePoints[i].x) && (iX - iWidth <= orResourcePoints[i].x + orResourcePoints[i].width) && (iY - iHeight <= orResourcePoints[i].y + orResourcePoints[i].height) && (iY + iHeight >= orResourcePoints[i].y))
        {
            //Desactivar el recurso
            orResourcePoints [i].iActivo = 0;
            
            //Quitar la imagen de la pantalla y volver nulo el sprite
            this->despintarRecurso (orResourcePoints [i].spriteResource);
            iReturn = 1;
        }
    }
    
    return iReturn;
}

void DrawRecursos::verRecurso(cocos2d::Sprite* spriteRecurso)
{
	spriteRecurso->setVisible(true);
}

void DrawRecursos::esconderRecurso(cocos2d::Sprite* spriteRecurso)
{
	spriteRecurso->setVisible(false);
}

void DrawRecursos::moverRecurso(cocos2d::Sprite* spriteRecurso, std::string tipo , int& posx, int& posy)
{
	if (tipo == "Logo1")
	{
		posx = 792;
		posy = 480;
		spriteRecurso->setPositionX(792);
		spriteRecurso->setPositionY(480);
	}
	if (tipo == "Logo2")
	{
		posx = 792;
		posy = 400;
		spriteRecurso->setPositionX(792);
		spriteRecurso->setPositionY(400);
	}
	if (tipo == "Logo3")
	{
		posx = 864;
		posy = 480;
		spriteRecurso->setPositionX(864);
		spriteRecurso->setPositionY(480);
	}
	if (tipo == "Logo4")
	{
		posx = 792;
		posy = 400;
		spriteRecurso->setPositionX(864);
		spriteRecurso->setPositionY(400);
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

