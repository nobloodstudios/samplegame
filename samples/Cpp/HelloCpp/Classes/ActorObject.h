#ifndef __ACTOROBJECT_H__
#define __ACTOROBJECT_H__
#include <GameObject.h>
#include <ActorStates.h>
class CCScene;
class CActorObject : public CGameObject
{
public:
	CActorObject(char type, cocos2d::CCScene* parent);
	virtual ~CActorObject();
	void update(float dt);
	CGameObject* onTouch(cocos2d::CCPoint point);
	void doAction(CGameObject* object);
	CC_PROPERTY(int, state, State);
private:
	void load();
	void remove();
private:
	int subtype;
	IState* stateHandler;
	//  states
	CActorState <ActorConstants::ACTOR_STATE_IDLE, ActorConstants::OBJECT_TYPE_BEE> stateBeeIdle;
	CActorState <ActorConstants::ACTOR_STATE_SELECTED, ActorConstants::OBJECT_TYPE_BEE> stateBeeSelected;
	// state mappings
	IState* stateList[ActorConstants::ACTORS_NUMBER][ActorConstants::ACTOR_NUMSTATES];
};
#endif