
#include "Sounds.h"

#define COCOS2D_DEBUG 1

USING_NS_CC;

void Sounds::GetEffect(std::string effectname, std::string prefix)
{
	_oEffect = CocosDenshion::SimpleAudioEngine::getInstance();
	std::string effect = effectname + prefix;
	const char * c = effect.c_str( );
	_oEffect->playEffect(c);
    _oEffect->setEffectsVolume( 2.0 );
}
