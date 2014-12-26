//
//  GameBuffering.h
//  JuegoTequilero
//
//  Created by Max on 11/4/14.
//
// Clase para inicializar los recursos, puertas, compañeros y parte del background del juego.
// Usar al principio de la aplicacion, durante el splash.
//
//

#ifndef __JuegoTequilero__GameBuffering__
#define __JuegoTequilero__GameBuffering__

#include <stdio.h>
#include "ResourcesBuffer.h"
#include "DoorsBuffer.h"
#include "RoomsWorld.h"
#include "MatesBuffer.h"



class GameBuffering
{
    
public:
    GameBuffering( );
    
    ~GameBuffering( );
    
    void initGameBuffers( );
    
};

#endif /* defined(__JuegoTequilero__GameBuffering__) */
