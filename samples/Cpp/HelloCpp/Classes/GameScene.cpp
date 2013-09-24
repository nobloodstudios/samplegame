#include "GameScene.h"
#include "AppMacros.h"
#include "GameController.h"
USING_NS_CC;
CGameController* GameScene::controller = NULL;
CCScene* GameScene::scene(CGameController* c)
{
    CCScene *scene = CCScene::create();
    GameScene *layer = GameScene::create();
	scene->addChild(layer);
	controller = c;
	return scene;
}
bool GameScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
	this->schedule( schedule_selector(GameScene::updateGame) );
	this->initWithColor(cocos2d::ccc4(0, 0, 0, 0));
	this->setTouchEnabled(true);
	return true;
}
void GameScene::updateGame(float dt)
{
	controller->update(dt);
}
void GameScene::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
     CCTouch* touch = (CCTouch*)( touches->anyObject() );
	 CCPoint location = touch->getLocationInView();
	 location = CCDirector::sharedDirector()->convertToGL(location);
	 controller->onTouch(location);
}
