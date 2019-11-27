
#ifndef __EnemyFish_H__
#define __EnemyFish_H__

#include "cocos2d.h"
#include "Fish.h"
#include <list> 

class EnemyFish
{
public:
	EnemyFish(cocos2d::Scene *scene);

	void spawn();
	void IncreaseMaxSize(float size) { MAX_SIZE = size; }
private:
	cocos2d::Scene* scene;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	std::list<Fish*> fishList;
	
	void scheduleDelete(float dt);

	const float MAX_SPEED = 0.0025;
	const float MIN_SPEED = 0.006;
	const float MIN_SIZE = 0.1;
	float MAX_SIZE=0.5;
   
};

#endif 
