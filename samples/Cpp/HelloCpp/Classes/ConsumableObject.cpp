#include <ConsumableObject.h>
#include <ActorStates.h>
#include <GameController.h>

CConsumableObject::CConsumableObject(char type, cocos2d::CCScene* parent, CGameController* controller)
	: CGameObject(CGameObject::OBJECT_TYPE_CONSUMABLE << 8 | type, parent, controller)
{
	subtype = type;
	stateHandler = NULL;
	stateList[ConsumableConstants::OBJECT_TYPE_HONEY][ConsumableConstants::CONSUMABLE_STATE_IDLE] = &stateHoneyIdle;
	stateList[ConsumableConstants::OBJECT_TYPE_FLOWER][ConsumableConstants::CONSUMABLE_STATE_IDLE] = &stateFlowerIdle;
	stateList[ConsumableConstants::OBJECT_TYPE_FLOWER][ConsumableConstants::CONSUMABLE_STATE_HARVESTED] = &stateFlowerHarvested;
	load();
}
CConsumableObject::~CConsumableObject()
{
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
	return CGameObject::onTouch(point);
}
void CConsumableObject::doAction(CGameObject* object)
{
	if (object->getType() == type)
		return;
	float distance = (object->getTilePosition() - getTilePosition()).getLength();
	if (distance <= 2.0f)
	{
		if ( object->getType() == ((CGameObject::OBJECT_TYPE_ACTOR << 8) | ActorConstants::OBJECT_TYPE_BEE) )
		{
			setState(ConsumableConstants::CONSUMABLE_STATE_HARVESTED);
		}
	}
}
void CConsumableObject::remove()
{
	gc->removeGameObject(this);
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
void CConsumableObject::onExitState(int state)
{
	if (state == ConsumableConstants::CONSUMABLE_STATE_HARVESTED)
	{
		remove();
		// TODO(iulia): gather points
	}
}
