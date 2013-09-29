#include <ActorObject.h>
#include <ConsumableStates.h>
CActorObject::CActorObject(char type, cocos2d::CCScene* parent, CGameController* controller)
	: CGameObject(CGameObject::OBJECT_TYPE_ACTOR << 8 | type, parent, controller)
{
	subtype = type;
	stateHandler = NULL;
	stateList[ActorConstants::OBJECT_TYPE_BEE][ActorConstants::ACTOR_STATE_IDLE] = &stateBeeIdle;
	stateList[ActorConstants::OBJECT_TYPE_BEE][ActorConstants::ACTOR_STATE_SELECTED] = &stateBeeSelected;
	stateList[ActorConstants::OBJECT_TYPE_BEE][ActorConstants::ACTOR_STATE_HARVESTING] = &stateBeeHarvesting;
	load();
}
CActorObject::~CActorObject()
{
	remove();
}
void CActorObject::load()
{
	if( subtype == ActorConstants::OBJECT_TYPE_BEE)
	{
		decorator = cocos2d::CCSprite::createWithSpriteFrameName("bee.png");
		decorator->setAnchorPoint(cocos2d::CCPoint(0.5f, 0.5f));
		decorator->setScale(0.93f);
		setState(ActorConstants::ACTOR_STATE_IDLE);
	} 
	else
	{
		assert(false && "unknown type");
	}
	scene->addChild(decorator);
}
void CActorObject::update(float dt)
{
	CGameObject::update(dt);
}
CGameObject* CActorObject::onTouch(cocos2d::CCPoint point)
{
	bool previouslySelected = selected;
	CGameObject* thisone = CGameObject::onTouch(point);
	if (thisone)
	{
		setState(ActorConstants::ACTOR_STATE_SELECTED);
	}
	if (previouslySelected && !selected)
	{
		setState(ActorConstants::ACTOR_STATE_IDLE);
	}
	return thisone;
}
void CActorObject::doAction(CGameObject* object)
{
	if (object->getType() == type)
		return;
	float distance = (object->getTilePosition() - getTilePosition()).getLength();
	if (distance <= 2.0f)
	{
		if ( object->getType() == ((CGameObject::OBJECT_TYPE_CONSUMABLE << 8) | ConsumableConstants::OBJECT_TYPE_FLOWER) )
		{
			setState(ActorConstants::ACTOR_STATE_HARVESTING);
			setTilePosition(object->getTilePosition());
			setScreenPosition(object->getScreenPosition());
		}
	}
}
void CActorObject::remove()
{
}
void CActorObject::setState(int  s)
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
int CActorObject::getState()
{
	return state;
}
void CActorObject::onExitState(int state)
{
	if (state == ActorConstants::ACTOR_STATE_HARVESTING)
	{
		setState(ActorConstants::ACTOR_STATE_IDLE);
		selected = true;
	}
}