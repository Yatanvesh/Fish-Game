
#include "SplashScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene* SplashScene::createScene()
{
    return SplashScene::create();
}


bool SplashScene::init()
{
  
    if ( !Scene::init() )
    {
        return false;
    }
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/death1.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/death2.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/death3.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/eat1.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/eat2.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/eat3.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/eat4.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/eat5.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sounds/music.mp3");


    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->scheduleOnce(schedule_selector(SplashScene::GoToMainMenuScene), 0.3);

	auto backgroundSprite = Sprite::create("back4.jpg");
	//backgroundSprite->setScale(2.5);
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	backgroundSprite->setScale(visibleSize.width / backgroundSprite->getContentSize().width, visibleSize.height / backgroundSprite->getContentSize().height);
	addChild(backgroundSprite);
	
	auto logo = Sprite::create("logo.png");
	logo->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	addChild(logo);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/music.mp3", true);

	cocos2d::Device::setKeepScreenOn(true);

    return true;
}

void SplashScene::GoToMainMenuScene(float dt) {
	auto scene = GameScene::createScene();

	Director::getInstance()->replaceScene(TransitionMoveInB::create(0.3, scene));
}