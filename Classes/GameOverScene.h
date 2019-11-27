
#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene( float tempScore);

    virtual bool init();
	static unsigned int score;
    CREATE_FUNC(GameOverScene);
private:
	void Exit(cocos2d::Ref* sender);
	void GoToGameScene(cocos2d::Ref* sender);

};

#endif 
