#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "cocos2d.h"
class CGameController;
class GameScene : public cocos2d::CCLayerColor
{
public:
    virtual bool init();  
    static cocos2d::CCScene* scene(CGameController* c);
	void updateGame(float dt);
	void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	CREATE_FUNC(GameScene);
private:
	static CGameController* controller;
};
#endif // __HELLOWORLD_SCENE_H__
