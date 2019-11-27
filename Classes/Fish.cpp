#include "Fish.h"
#include "helpers.h"

USING_NS_CC;
Vector< SpriteFrame*> getAnimation2(const char* format, int count)
{
	auto spritecache = SpriteFrameCache::getInstance();
	Vector< SpriteFrame*> animFrames;
	char str[100];
	for (int i = 1; i <= count; i++)
	{
		sprintf(str, format, i);
		animFrames.pushBack(spritecache->getSpriteFrameByName(str));
	}
	return animFrames;
}
Fish::Fish(){
	float random = CCRANDOM_0_1();
	Vector< SpriteFrame*>  frames;
	Animation* animation;
	int fishNumber =2+ rand() %11;
	//CCLOG("fish %d", fishNumber);
	std::ostringstream stringStream;
	stringStream << "fish" << fishNumber << "/tile%03d.png";
	std::string fishDirectory = stringStream.str();
	

	
		  frames = getAnimation2(fishDirectory.c_str(), 11);
		 animation = Animation::createWithSpriteFrames(frames, 1.0f / 11);


	
	//fishSprite->setScaleX(fishSprite->getScaleX() * -1);
	fishSprite = Sprite::createWithSpriteFrame(frames.front());
	if(fishNumber<=6)
	spriteBody = PhysicsBody::createCircle(fishSprite->getContentSize().width / 2.8);
	else 	spriteBody = PhysicsBody::createCircle(fishSprite->getContentSize().width / 2.3);

	fishSprite->setPhysicsBody(spriteBody);
	//if(fishNumber<=6)
	//shapeCache->setBodyOnSprite("tile000", fishSprite);
	//else 	shapeCache->setBodyOnSprite("tile011", fishSprite);
	//spriteBody = fishSprite->getPhysicsBody();
	spriteBody->setRotationEnable(false);
	//fishSprite->setScale(0.2);
	spriteBody->setGravityEnable(false);
	//spriteBody->setDynamic(false);

	spriteBody->setContactTestBitmask(true);
//spriteBody->setMass(1);
	spriteBody->setCategoryBitmask(0x01);   
	//spriteBody->setCollisionBitmask(0x03);
	fishSprite->runAction(RepeatForever::create(Animate::create(animation)));
	fishSprite->setTag(12);
}