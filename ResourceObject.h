//
//  ResourceObject.h
//  JuegoTequilero
//
//  Created by Max on 7/13/14.
//
//

#ifndef JuegoTequilero_ResourceObject_h
#define JuegoTequilero_ResourceObject_h

#include "ObjectKey.h"
#include "ObjectBottle.h"
#include "ObjectLogo.h"
#include "ObjectTool.h"
#include "ObjectLetter.h"

struct _ObjectResource
{
    ObjectKey* objectKey;
    ObjectBottle* objectBottle;
    ObjectLogo* objectLogo;
    ObjectTool* objectTool;
    ObjectLetter* objectLetter;
    
    int* hash;
    int* type;
    int* state;
    
    _ObjectResource( ):  objectKey( 0 ),
                                    objectBottle( 0 ),
                                    objectLogo( 0 ),
                                    objectTool( 0 ),
                                    objectLetter( 0 )
    { }
    
    void setKey( ObjectKey* _objectKey, int& _hash, int& _type ) //Type 2
    {
        objectKey = _objectKey;
        setAttributes( _hash, _type, _objectKey->getState( ) );
    }
    
    void setBottle( ObjectBottle* _objectBottle, int& _hash, int& _type ) //Type 1
    {
        objectBottle = _objectBottle;
        setAttributes( _hash, _type, _objectBottle->getState( ) );
    }
    
    void setLogo( ObjectLogo* _objectLogo, int& _hash, int& _type ) //Type 5
    {
        objectLogo = _objectLogo;
        setAttributes( _hash, _type, _objectLogo->getState( ) );
    }
    
    void setTool( ObjectTool* _objectTool, int& _hash, int& _type ) //Type 3
    {
        objectTool = _objectTool;
        setAttributes( _hash, _type, _objectTool->getState( ) );
    }
    
    void setLetter( ObjectLetter* _objectLetter, int& _hash, int& _type ) //Type 4
    {
        objectLetter = _objectLetter;
        setAttributes( _hash, _type, _objectLetter->getState( ) );
    }
    
    void setAttributes( int& _hash, int& _type, int& _state )
    {
        hash = new int( 0 );
        *hash = _hash;
        type = new int( 0 );
        *type = _type;
        state = new int( 0 );
        *state = _state;
    }
    
    int& getType( )
    {
        return *type;
    }
    
    ObjectBottle* getObjectBottle( )
    {
        return objectBottle;
    }
    
    ObjectKey* getObjectKey( )
    {
        return objectKey;
    }
    
    ObjectTool* getObjectTool( )
    {
        return objectTool;
    }
    
    ObjectLetter* getObjectLetter( )
    {
        return objectLetter;
    }
    
    ObjectLogo* getObjectLogo( )
    {
        return objectLogo;
    }
    
    int& getState( )
    {
        return *state;
    }
    
};

typedef _ObjectResource ObjectResource;

#endif
