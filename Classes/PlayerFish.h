
#ifndef __PLAYERFISH_H__
#define __PLAYERFISH_H__


#include "cocos2d.h"

class PlayerFish
{
public:
	PlayerFish(cocos2d::Scene *scene);
	void grow(float size);
	void reset();
	void flip(bool flipped);
	float getScale() { return fishSprite->getScaleX(); }
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Sprite* fishSprite;

	const float INITIAL_SCALE = 0.4;
};

#endif 
