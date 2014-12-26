//
//  BarraMision.h
//  JuegoTequilero
//
//  Created by Max on 7/19/14.
//
//

#ifndef __JuegoTequilero__Sounds__
#define __JuegoTequilero__Sounds__

#include <iostream>
#include "SimpleAudioEngine.h"
#include "cocos2d.h"

class Sounds 
{

private:
	
	CocosDenshion::SimpleAudioEngine* _oEffect;

public:
	void GetEffect(std::string effectname, std::string prefix);
	
	


};

#endif /* defined(__JuegoTequilero__Sounds__) */