//
//  DrawRecursos.h
//  JuegoTequilero
//
//  Created by Max on 7/17/14.
//
//

#ifndef __JuegoTequilero__DrawRecursos__
#define __JuegoTequilero__DrawRecursos__

#include <iostream>

#include "ResourceObject.h"

#include "cocos2d.h"


class DrawRecursos
{
private:
    int _iNRecursos;
    
    void despintarRecurso (cocos2d::Sprite* spriteRecurso);
    
	void verRecurso(cocos2d::Sprite* spriteRecurso);
    
	void esconderRecurso(cocos2d::Sprite* spriteRecurso);
    
	void moverRecurso(cocos2d::Sprite* spriteRecurso, std::string tipo, int& x, int& y);
    
public:
    DrawRecursos ();
    
    ~DrawRecursos ();
    
    void setNRecursos (int& iNRecursos);
    
    int doCollisionsWith (int& iX, int& iY, int& iWidth, int& iHeight, objectResource* orResourcePoints);
    
	void doCollisionsWithEnemies(int& iX, int& iY, int& iWidth, int& iHeight, objectResource* orResourcePoints);
    
    void resetValues ();
};


#endif /* defined(__JuegoTequilero__DrawRecursos__) */
