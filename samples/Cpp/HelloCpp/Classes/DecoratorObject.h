#ifndef __DECORATOROBJECT_H__
#define __DECORATOROBJECT_H__
#include <GameObject.h>
class CCScene;
class CGameController;
class CDecoratorObject : public CGameObject
{
public:
	enum {OBJECT_TYPE_EMPTY_TILE = 1};
	CDecoratorObject(char type, cocos2d::CCScene* parent, CGameController* controller);
	virtual ~CDecoratorObject();
	void update(float dt);
	CGameObject* onTouch(cocos2d::CCPoint point) { return NULL; }
private:
	void load();
	void remove();
	int subtype;
};
#endif