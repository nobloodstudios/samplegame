#ifndef __STATE_H__
#define __STATE_H__
class CGameObject;
class IState
{
public:
	virtual void onInit() = 0;
	virtual void onEnter(CGameObject*) = 0;
	virtual void onExit(CGameObject*) = 0;
	virtual void onUpdate(float dt) = 0;
	virtual void onRelease() = 0;
};
#endif