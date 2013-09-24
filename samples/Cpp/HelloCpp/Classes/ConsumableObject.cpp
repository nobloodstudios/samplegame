#include <ConsumableObject.h>
CConsumableObject::CConsumableObject(char type, cocos2d::CCScene* parent)
	: CGameObject(CGameObject::OBJECT_TYPE_CONSUMABLE << 8 | type, parent)
{
	subtype = type;
	stateHandler = NULL;
	stateList[ConsumableConstants::OBJECT_TYPE_HONEY][ConsumableConstants::CONSUMABLE_STATE_IDLE] = &stateHoneyIdle;
	stateList[ConsumableConstants::OBJECT_TYPE_FLOWER][ConsumableConstants::CONSUMABLE_STATE_IDLE] = &stateFlowerIdle;
	load();
}
CConsumableObject::~CConsumableObject()
{
	remove();
}
void CConsumableObject::load()
{
	if( subtype == ConsumableConstants::OBJECT_TYPE_HONEY)
	{
		decorator = cocos2d::CCSprite::createWithSpriteFrameName("honey.png");
		decorator->setAnchorPoint(cocos2d::CCPoint(0.5f, 0.5f));
		decorator->setScale(1.0f);
		setState(ConsumableConstants::CONSUMABLE_STATE_IDLE);
	} 
	else if (subtype == ConsumableConstants::OBJECT_TYPE_FLOWER)
	{
		decorator = cocos2d::CCSprite::createWithSpriteFrameName("flower3.png");
		decorator->setAnchorPoint(cocos2d::CCPoint(0.5f, 0.5f));
		decorator->setScale(1.0f);
		setState(ConsumableConstants::CONSUMABLE_STATE_IDLE);
	}
	else
	{
		assert(false && "unknown type");
	}
	scene->addChild(decorator);
}
void CConsumableObject::update(float dt)
{
	stateHandler->onUpdate(dt);
	CGameObject::update(dt);
}
CGameObject* CConsumableObject::onTouch(cocos2d::CCPoint point)
{
	if (subtype == 1)
	{
		int xxx=0;
	}
	return CGameObject::onTouch(point);
}
void CConsumableObject::doAction(CGameObject* object)
{
	if (object->getType() == type)
		return;
}
void CConsumableObject::remove()
{
}
void CConsumableObject::setState(int  s)
{
	if (state == s) 
		return;
	state = s;
	if (stateHandler)
	{
		stateHandler->onExit(this);
	}
	stateHandler = stateList[subtype][s];
	stateHandler->onEnter(this);
}
int CConsumableObject::getState()
{
	return state;
}