#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__
#include <vector>
#include <cocos2d.h>
class CGameObject;
class CConsumableObject;
class CGameController
{
private:
	CGameController() ;
	virtual ~CGameController();
public:
	static CGameController& instance()
	{
	    static CGameController controller;
	    return controller;		
	}
	void init();
	void populateTile(int row, int col, int type, int subtype);
	void loadBoardSettings(int nrows, int ncols, int ox, int oy, int px, int py);
	void loadBackground(const char* filename);
	void update(float dt);
	void onTouch(cocos2d::CCPoint point);
private:
	cocos2d::CCScene* scene;
	std::vector<CGameObject*>** grid;
	// board configuration
	unsigned gridSizeX;
	unsigned gridSizeY;
	unsigned offsetX;
	unsigned offsetY;
	unsigned paddingX;
	unsigned paddingY;
	// keep track of object selections 
	CGameObject* selections[2];
	int selectionIndex;
};
#endif
