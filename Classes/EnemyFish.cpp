#include "EnemyFish.h"
#include "helpers.h"

//#include "SimpleAudioEngine.h"

USING_NS_CC;

EnemyFish::EnemyFish(cocos2d::Scene* scene) {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	this->scene = scene;
	srand(static_cast <unsigned> (time(0)));


	
}

void EnemyFish::spawn() {
	auto fish = new Fish();
	fishList.push_back(fish);
	scene->addChild(fish->fishSprite);
	
	float random = CCRANDOM_0_1();
	float posY = CCRANDOM_0_1() * visibleSize.height;
	//float speed = CCRANDOM_0_1();
	//speed = speed * visibleSize.width;
	//speed < MIN_SPEED ? speed = MIN_SPEED : NULL;
	//speed > MAX_SPEED ? speed = MAX_SPEED : NULL;
	float speed = MAX_SPEED + static_cast <float> (CCRANDOM_0_1()*100000) / (static_cast <float> (100000 / (MIN_SPEED - MAX_SPEED)));
	float scale = MIN_SIZE + static_cast <float> (CCRANDOM_0_1() * 100000) / (static_cast <float> (100000 / (MAX_SIZE - MIN_SIZE)));
	//CCLOG("speed %f", speed);
	auto moveAction = random>0.5? MoveBy::create(speed * visibleSize.width, Point(visibleSize.width * -2, 0)) :
								  MoveBy::create(speed * visibleSize.width, Point(visibleSize.width * 2, 0));;
	if (random > 0.5) {
		//right
		fish->fishSprite->setPosition(visibleSize.width * 1.5 + origin.x, posY );
		//fish->fishSprite->setScale(fish->fishSprite->getScaleX() * -1, fish->fishSprite->getScaleY());
		//fish->spriteBody->set
		//CCLOG(" speed %f", speed * 0.01 );
		
	}
	else {
		fish->fishSprite->setPosition(visibleSize.width * -0.5 + origin.x, posY );
		float moveSpeed = speed * 0.01 * visibleSize.width;
		fish->fishSprite->setFlippedX(true);

	//	CCLOG(" speed %f", speed * 0.01);
		//fish->fishSprite->runAction(moveAction);
	}
	fish->fishSprite->getPhysicsBody()->setCategoryBitmask(0x03);    // 0010
	fish->fishSprite->getPhysicsBody()->setCollisionBitmask(0x04);   // 0001


	fish->fishSprite->setScale(scale);

	auto deleteFish = CallFunc::create([=]() {
		scene->removeChild(fish->fishSprite);
		delete fish;
		//CCLOG("deleting fish");
		});

	auto sequence = Sequence::create(moveAction, deleteFish, NULL);
	fish->fishSprite->runAction(sequence);
}

