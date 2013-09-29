#ifndef __ACTORSTATES_H__
#define __ACTORSTATES_H__
#include <State.h>
struct ActorConstants
{
	enum {ACTOR_STATE_IDLE = 1, ACTOR_STATE_SELECTED = 2, ACTOR_STATE_HARVESTING = 3, ACTOR_NUMSTATES = (1 + ACTOR_STATE_HARVESTING)} states;
	enum {OBJECT_TYPE_BEE = 1 , ACTORS_NUMBER = (1 + OBJECT_TYPE_BEE)} subtypes;
};
template<int state, int subtype>
class CActorState : public IState
{
};
/**
 * specialize all states with an implementation 
 * STATE IDLE <BEE>
 */
template<>
class CActorState <ActorConstants::ACTOR_STATE_IDLE, ActorConstants::OBJECT_TYPE_BEE> : public IState
{
public:
	CActorState()
		: idleAction(NULL)
	{
		onInit();
	}
	/**
	*  load animations or any item related to this state
	*/
	void onInit()
	{
	}
	void onRelease()
	{
	}
	/**
	 *  do stuff when before entering into new state
	 */
	void onEnter(CGameObject* object)
	{
		cocos2d::CCArray a ;
		a.addObject(cocos2d::CCRotateBy::create(1.5f, 5.0f));
		a.addObject(cocos2d::CCRotateBy::create(1.5f, -5.0f));
		idleAction = cocos2d::CCRepeatForever::create(cocos2d::CCSequence::create(&a));
		object->getDecorator()->runAction(idleAction);
	}
	/**
	 * do stuff before leaving state
	 */
	void onExit(CGameObject* object)
	{
		object->getDecorator()->stopAction(idleAction);
		idleAction = NULL;
	}
	/**
	 * do stuff before leaving state
	 */
	void onUpdate(float dt)
	{
	}
private:
	cocos2d::CCAction* idleAction;
};
/**
 *      STATE_SELECTED  <BEE>
 */
template<>
class CActorState <ActorConstants::ACTOR_STATE_SELECTED, ActorConstants::OBJECT_TYPE_BEE> : public IState
{
public:
	CActorState()
		: selectedAction(NULL)
	{
		onInit();
	}
	void onInit()
	{
	}
	void onRelease()
	{
	}
	void onEnter(CGameObject* object)
	{
	}
	void onExit(CGameObject* object)
	{
	}
	void onUpdate(float dt)
	{
	}
private:
	cocos2d::CCAction* selectedAction;
};
template<>
class CActorState <ActorConstants::ACTOR_STATE_HARVESTING, ActorConstants::OBJECT_TYPE_BEE> : public IState
{
public:
	CActorState()
		: harvestingAction(NULL)
	{
		onInit();
	}
	void onInit()
	{
	}
	void onRelease()
	{
	}
	void onEnter(CGameObject* object)
	{
		// no animation to play yet, so exit
		onExit(object);
	}
	void onExit(CGameObject* object)
	{
		object->onExitState(ActorConstants::ACTOR_STATE_HARVESTING);
	}
	void onUpdate(float dt)
	{
	}
private:
	cocos2d::CCAction* harvestingAction;
};
#endif
