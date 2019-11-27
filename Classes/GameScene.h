
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "PlayerFish.h"
#include "EnemyFish.h"
#include <time.h>
class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
	void OnAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* event);
private:
	//cocos2d::Vector < cocos2d::SpriteFrame*> getAnimation(const char* format, int count);
	PlayerFish* playerFish;
	EnemyFish* enemyFish;

	bool grow(float playerMass, float enemyMass);
		void spawn(float dt);
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	std::tm startTime;
};

#endif // __HELLOWORLD_SCENE_H__
