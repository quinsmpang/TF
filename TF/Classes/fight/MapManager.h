#include "cocos2d.h"
USING_NS_CC;

/************************************************************************/
/* Map manager                                                          */
/*
/************************************************************************/
class MapManager
{
public:
	MapManager(void);
	~MapManager(void);

	//≥ı ºªØµÿÕº
	TMXTiledMap* initMap(const std::string &filename);

	static MapManager* getInstance();

	TMXTiledMap* getCurrMap(){ return _currMap; };

private:
	TMXTiledMap* _currMap;
};

