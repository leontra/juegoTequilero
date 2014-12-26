//
//  RoomsWorld.h
//  JuegoTequilero
//
//  Created by Max on 10/17/14.
//
//

#ifndef JuegoTequilero_RoomsWorld_h
#define JuegoTequilero_RoomsWorld_h

////Definir el total de recursos por cada cuarto
struct _RoomsWorld
{
    const int iNRooms = 12;
    
    int aiRoomsWorld[ 12 ] =
    {
        0,
        2,
        2,
        3,
        3,
        3,
        2,
        1,
        3,
        2,
        2,
        2
    };
    
};

typedef _RoomsWorld RoomsWorld;

#endif
