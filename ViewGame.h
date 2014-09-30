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

#include "Puertas.h"

#include "PuertasBoxCollision.h"

#include "DrawRecursos.h"

#include "BarraMision.h"

#include "SimpleAudioEngine.h"

#include "Milliseconds.h"

#include "PauseGame.h"




class ViewGame: public cocos2d::Layer
{
private:
    
    bool _bfStart;
    bool _bChangeScene;
    bool _bActionTouch;
    
    bool _bPauseLeft;
    bool _bPauseRight;
    bool _bStartTouchLeft;
    bool _bStartTouchRight;
    bool _bPause;
    
    float _iStartSeconds;
    
    CocosDenshion::SimpleAudioEngine* _oAudioEngine;
    
    int* _bInicio;
    
    int _iMapIndex;
    int _iPx;
    int _iPy;
    int _iPWidth;
    int _iPHeight;
    int _iAvanzoRetrocedio;
    int _iMapWidth;
    
    float _fPauseLeft;
    float _fPauseRight;
    
    std::string _sPuerta;
    
    MapWorld* _oMap;
    Resource* _oResource;
    Player* _oPlayer;
    Resource* _oPuertas;
    PuertasBoxCollision* _oPuertasBoxCollision;
    DrawRecursos* _oDrawRecursos;
    BarraMision* _oBarraMision;
    Milliseconds* _oMilliseconds;
    
    objectResource* _piResourcePoints;
    objectResource* _orPuertasPoints;
    
    cocos2d::TMXTiledMap* _tileMap;
    
    void update (float dt);
    void checkForCollisionWithPuertas ();
    void checkForCollisionWithRecursosAndPaintThem ();
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
    
public:
    
    ViewGame ();
    
    ~ViewGame ();
    
    bool init ();
    
    CREATE_FUNC( ViewGame );
};

#endif /* defined(__JuegoTequilero__ViewGame__) */
