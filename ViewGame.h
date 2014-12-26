//
//  ViewGame.h
//  JuegoTequilero
//
//  Created by Max on 7/11/14.
//
//

#ifndef __JuegoTequilero__ViewGame__
#define __JuegoTequilero__ViewGame__

#include <iostream>

#include "cocos2d.h"

#include "Player.h"
#include "MapWorld.h"
#include "Resources.h"
#include "BarraMision.h"
#include "SimpleAudioEngine.h"
#include "Milliseconds.h"
#include "PauseGame.h"
#include "RoomExit.h"
#include "Doors.h"
#include "Mates.h"
#include "FilosofiaIntroduction.h"


class ViewGame: public cocos2d::Layer
{
public:
    
    ViewGame ();
    ~ViewGame ();
    
    bool init ();
    
    CREATE_FUNC( ViewGame );
    
    
private:
    
    void update (float dt);
    void checkForCollisionWithPuertas( );
    void testObjectsCollisions( );
    bool testResourcesCollisions( );
    bool testMatesCollision( );
    bool testDoorsCollision( );
    void roomConstructor ();
    void roomDeconstructor ();
    void changeScene (int& iPrevMapIndex);
    void updatePuertasRecursos ();
    void createScene ();
    
    void pauseGameInput ();
    cocos2d::EventListenerTouchOneByOne* createInputForPause ();
    
    void beganTouch( cocos2d::EventListenerTouchOneByOne* listenerPause );
    void endedTouch( cocos2d::EventListenerTouchOneByOne* listenerPause );
    void movedTouch( cocos2d::EventListenerTouchOneByOne* listenerPause );
    void cancelledTouch( cocos2d::EventListenerTouchOneByOne* listenerPause );
    
    void resetPauseValues( );
    void doPause( );
    
    std::string chooseADoor( int& iPrevMapIndex );
    
    
private:
    
    bool _bfStart;
    bool _bChangeScene;
    bool _bActionTouch;
    
    bool _bPauseLeft;
    bool _bPauseRight;
    bool _bStartTouchLeft;
    bool _bStartTouchRight;
    bool _bPause;
    
    bool _bText;
    
    bool _bDoorCollision;
    
    float _iStartSeconds;
    
    CocosDenshion::SimpleAudioEngine* _oAudioEngine;
    
    int* _bInicio;
    
    int _iPx;
    int _iPy;
    int _iPWidth;
    int _iPHeight;
    int _iAvanzoRetrocedio;
    int _iMapWidth;
    
    float _fPauseLeft;
    float _fPauseRight;
    
    bool _bFilosofiaInitialText;
    bool _bDoorMissText;
    
    std::string _sPuerta;
    
    MapWorld* _oMap;
    Resource* _oResource;
    Player* _oPlayer;
    Resource* _oPuertas;
    BarraMision* _oBarraMision;
    Milliseconds* _oMilliseconds;
    RoomExit* _oRoomExit;
    Doors* _oDoors;
    Mates* _oMates;
    FilosofiaIntroduction* _oFilosofia;
    
    cocos2d::TMXTiledMap* _tileMap;
};

#endif /* defined(__JuegoTequilero__ViewGame__) */
