#ifndef __CONSUMABLEOBJECT_H__
#define __CONSUMABLEOBJECT_H__
#include <GameObject.h>
#include <ConsumableStates.h>
class CCScene;
class CGameController;
class CConsumableObject : public CGameObject
{
public:
	CConsumableObject(char type, cocos2d::CCScene* parent, CGameController* controller);
	virtual ~CConsumableObject();
	void update(float dt);
	CGameObject* onTouch(cocos2d::CCPoint point);
	void doAction(CGameObject* object);
	CC_PROPERTY(int, state, State);
private:
	void load();
	void remove();
	void onExitState(int state);
private:
	int subtype;
	IState* stateHandler;
	//  states
	CConsumableState <ConsumableConstants::CONSUMABLE_STATE_IDLE, ConsumableConstants::OBJECT_TYPE_HONEY> stateHoneyIdle;
	CConsumableState <ConsumableConstants::CONSUMABLE_STATE_IDLE, ConsumableConstants::OBJECT_TYPE_FLOWER> stateFlowerIdle;
	CConsumableState <ConsumableConstants::CONSUMABLE_STATE_HARVESTED, ConsumableConstants::OBJECT_TYPE_FLOWER> stateFlowerHarvested;

	// state mappings
	IState* stateList[ConsumableConstants::CONSUMABLE_NUMBER][ConsumableConstants::CONSUMABLE_NUMSTATES];
};
#endif