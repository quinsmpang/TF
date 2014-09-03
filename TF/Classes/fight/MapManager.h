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

	//��ʼ����ͼ
	TMXTiledMap* initMap(const std::string &filename);

	static MapManager* getInstance();

	TMXTiledMap* getCurrMap(){ return _currMap; };

public:
	std::vector<Point> towers;

private:
	TMXTiledMap* _currMap;


};

