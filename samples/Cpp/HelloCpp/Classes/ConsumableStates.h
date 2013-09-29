#ifndef _CONSUMABLESTATES_H__
#define _CONSUMABLESTATES_H__
#include <State.h>
/**
 * define all consumable states and subtypes here
 */
struct ConsumableConstants
{
	enum {CONSUMABLE_STATE_IDLE = 1, CONSUMABLE_STATE_HARVESTED, CONSUMABLE_NUMSTATES = (1 + CONSUMABLE_STATE_HARVESTED)} states;
	enum {OBJECT_TYPE_HONEY = 1, OBJECT_TYPE_FLOWER, CONSUMABLE_NUMBER = (OBJECT_TYPE_FLOWER + 1)} subtypes;
};
/**
*  generic consumable state implementation
*/
template<int state, int subtype>
class CConsumableState : public IState
{
};
/**
 * specialize all states with an implementation 
 * <HONEY>
 */
template<>
class CConsumableState <ConsumableConstants::CONSUMABLE_STATE_IDLE, ConsumableConstants::OBJECT_TYPE_HONEY> : public IState
{
public:
	CConsumableState()
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
		a.addObject(cocos2d::CCScaleBy::create(1.0f, 1.01f));
		a.addObject(cocos2d::CCScaleBy::create(1.0f, 1.0f/1.01f));
		idleAction = cocos2d::CCRepeatForever::create(cocos2d::CCSequence::create(&a));
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
 * specialize all states with an implementation 
 * <FLOWER idle>
 */
template<>
class CConsumableState <ConsumableConstants::CONSUMABLE_STATE_IDLE, ConsumableConstants::OBJECT_TYPE_FLOWER> : public IState
{
public:
	CConsumableState()
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
		a.addObject(cocos2d::CCRotateBy::create(30.0f, 360.0f));
		idleAction = cocos2d::CCRepeatForever::create(cocos2d::CCSequence::create(&a));
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
 * specialize all states with an implementation 
 * <FLOWER harvested>
 */
template<>
class CConsumableState <ConsumableConstants::CONSUMABLE_STATE_HARVESTED, ConsumableConstants::OBJECT_TYPE_FLOWER> : public IState
{
public:
	CConsumableState()
		: harvestedAction(NULL)
	{
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
		// no animation yet ...just exit for now
		onExit(object);
	}
	/**
	 * do stuff before leaving state
	 */
	void onExit(CGameObject* object)
	{
		object->onExitState(ConsumableConstants::CONSUMABLE_STATE_HARVESTED);
	}
	/**
	 * do stuff before leaving state
	 */
	void onUpdate(float dt)
	{
	}
private:
	cocos2d::CCAction* harvestedAction;
};

#endif
