#ifndef __ACTORSTATES_H__
#define __ACTORSTATES_H__
#include <State.h>
struct ActorConstants
{
	enum {ACTOR_STATE_IDLE = 1, ACTOR_STATE_SELECTED = 2, ACTOR_NUMSTATES = (1 + ACTOR_STATE_SELECTED)} states;
	enum {OBJECT_TYPE_BEE = 1 , ACTORS_NUMBER = (1 + OBJECT_TYPE_BEE)} subtypes;
};
template<int state, int subtype>
class CActorState : public State
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
	{
	}
	/**
	*  load animations or any item related to this state
	*/
	void onInit()
	{
		cocos2d::CCArray a ;
		a.addObject(cocos2d::CCRotateBy::create(1.5f, 5.0f));
		a.addObject(cocos2d::CCRotateBy::create(1.5f, -5.0f));
		idleAction = cocos2d::CCRepeatForever::create(cocos2d::CCSequence::create(&a));
	}
	/**
	 *  do stuff when before entering into new state
	 */
	void onEnter(CGameObject* object)
	{
		onInit();
		object->getDecorator()->runAction(idleAction);
	}
	/**
	 * do stuff before leaving state
	 */
	void onExit(CGameObject* object)
	{
		object->getDecorator()->stopAction(idleAction);
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
	{
		onInit();
	}
	void onInit()
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
#endif