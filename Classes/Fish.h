
#ifndef __HELPERS_H__
#define __HELPERS_H__
#include "cocos2d.h"

class Fish {
public:
	Fish();
	cocos2d::Sprite * fishSprite;
	cocos2d::PhysicsBody* spriteBody;
};

#endif