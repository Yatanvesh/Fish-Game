#include "GameOverScene.h"
#include "GameScene.h"
USING_NS_CC;
unsigned int GameOverScene::score;

Scene* GameOverScene::createScene( float tempScore)
{
	GameOverScene::score = (int) tempScore;
    return GameOverScene::create();
}

bool GameOverScene::init()
{
  
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto backgroundSprite = Sprite::create("back4.jpg");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	backgroundSprite->setScale(visibleSize.width / backgroundSprite->getContentSize().width, visibleSize.height / backgroundSprite->getContentSize().height);

	addChild(backgroundSprite);
   
	auto retryItem = MenuItemImage::create("Retry.png", "RetryClicked.png", CC_CALLBACK_1(GameOverScene::GoToGameScene, this));
	retryItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 3));
	retryItem->setScale(1.3, 1.3);
	auto exitItem = MenuItemImage::create("Exit.png", "ExitClicked.png", CC_CALLBACK_1(GameOverScene::Exit, this));
	exitItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4 ));
	exitItem->setScale(1.3, 1.3);

	UserDefault* def = UserDefault::getInstance();
	auto highScore = def->getIntegerForKey("HIGHSCORE", 0);
	if (score < highScore) {
		highScore = score;
		def->setIntegerForKey("HIGHSCORE", score);
	}
	def->flush();

	__String* tempScore = __String::createWithFormat("Time: %i", GameOverScene::score);
	auto currentScore = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf", 70);
	currentScore->setScale(1.5);
	currentScore->enableShadow();
	
	currentScore->setColor( Color3B( 85,255,51));
	currentScore->setPosition(Point(visibleSize.width *0.25 + origin.x, visibleSize.height /2 + origin.y));
	this->addChild(currentScore);
	


	__String* tempHighScore = __String::createWithFormat("Best: %i", highScore);
	auto highScoreLabel = Label::createWithTTF(tempHighScore->getCString(), "fonts/Marker Felt.ttf", 70);
	highScoreLabel->setColor(Color3B(102, 254, 255));
	highScoreLabel->setScale(1.5);
	highScoreLabel->enableShadow();

	highScoreLabel->setPosition(Point(visibleSize.width * 0.75 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(highScoreLabel);


	auto menu = Menu::create(retryItem, exitItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
    return true;
}

void GameOverScene::Exit(cocos2d::Ref* sender) {
	Director::getInstance()->end();
}

void GameOverScene::GoToGameScene(cocos2d::Ref* sender) {
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFlipAngular::create(0.3, scene));
}