#include <GameObject.h>
CGameObject::CGameObject(int _type, cocos2d::CCScene* parent, CGameController* controller)
	: scene(parent)
	, type(_type)
	, selected(false)
	, selection(NULL)
	, gc(controller)
{
}
CGameObject::~CGameObject()
{
	decorator->removeFromParent();
	if (selected)
	{
		selection->removeFromParent();
	}
}
void CGameObject::load()
{
}
void CGameObject::update(float dt)
{
	decorator->setPosition(screenPosition);
}
void CGameObject::remove()
{
}
cocos2d::CCSprite* CGameObject::getDecorator()
{
	return decorator;
}
void CGameObject::setDecorator(cocos2d::CCSprite* sprite)
{
	decorator = sprite;
}
cocos2d::CCScene* CGameObject::getScene()
{
	return scene;
}
void CGameObject::setScene(cocos2d::CCScene* scn)
{
	scene = scn;
}
void CGameObject::setScreenPosition(cocos2d::CCPoint p)
{
	screenPosition = p;
}
cocos2d::CCPoint CGameObject::getScreenPosition()
{
	return screenPosition;
}
void CGameObject::setTilePosition(cocos2d::CCPoint p)
{
	tilePosition = p;
}
cocos2d::CCPoint CGameObject::getTilePosition()
{
	return tilePosition;
}
int CGameObject::getType()
{
	return type;
}
void CGameObject::setType(int typ)
{
	type = typ;
}
CGameObject* CGameObject::onTouch(cocos2d::CCPoint point)
{
	float zoomFactor = 1.0f;//cocos2d::CCEGLView::sharedOpenGLView()->getFrameZoomFactor();
	cocos2d::CCRect bound( getScreenPosition().x - getBounds().size.width / (2.0f * zoomFactor), 
					   getScreenPosition().y - getBounds().size.height / (2.0f * zoomFactor),
					   getBounds().size.width / zoomFactor,
					   getBounds().size.height / zoomFactor);
	if (selected)
	{
		selection->removeFromParent();
	} 
	else if (bound.containsPoint(point))
	{
		selection = cocos2d::CCSprite::createWithSpriteFrameName("select-tile2.png");
		selection->setPosition(getScreenPosition());
		selection->setAnchorPoint(cocos2d::CCPoint(0.5f, 0.5f));
		selection->setScale(1.2f);
		scene->addChild(selection);
		selected = true;
		return this;
	}
	selected = false;
	return NULL;
}
/**
 *  state callbacks
 */
void CGameObject::onExitState(int state)
{
}