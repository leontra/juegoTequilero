//
//  Vector.h
//  JuegoTequilero
//
//  Created by Max on 7/11/14.
//
//

#ifndef JuegoTequilero_Vector_h
#define JuegoTequilero_Vector_h

struct _Vector
{
    int x;
    int y;
    int iActivo;
    
    _Vector( ):   x( 0 ),
                        y( 0 ),
                        iActivo( 0 )
    { }
    
    _Vector( const int& x, const int& y, int& iActivo ):    x( x ),
                                                                y( y ),
                                                                iActivo( iActivo )
    { }
};

typedef _Vector vector;

#endif
