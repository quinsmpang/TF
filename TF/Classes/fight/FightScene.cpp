#include "fight/FightScene.h"
#include "TFMacro.h";
#include "fight/MonsterManager.h"
#include "fight/MapManager.h"

FightScene::FightScene()
{
}


FightScene::~FightScene()
{
}

Scene* FightScene::scene()
{
	auto layer = FightScene::create();

	auto scene = Scene::create();
	scene->addChild(layer);

	return scene;
}

bool FightScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto map = MapManager::getInstance()->initMap("tile/TF.tmx");
	this->addChild(map);
	map->setTag(MAP_TAG);

	MONSTER_MANAGER->initStageData(1);
	float delay = MONSTER_MANAGER->addOne(map);

	this->schedule(schedule_selector(FightScene::onceUpdate), delay);


	return true;
}


void FightScene::onceUpdate(float f)
{
	auto _map = this->getChildByTag(MAP_TAG);
	float delay = MONSTER_MANAGER->addOne(_map);
	log("onceUpdate>>>%f", delay);
	this->unscheduleAllSelectors();
	if (delay != -1)
	{
		this->schedule(schedule_selector(FightScene::onceUpdate), delay);
	}
}

void FightScene::quickCallback(Ref* sender)
{
	MONSTER_MANAGER->test(1);
}

void FightScene::slowCallback(Ref* sender)
{
	MONSTER_MANAGER->test(2);
}

bool FightScene::onTouchBegan(Touch *touch, Event *unused_event)
{

	return true;
}

void FightScene::onTouchMoved(Touch *touch, Event *unused_event)
{
	auto _map = this->getChildByTag(MAP_TAG);
	Point oldPoint = touch->getPreviousLocation();
	Point tran = touch->getLocation() - oldPoint;
	Point newPos = _map->getPosition() + tran;
	_map->setPosition(boundLayer(newPos));
}

void FightScene::onTouchEnded(Touch *touch, Event *unused_event)
{

}

Point FightScene::boundLayer(Point pos)
{
	Size winSize = Director::getInstance()->getWinSize();
	auto _map = this->getChildByTag(MAP_TAG);
	Point retval = pos;

	retval.x = MIN(retval.x, 0);
	retval.x = MAX(retval.x, -_map->getContentSize().width + winSize.width);

	retval.y = MIN(retval.y, 0);
	retval.y = MAX(retval.y, -_map->getContentSize().height + winSize.height);

	return retval;
}
