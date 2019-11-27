#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "helpers.h"
#include "GameOverScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
   
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Device::setAccelerometerEnabled(true);
	auto accListener = EventListenerAcceleration::create(CC_CALLBACK_2(GameScene::OnAcceleration, this));
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(accListener, this);

	auto backgroundSprite = Sprite::create("back2.jpg");
	backgroundSprite->setScale(visibleSize.width / backgroundSprite->getContentSize().width, visibleSize.height / backgroundSprite->getContentSize().height);

	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	addChild(backgroundSprite);

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);
	edgeBody->setCategoryBitmask(0x03);
	edgeBody->setCollisionBitmask(0x01);
	addChild(edgeNode);

	//this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("allFish-0.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("allFish-1.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("allFish-2.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("allFish-3.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("allFish-4.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("allFish-5.plist");

	playerFish= new PlayerFish(this);

	//this->schedule(schedule_selector(HelloWorld::grow), 1);
	this->schedule(schedule_selector(GameScene::spawn), 0.8);

	enemyFish = new EnemyFish(this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	time_t _time = time(0); // now
	startTime = *localtime(&_time);

    return true;
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
	{
		Director::getInstance()->end();
	}
}

bool GameScene::grow(float playerMass,  float enemyMass) {
	auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();

	float currentScale = playerFish->getScale();
	
	if (currentScale > 2) {
		time_t _time = time(0); // now
		struct std::tm endTime = *localtime(&_time);
		double score = difftime(mktime(&endTime), mktime(&startTime));
		CCLOG("Time: %lf", score);

		auto scene = GameOverScene::createScene(score);
		Director::getInstance()->replaceScene(TransitionFlipAngular::create(0.3, scene));
		
	}

	if (currentScale > 1.6) {
		enemyFish->IncreaseMaxSize(0.8);
	}
	else if (currentScale > 1.1)
		enemyFish->IncreaseMaxSize(0.7);
	

	if (enemyMass > playerMass) {
		playerFish->reset();
		switch (rand() % 3) {
		case 0: audioEngine->playEffect("Sounds/death1.mp3");
			break;
		case 1:audioEngine->playEffect("Sounds/death2.mp3");
			break;
		case 2:audioEngine->playEffect("Sounds/death3.mp3");
			break;
		default: throw 45;
		}
		Device::vibrate(1);

		return false;

	}
	float growRatio =1+ (enemyMass / playerMass);

	//CCLOG("%f", growRatio);
	if (growRatio > 1.1)
		growRatio = 1.1;
	playerFish->grow(growRatio);

	switch (rand() % 5) {
	case 0: audioEngine->playEffect("Sounds/eat1.mp3");
		break;
	case 1:audioEngine->playEffect("Sounds/eat2.mp3");
		break;
	case 2:audioEngine->playEffect("Sounds/eat3.mp3");
		break;
	case 3:audioEngine->playEffect("Sounds/eat4.mp3");
		break;
	case 4:audioEngine->playEffect("Sounds/eat5.mp3");
		break;
	default: throw 45;
	}
	Device::vibrate(0.2);

	return true;

}
void GameScene::spawn(float dt) {
	enemyFish->spawn();

}


void GameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

void GameScene::OnAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* event) {
	//CCLOG("accboi %f %f %f", acc->z, acc->y, acc->x);
	this->getPhysicsWorld()->setGravity(Vec2(acc->x * 4000, 250+ acc->y * 3750));
	if (acc->x < 0)
		playerFish->flip(false);
	else playerFish->flip(true);
}


bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact) {
	auto a = contact.getShapeA()->getBody()->getNode();
	auto b = contact.getShapeB()->getBody()->getNode();

	//if ((PLAYER_COLLISION_BITMASK == a->getCollisionBitmask() && ENEMY_COLLISION_BITMASK == b->getCollisionBitmask()) ||
	//	(PLAYER_COLLISION_BITMASK == b->getCollisionBitmask() && ENEMY_COLLISION_BITMASK == a->getCollisionBitmask())) {
	//	float mass = a->getMass();
	//	CCLOG("mass ", mass);
	//}
	//CCLOG("mass %d %d %d %d", a->getPhysicsBody()->getCollisionBitmask(), b->getPhysicsBody()->getCollisionBitmask(), a->getPhysicsBody()->getCategoryBitmask(), b->getPhysicsBody()->getCategoryBitmask());
	//CCLOG("COllision %d %d", a->getTag(), b->getTag());
	auto shrinkAction = ScaleTo::create(0.2, 0);
	
	if (a && b)
	{
		if (a->getTag() == 10 && b->getTag()== 12 )
		{
			if (grow(a->getPhysicsBody()->getMass(), b->getPhysicsBody()->getMass()))
				b->runAction(shrinkAction);
			//	b->setPosition(-2000, -2000);
		}
		else if (a->getTag() == 12 && b->getTag() == 10)
		{
			if(grow(b->getPhysicsBody()->getMass(), a->getPhysicsBody()->getMass()))
				a->runAction(shrinkAction);
			//a->setPosition(-2000, -2000);


		}
	}

	return true;

}
