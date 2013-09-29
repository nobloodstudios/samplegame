#include <DecoratorObject.h>
CDecoratorObject::CDecoratorObject(char type, cocos2d::CCScene* parent, CGameController* controller)
	: CGameObject(CGameObject::OBJECT_TYPE_DECORATOR << 8 | type, parent, controller)
{
	subtype = type;
	load();
}
CDecoratorObject::~CDecoratorObject()
{
	remove();
}
void CDecoratorObject::load()
{
	if( subtype == CDecoratorObject::OBJECT_TYPE_EMPTY_TILE)
	{
		decorator = cocos2d::CCSprite::createWithSpriteFrameName("tile.png");
	}
	else
	{
		assert(false && "unknown type");
	}
	scene->addChild(decorator);
}
void CDecoratorObject::update(float dt)
{
	CGameObject::update(dt);
}
void CDecoratorObject::remove()
{
	
}
