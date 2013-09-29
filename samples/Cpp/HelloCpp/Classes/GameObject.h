#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#include <cocos2d.h>
#include <State.h>
class CCSprite;
class CGameController;
class CGameObject
{
public:	
	enum {	OBJECT_TYPE_NOTYPE = -1, 
			OBJECT_TYPE_ACTOR, 
			OBJECT_TYPE_CONSUMABLE, 
			OBJECT_TYPE_DECORATOR
		  };
	CGameObject(int _type, cocos2d::CCScene* parent, CGameController* controller);
	virtual ~CGameObject();
	virtual void load();
	virtual void update(float dt);
	virtual CGameObject* onTouch(cocos2d::CCPoint point);
	virtual void doAction(CGameObject*) {}
	virtual void remove();
    cocos2d::CCRect getBounds() { return decorator->getTextureRect();}
	CC_PROPERTY(cocos2d::CCSprite*, decorator, Decorator);
	CC_PROPERTY(cocos2d::CCScene*, scene, Scene);
	CC_PROPERTY(cocos2d::CCPoint, screenPosition, ScreenPosition);
	CC_PROPERTY(cocos2d::CCPoint, tilePosition, TilePosition);
	CC_PROPERTY(int, type, Type);
	//  callbacks from state machine
	virtual void onExitState(int state);
protected:
	bool selected;
	cocos2d::CCSprite* selection;
	CGameController* gc;
};
#endif
