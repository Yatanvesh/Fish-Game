
#ifndef __HELPERS_H__
#define __HELPERS_H__
#include "cocos2d.h"
USING_NS_CC;

Vector< SpriteFrame*> getAnimation(const char* format, int count);

#endif

#define ENEMY_COLLISION_BITMASK 3
#define PLAYER_COLLISION_BITMASK 5