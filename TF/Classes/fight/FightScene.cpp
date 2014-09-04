#include "fight\FightScene.h"
#include "TFMacro.h";
#include "fight\MonsterManager.h"
#include "fight\MapManager.h"
#include "ResourceType.h"
#include "component\SpreadMenu.h"

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

	//初始化塔按钮
	initTowerBtn();

	MONSTER_MANAGER->initStageData(1);
	float delay = MONSTER_MANAGER->addOne(map);

	this->schedule(schedule_selector(FightScene::onceUpdate), delay);


	return true;
}

void FightScene::initTowerBtn()
{
	auto towers = MapManager::getInstance()->towers;

	//测试展开菜单
	auto sbt = SpreadMenu::create();
	sbt->initSpread(TOWER_BTN, TOWER_BTN, POSITION::CENTER, 1);
	sbt->setPosition(Point(200, 200));

	std::vector<SpreadItem*> items;

	auto item = new SpreadItem();
	item->id = 1;
	item->normal = MENU_ITEM_1;
	item->down = MENU_ITEM_2;

	items.push_back(item);

	sbt->setItems(items, CC_CALLBACK_2(FightScene::menuCallback, this));

	this->addChild(sbt);
	//测试展开菜单结束

	for (Point p : towers)
	{
		auto sp = Sprite::create(TOWER_BTN);
		sp->setPosition(p);
		sp->setAnchorPoint(Point(0, 0));
		this->addChild(sp);
	}
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

void FightScene::menuCallback(int id, int subId)
{
	log("%d===%d", id, subId);
}