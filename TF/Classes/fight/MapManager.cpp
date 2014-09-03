#include "fight/MapManager.h"
#include "ui/CocosGUI.h"

using namespace ui;

static MapManager* _instance = nullptr;

MapManager::MapManager(void)
{
}


MapManager::~MapManager(void)
{
}

MapManager* MapManager::getInstance()
{
	if(_instance == nullptr)
	{
		_instance = new MapManager();
	}
	return _instance;
}


TMXTiledMap* MapManager::initMap(const std::string &filename)
{
	_currMap = TMXTiledMap::create(filename);

	_currMap->getChildren();

	TMXObjectGroup *tower_group = MapManager::getInstance()->getCurrMap()->getObjectGroup("towers");

	auto& objects = tower_group->getObjects();
	for (auto& obj : objects)
	{
		ValueMap& dict = obj.asValueMap();

		float x = dict["x"].asFloat();
		float y = dict["y"].asFloat();
		float width = dict["width"].asFloat();
		float height = dict["height"].asFloat();
		towers.push_back(Point(x, y));
	}
	return _currMap;
}





