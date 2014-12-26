//
//  ResourcesBuffer.cpp
//  JuegoTequilero
//
//  Created by Max on 10/17/14.
//
//

#include <ResourcesBuffer.h>

ResourcesBuffer::ResourcesBuffer( ):  _iNMaxResources( 0 ),
                                                        _iNTotalKeysRoom( 0 ),
                                                        iBottle( 0 ),
                                                        iKey( 0 ),
                                                        iLogo( 0 ),
                                                        iLetter( 0 ),
                                                        iTool( 0 ),
                                                        _aiNResourcesRoom( nullptr ),
                                                        _bfInit( 0 ),
                                                        _iNTotalKeys( 0 ),
                                                        _iNTotalTools( 0 ),
                                                        _iMaxTotalKeys( 2 ),
                                                        _iMaxTotalTools( 2 ),
                                                        _iNTotalLogos( 0 ),
                                                        _bTestLetters( 0 )
{
    for( int i = 0; i  < sizeof( keysCollectedIndex ) / sizeof(int); ++i )
        keysCollectedIndex[ i ] = -1;
    
    for( int i = 0; i  < sizeof( toolsCollectedIndex ) / sizeof(int); ++i )
        toolsCollectedIndex[ i ] = -1;
    //printf( "Se ha Iniciado el ResourceBuffer\n" );
}

void ResourcesBuffer::initResourcesArray( int totalResources )
{
    _aiNResourcesRoom = new( std::nothrow ) int[ totalResources ];
    for( int i = 0; i < totalResources; ++i )
        _aiNResourcesRoom[ i ] = 0;
}

void ResourcesBuffer::setRoomBuffer( cocos2d::TMXTiledMap& tileMap, const int& roomIndex, RoomsWorld& roomsWorld )
{
    //Arreglo para saber el numero de recursos por room
    int roomResources = roomsWorld.aiRoomsWorld[ roomIndex ];
    _aiNResourcesRoom[ roomIndex ] = roomResources;

    //Vector de vectores, para localizar los objetos de cada nivel
    std::vector< ObjectResource* > roomBuffer = *new std::vector< ObjectResource* >;
        
    //Obtener todos los grupos de cada mapa
    cocos2d::Vector< cocos2d::TMXObjectGroup* > tileGroups = tileMap.getObjectGroups( );
    
    int iTotalResourcesPerRoom = roomResources;
    if( !roomIndex ) iTotalResourcesPerRoom = 0;
        
        //Iterar sobre cada grupo
        for( cocos2d::TMXObjectGroup* objectGroup : tileGroups )
        {
            //Terminar si el objeto no es un objeto
            if(  objectGroup->getProperty( "id" ).asInt( ) != 1 )
                continue;
            
            //Obtener objeto
            cocos2d::ValueVector objects = objectGroup->getObjects( );
            
            //Revisar por cada propiedad del objeto
            for( cocos2d::Value& object : objects )
            {
                cocos2d::ValueMap properties = object.asValueMap( );

                std::string name = properties.at( "name" ).asString( );
                //std::string nameExtension = properties.at( "suffix" ).asString( );
                std::string nameExtension = "png";
                int type = properties.at( "type" ).asInt( );
                int x = properties.at( "x" ).asFloat( );
                int y = properties.at( "y" ).asFloat( );
                int width = properties.at( "width" ).asFloat( );
                int height = properties.at( "height" ).asFloat( );
                
                //Evitar errores
                if( !object.isNull( ) )
                {
                    ObjectResource* oLevel = new ObjectResource(  );
                    --iTotalResourcesPerRoom;
                    
                    switch( type )
                    {
                        case 1:
                        {
                            ObjectBottle* bottle = new ObjectBottle( x, y, width, height );
                            bottle->setObject( iBottle, type, roomIndex );
                            bottle->setSpriteName( name, nameExtension );
                            bottle->setStateUpgrade( 0, 2.5 );
                            
                            oLevel->setBottle( bottle, iBottle, type );
                            _apBottles.push_back( bottle );
                            ++iBottle;
                        }
                            break;
                            
                        case 2:
                        {
                            ObjectKey* key = new ObjectKey( x, y, width, height );
                            key->setObject( iKey, type, roomIndex );
                            key->setSpriteName( name, nameExtension );
                            key->setStateUpgrade( 0, 4 );
                            key->setConexion( properties.at( "idLlave" ).asInt( ) );
                            
                            oLevel->setKey( key, iKey, type );
                            _apKeys.push_back( key );
                            ++iKey;
                        }
                            break;
                            
                        case 3:
                        {
                            ObjectTool* tool = new ObjectTool( x, y, width, height );
                            tool->setObject( iTool, type, roomIndex );
                            tool->setSpriteName( name, nameExtension );
                            tool->setStateUpgrade( 0, 25 );
                            tool->setConexion( properties.at( "idHerramienta" ).asInt( ) );
                            
                            oLevel->setTool( tool, iTool, type );
                            _apTools.push_back( tool );
                            ++iTool;
                        }
                            break;
                            
                        case 4:
                        {
                            ObjectLetter* letter = new ObjectLetter( x, y, width, height );
                            letter->setObject( iLetter, type, roomIndex );
                            letter->setSpriteName( name, nameExtension );
                            letter->setStateUpgrade( 0, 20 );
                            letter->setConexion( properties.at( "idLetra" ).asInt( ) );
                            letter->setLetra( properties.at( "sLetra" ).asString( ) );
                            
                            oLevel->setLetter( letter, iLetter, type );
                            _apLetters.push_back( letter );
                            ++iLetter;
                        }
                            break;
                            
                        case 5:
                        {
                            ObjectLogo* logo = new ObjectLogo( x, y, width, height );
                            logo->setObject( iLogo, type, roomIndex );
                            logo->setSpriteName( name, nameExtension );
                            logo->setStateUpgrade( 0, 5 );
                            logo->setConexion( properties.at( "idLogo" ).asInt( ) );
                            
                            oLevel->setLogo( logo, iLogo, type );
                            _apLogos.push_back( logo );
                            ++iLogo;
                        }
                            break;
                            
                        default:
                            break;
                            
                    }//Switch
                    
                    roomBuffer.push_back( oLevel );
                    
                }//if
                
            }//For
            
        }//For
    
    if( iTotalResourcesPerRoom )
    {
        printf( "\nEl cuarto erroneo es:     %d - %d\n", roomIndex, iTotalResourcesPerRoom );
        throw std::exception( );
    }
    printf( "Mapa:  %d \n", roomIndex );
    //Agregar los objetos por cuarto
    _apBuffer.push_back( roomBuffer );
    
}//void

/*
bool ResourcesBuffer::setResourceObtenidoAtHash( const int& hash, std::string _name, const int& type, const int& room )
{
    if( type == 2 && _iNMaxResources >= 5 ) return 0;
    
    std::vector< ObjectResource* > buffer = _apBuffer[ room ];
    ObjectResource* oLevel = buffer[ hash ];
    
    oLevel->iState = 1;
    oLevel->name = _name;
    
    this->addResourceMemoryDirection( type, oLevel );
    
    return 1;
}

void ResourcesBuffer::addResourceMemoryDirection( const int& type, ObjectResource* oLevel )
{
    if( type == 1  )
    {
        _apBottles.push_back( oLevel );
        return;
    }
    
    if( type == 2 )
    {
        this->addKey( type, oLevel );
        return;
    }
}

void ResourcesBuffer::addKey( const int& type, ObjectResource* oLevel )
{
    if( _iNTotalKeysRoom )
        this->removeResourceMemoryDirection( type, oLevel->index );
    
    oLevel->index = ( int ) _apKeys.size( );
    _iNTotalKeysRoom = 1;
    ++_iNMaxResources;
    _apKeys.push_back( oLevel );
}



void ResourcesBuffer::removeResourceMemoryDirection( const int& type, const int& hash )
{
    if( type == 1  )
    {
        _apBottles.erase( _apBottles.begin( ) + hash - 1 );
    }
    
    if( type == 2 )
    {
        _iNTotalKeysRoom = 0;
        --_iNMaxResources;
        _apKeys.erase(  _apKeys.begin( ) + hash - 1 );
    }
    
}

*/

bool ResourcesBuffer::testResourceToDraw( const int& hash, const int& room )
{
    std::vector< ObjectResource* > buffer = _apBuffer[ room ];
    ObjectResource* oLevel = buffer[ hash ];
    
    if( oLevel->getState( ) == 1 )
        return 1;
    
    return 0;
}


const int& ResourcesBuffer::getNResources( )
{
    return _iNMaxResources;
}

void ResourcesBuffer::setNResources( const int& iSum )
{
    _iNMaxResources = iSum;
}

void ResourcesBuffer::resetToNewRoom( )
{
    
}


int ResourcesBuffer::getTotalRoomResources( const int& indexRoom )
{
    printf( "\nEl numero total de recursos en el cuarto %d, es:    %d\n", indexRoom, _aiNResourcesRoom[ indexRoom ] );
    return _aiNResourcesRoom[ indexRoom ];
}

int& ResourcesBuffer::getTotalKeysCollected( )
{
    return _iNTotalKeys;
}

int& ResourcesBuffer::getTotalToolsCollected( )
{
    return _iNTotalTools;
}

bool ResourcesBuffer::testKeysCollected( )
{
    return _iNTotalKeys >= _iMaxTotalKeys ? 1 : 0;
}

bool ResourcesBuffer::testToolsCollected( )
{
    return _iNTotalTools >= _iMaxTotalTools ? 1 : 0;
}

void ResourcesBuffer::sumLogos( )
{
    ++_iNTotalLogos;
}

void ResourcesBuffer::sumKeysCollectedBy( const int& sum, int keyIndex )
{
    //Revisar si ya ha llenado ambas
    if( keysCollectedIndex[ 1 ] == -1 && !_iNTotalKeys )
    {
        keysCollectedIndex[ 1 ] = keyIndex;
    }
    else //Para la segunda llave que entra
    if( keysCollectedIndex[ 0 ] == -1 && _iNTotalKeys )
    {
        keysCollectedIndex[ 0 ] = keyIndex;
    }
    
    _iNTotalKeys += sum;
}

void ResourcesBuffer::sumToolsCollectedBy( const int& sum, int toolIndex )
{
    //Revisar si ya ha llenado ambas
    if( toolsCollectedIndex[ 1 ] == -1 && !_iNTotalTools )
    {
        toolsCollectedIndex[ 1 ] = toolIndex;
    }
    else //Para la segunda llave que entra
        if( toolsCollectedIndex[ 0 ] == -1 && _iNTotalTools )
        {
            toolsCollectedIndex[ 0 ] = toolIndex;
        }
    _iNTotalTools += sum;
}

//Sacar al ultimo de la lista, si la llave es del cuarto regresar el indice de esta, para volver a pintar
int ResourcesBuffer::respawnLastKey( const int& _iRoomIndex )
{
    if( _iRoomIndex == _apKeys[ keysCollectedIndex[ 1 ] ]->getRoomIndex( ) )
    {
        int keyIndex = keysCollectedIndex[ 1 ];
        keysCollectedIndex[ 1 ] = keysCollectedIndex[ 0 ];
        keysCollectedIndex[ 0 ] = -1;
        --_iNTotalKeys;
        return keyIndex;
    }
    
    _apKeys[ keysCollectedIndex[ 1 ] ]->setState( 0 );
    keysCollectedIndex[ 1 ] = keysCollectedIndex[ 0 ];
    keysCollectedIndex[ 0 ] = -1;
    --_iNTotalKeys;
    
    return -1;
}

int ResourcesBuffer::respawnLastTool( const int& _iRoomIndex )
{
    if( _iRoomIndex == _apTools[ toolsCollectedIndex[ 1 ] ]->getRoomIndex( ) )
    {
        int toolIndex = keysCollectedIndex[ 1 ];
        toolsCollectedIndex[ 1 ] = toolsCollectedIndex[ 0 ];
        toolsCollectedIndex[ 0 ] = -1;
        --_iNTotalKeys;
        return toolIndex;
    }
    _apTools[ toolsCollectedIndex[ 1 ] ]->setState( 0 );
    toolsCollectedIndex[ 1 ] = toolsCollectedIndex[ 0 ];
    toolsCollectedIndex[ 0 ] = -1;
    --_iNTotalTools;
    return -1;
}

bool ResourcesBuffer::testKeyForDoor( const int& idKey )
{
    //Revisar que la puerta necesite una llave genérica
    if( idKey == -1 )
    {
        for( int i = 0; i < sizeof( keysCollectedIndex ); ++i )
        {
            if( _apKeys[ keysCollectedIndex[ i ] ]->getHash( ) == idKey )
            {
                _apKeys[ i ]->setState( 4 );
                --_iNTotalKeys;
                if( keysCollectedIndex[ 1 ] == idKey )
                    keysCollectedIndex[ 1 ] = keysCollectedIndex[ 0 ];
                keysCollectedIndex[ 0 ] = -1;
                
                return 1;
            }
        }
    }
    else
    //Revisar si el jugador tiene el objeto guardado
    if( _apKeys[ idKey ]->getState( ) == 3 || _apKeys[ idKey ]->getState( ) == 2 )
    {
        //Cambiar el estado del objeto a usado
        _apKeys[ idKey ]->setState( 4 );
        --_iNTotalKeys;
        if( keysCollectedIndex[ 1 ] == idKey )
            keysCollectedIndex[ 1 ] = keysCollectedIndex[ 0 ];
        
        keysCollectedIndex[ 0 ] = -1;
        
        return 1;
    }
    
    return 0;
}

bool ResourcesBuffer::testToolForMate( const int& idTool )
{
    if( _apTools[ idTool ]->getState( ) == 3 || _apTools[ idTool ]->getState( ) == 2 )
    {
        //Cambiar el estado del objeto a usado
        _apTools[ idTool ]->setState( 4 );
        --_iNTotalTools;
        if( toolsCollectedIndex[ 1 ] == idTool )
            toolsCollectedIndex[ 1 ] = toolsCollectedIndex[ 0 ];
        
        toolsCollectedIndex[ 0 ] = -1;
        
        return 1;
    }
    return 0;
}

int ResourcesBuffer::getTotalBottles( )
{
    return _apBottles.size( );
}

int ResourcesBuffer::getTotalKeys( )
{
    return _apKeys.size( );
}

int ResourcesBuffer::getTotalTools( )
{
    return _apTools.size( );
}

int ResourcesBuffer::getTotalLogos( )
{
    return _apLogos.size( );
}

int ResourcesBuffer::getTotalLetters( )
{
    return _apLetters.size( );
}

ObjectBottle* ResourcesBuffer::testBottleCollected( const int& index )
{
    if( (*_apBottles[ index ] ).getState( ) > 2 ) return _apBottles[ index ];
    
    return nullptr;
}

ObjectKey* ResourcesBuffer::testKeyCollected( const int& index )
{
    int objectState = (*_apKeys[ index ] ).getState( );
    if( objectState > 2 && objectState < 4  ) return _apKeys[ index ];
    
    return nullptr;
}

ObjectTool* ResourcesBuffer::testToolCollected( const int& index )
{
    int objectState = (*_apTools[ index ] ).getState( );
    if( objectState > 2  ) return _apTools[ index ];
    
    return nullptr;
}

ObjectLogo* ResourcesBuffer::testLogoCollected( const int& index )
{
    int objectState = (*_apLogos[ index ] ).getState( );
    if( objectState > 2  ) return _apLogos[ index ];
    
    return nullptr;
}

ObjectLetter* ResourcesBuffer::testLetterCollected( const int& index )
{
    int objectState = (*_apLetters[ index ] ).getState( );
    if( objectState > 2 && objectState < 4  ) return _apLetters[ index ];
    
    return nullptr;
}

ObjectResource& ResourcesBuffer::getRoomResourcesBuffer( const int& indexRoom, const int& index )
{
    std::vector< ObjectResource* > buffer = _apBuffer[ indexRoom ];
    ObjectResource* ResourcesRoom = buffer[ index ];
    return *ResourcesRoom;
}

void ResourcesBuffer::setLettersTest( bool bTestLetters )
{
    _bTestLetters = bTestLetters;
}

bool ResourcesBuffer::testLetters( )
{
    return _bTestLetters;
}


ResourcesBuffer::~ResourcesBuffer( )
{
    _InstanceFlag = iBottle = iKey = iLogo = iLetter = iTool = 0;
}


//
//
///
////
/////Singleton Pattern
int ResourcesBuffer::_InstanceFlag = 0;
ResourcesBuffer* ResourcesBuffer::singResourcesBuffer = nullptr;

ResourcesBuffer* ResourcesBuffer::GetInstance( )
{
    if( !_InstanceFlag && ( _InstanceFlag = 1 ) )
        singResourcesBuffer = new ResourcesBuffer( );
    
    return singResourcesBuffer;
}