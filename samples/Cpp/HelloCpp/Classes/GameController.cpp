#include <GameController.h>
#include <cocos2d.h>
#include <GameScene.h>
#include <DecoratorObject.h>
#include <ConsumableObject.h>
#include <ActorObject.h>
#include <CCLuaEngine.h>
/**
 *	Populate tiles with game entities
 *  params: row, col, type, subtype
 */
static int luaPopulateTile(lua_State *L)
{
	CGameController::instance().populateTile( lua_tonumber(L, 1), 
											  lua_tonumber(L, 2), 
											  lua_tonumber(L, 3),
											  lua_tonumber(L, 4));
	return 0;
}
/**
 * Loads board settings
 * Params: gridSizex, gridSizey, offsetX, offsetY, paddingX, paddingy
 */
static int luaSetBoardSettings(lua_State* L)
{
	CGameController::instance().loadBoardSettings( lua_tonumber(L, 1), 
											  lua_tonumber(L, 2), 
											  lua_tonumber(L, 3),
											  lua_tonumber(L, 4),
											  lua_tonumber(L, 5),
											  lua_tonumber(L, 6));
	return 0;
}
/**
 * Loads level background
 * Params: texture filename
 */
static int luaLoadBackground(lua_State* L)
{
	CGameController::instance().loadBackground(lua_tostring(L, 1));
	return 0;
}
/**
 *    CGameController
 *	  Game class controlling game related items and events
 */
CGameController::CGameController()
	: scene(NULL)
	, gridSizeX(0)
	, gridSizeY(0)
	, offsetX(0)
	, offsetY(0)
	, paddingX(0)
	, paddingY(0)
{
	selections[0] = NULL;
	selections[1] = NULL;
	selectionIndex = NULL;
}
CGameController::~CGameController()
{
	for (unsigned i = 0; i < gridSizeY; i++)
	{
		std::vector<CGameObject*>* container = grid[i];
		for (unsigned j = 0; j < gridSizeY; j++)
		{
			for (unsigned k = 0; k < container[j].size(); k++)
			{
				delete container[j][k];
				container[j][k] = NULL;
			}
			container[j].clear();
		}
	}
}
void CGameController::init()
{
	//  load atlases here
	cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("common.plist"); 
	//  create game scenes
	scene = GameScene::scene(this);
	//  select startup scene
	cocos2d::CCDirector::sharedDirector()->runWithScene(scene);
	//  map lua functions
	lua_State* L = ((cocos2d::CCLuaEngine*)cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine())->getLuaStack()->getLuaState();
	lua_pushcfunction(L, luaPopulateTile);
	lua_setglobal(L, "luaPopulateTile");
	lua_pushcfunction(L, luaSetBoardSettings);
	lua_setglobal(L, "luaSetBoardSettings");
	lua_pushcfunction(L, luaLoadBackground);
	lua_setglobal(L, "luaLoadBackground");
	//  load level
	cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeScriptFile("scripts/level1.lua");
}
void CGameController::loadBoardSettings(int nrows, int ncols, int ox, int oy, int px, int py)
{
	gridSizeX = nrows;
	gridSizeY = ncols;
	offsetX = ox;
	offsetY = oy;
	paddingX = px;
	paddingY = py;
	// center grid
	if (ox == -1 || oy == -1)
	{
		CDecoratorObject dummy(CDecoratorObject::OBJECT_TYPE_EMPTY_TILE, scene);
		cocos2d::CCRect rect = dummy.getBounds();
		int width = rect.getMaxX() - rect.getMinX();
		int height = rect.getMaxY() - rect.getMinY();
		int gridW = (width + px) * (nrows - 1);
		int gridH = (height + py) * (ncols - 1);
		cocos2d::CCSize size = cocos2d::CCDirector::sharedDirector()->getWinSize();
		offsetX =  size.width/2 - gridW/2;
		offsetY = size.height/2 + gridH/2;
	}
	// init grid
	grid = new std::vector<CGameObject*>*[gridSizeY];
	for (unsigned i = 0; i < gridSizeY; i++)
	{
		grid[i] = new std::vector<CGameObject*>[gridSizeX];
	}
}
void CGameController::loadBackground(const char* filename)
{
	cocos2d::CCSize size = cocos2d::CCDirector::sharedDirector()->getWinSize();
	cocos2d::CCSprite* pSprite = cocos2d::CCSprite::create(filename);
	pSprite->setAnchorPoint(cocos2d::CCPoint(0.5f, 0.5f));
	pSprite->setScale(3.0);
	pSprite->setPosition(cocos2d::CCPoint(size.width/2.0f, size.height/2.0f));
	scene->addChild(pSprite);
}
void CGameController::populateTile(int row, int col, int type, int subtype)
{
	CGameObject* go = NULL;
	if (type == CGameObject::OBJECT_TYPE_CONSUMABLE)
	{
		go = new CConsumableObject(subtype, scene);
		cocos2d::CCPoint position = cocos2d::CCPoint(grid[row][col][0]->getScreenPosition().x, 
													grid[row][col][0]->getScreenPosition().y);
		go->setScreenPosition(position);
	} 
	else if ( type == CGameObject::OBJECT_TYPE_DECORATOR)
	{
		go = new CDecoratorObject(CDecoratorObject::OBJECT_TYPE_EMPTY_TILE, scene);
		cocos2d::CCPoint position = cocos2d::CCPoint(offsetX + col * (go->getBounds().getMaxX() - go->getBounds().getMinX() + paddingX),
			offsetY - row * (go->getBounds().getMaxY() - go->getBounds().getMinY() + paddingY));
		go->setScreenPosition(position);
	}
	else if (type == CGameObject::OBJECT_TYPE_ACTOR)
	{
		go = new CActorObject(subtype, scene);
		cocos2d::CCPoint position = cocos2d::CCPoint(grid[row][col][0]->getScreenPosition().x, 
													grid[row][col][0]->getScreenPosition().y);
		go->setScreenPosition(position);
	}
	grid[row][col].push_back(go);
	go->setTilePosition(cocos2d::CCPoint(row, col));
}
void CGameController::update(float dt)
{
	for (unsigned row = 0; row < gridSizeY; row++)
	{
		for (unsigned col = 0; col < gridSizeX; col++)
		{
			for (unsigned k = 0; k < grid[row][col].size(); k++)
			{
				grid[row][col][k]->update(dt);
			}
		}
	}
}
void CGameController::onTouch(cocos2d::CCPoint point)
{
	for (unsigned row = 0; row < gridSizeY; row++)
	{
		for (unsigned col = 0; col < gridSizeX; col++)
		{
			for (unsigned k = 0; k < grid[row][col].size(); k++)
			{
				if (CGameObject* go = grid[row][col][k]->onTouch(point))
				{
					selections[selectionIndex] = go;
					selectionIndex = (selectionIndex + 1) % 2;
					if (!selectionIndex)
					{
						// react to one another
						selections[0]->doAction(selections[1]);
						selections[1]->doAction(selections[0]);
					}
					break;
				}
			}
		}
	}
}
