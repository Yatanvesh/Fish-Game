#include "PlayerFish.h"
#include "helpers.h"
//#include "SimpleAudioEngine.h"

USING_NS_CC;

PlayerFish::PlayerFish(cocos2d::Scene* scene) {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();



	Vector< SpriteFrame*>  frames = getAnimation("fish1/tile%03d.png", 6);
	 fishSprite = Sprite::createWithSpriteFrame(frames.front());
	scene->addChild(fishSprite, 100);
	auto spriteBody = PhysicsBody::createCircle(fishSprite->getContentSize().width / 2.7);
	fishSprite->setPhysicsBody(spriteBody);
	//shapeCache->setBodyOnSprite("1", fishSprite);
	//auto spriteBody = fishSprite->getPhysicsBody();
	fishSprite->setPosition(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
	spriteBody->setRotationEnable(false);
	auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 6);
	fishSprite->runAction(RepeatForever::create(Animate::create(animation)));
	fishSprite->setScale(INITIAL_SCALE);
	//fishSprite->setColor(Color3B::MAGENTA);
	//spriteBody->setCollisionBitmask(PLAYER_COLLISION_BITMASK);
	spriteBody->setContactTestBitmask(true);
	//spriteBody->setCategoryBitmask(0x02);    // 0010
	//spriteBody->setMass(10000000);
	

	spriteBody->setCategoryBitmask(0x01);
	spriteBody->setCollisionBitmask(0x03);
	fishSprite->setTag(10);
}

void PlayerFish::grow(float size) {

	auto growAction = ScaleBy::create(0.2, size, size);
	//auto move_ease_in = EaseBackOut::create(growAction);

	auto shrinkSlight = ScaleBy::create(0.2, ( 0.95), ( 0.95));
	auto seq = Sequence::create(growAction, shrinkSlight, nullptr);

	fishSprite->runAction(seq);
	
	CCLOG("scale:  %f %f", fishSprite->getScaleX(), fishSprite->getScaleY());


}
void PlayerFish::reset() {
	auto scaleDown= ScaleTo::create(0.2, INITIAL_SCALE-0.05);
	auto scaleReset = ScaleTo::create(0.2, INITIAL_SCALE );

	auto turnRed = TintTo::create(0.25f, 250, 0, 0);
	auto turnBack = TintTo::create(0.25f, 255, 255, 255);
	auto seq = Sequence::create(turnRed, turnBack, nullptr);
	auto seq2 = Sequence::create(scaleDown, scaleReset,nullptr);
	fishSprite->runAction(seq);
	fishSprite->runAction(seq2);
}

void PlayerFish::flip(bool flipped) {
	fishSprite->setFlippedX(flipped);
}