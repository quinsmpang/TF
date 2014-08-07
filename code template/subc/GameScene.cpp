#include "fight/GameScene.h"
#include "fight/MapManager.h"
#include "fight/MonsterManager.h"
#include "global.h"
#include "data/DataManager.h"

GameScene::GameScene(void)
{
}


GameScene::~GameScene(void)
{
}

Scene* GameScene::scene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	GameScene *layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GameScene::init()
{

	if ( !Layer::init() )
	{
		return false;
	}

	///////////////////////////////////////////////////////////////////////
	////							Test							  /////
	///////////////////////////////////////////////////////////////////////
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto quickItem = MenuItemImage::create(
		"quick.png", "quick.png", CC_CALLBACK_1(GameScene::quickCallback,this));

	quickItem->setPosition(Point(visibleSize) - Point(quickItem->getContentSize() / 2) - Point(0, 100));

	auto slowItem = MenuItemImage::create(
		"slow.png", "slow.png", CC_CALLBACK_1(GameScene::slowCallback,this));

	slowItem->setPosition(Point(visibleSize) - Point(slowItem->getContentSize() / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(quickItem, slowItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);


	DataManager::getInstance()->loadTable();

	

	///////////////////////////////////////////////////////////////////////
	////							Test							   ////
	///////////////////////////////////////////////////////////////////////


	auto map = MapManager::getInstance()->initMap("tile/TF.tmx");
	map->setPositionX(20);
	this->addChild(map);
	map->setTag(MAP_TAG);

	MONSTER_MANAGER->initStageData(1);
	float delay = MONSTER_MANAGER->addOne(map);
	
	//this->scheduleOnce(schedule_selector(GameScene::onceUpdate), delay);

	this->schedule(schedule_selector(GameScene::onceUpdate), delay);

	auto eventDispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void GameScene::onceUpdate(float f)
{
	auto _map = this->getChildByTag(MAP_TAG);
	float delay = MONSTER_MANAGER->addOne(_map);
	log("onceUpdate>>>%f", delay);
	this->unscheduleAllSelectors();
	if (delay != -1)
	{
		this->schedule(schedule_selector(GameScene::onceUpdate), delay);
	}
}

void GameScene::quickCallback(Ref* sender)
{
	MONSTER_MANAGER->test(1);
}

void GameScene::slowCallback(Ref* sender)
{
	MONSTER_MANAGER->test(2);
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event)
{

	return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *unused_event)
{
	auto _map = this->getChildByTag(MAP_TAG);
	Point oldPoint = touch->getPreviousLocation();
	Point tran =  touch->getLocation() - oldPoint;
	Point newPos = _map->getPosition() + tran;
	_map->setPosition(boundLayer(newPos));
}

void GameScene::onTouchEnded(Touch *touch, Event *unused_event)
{

}

Point GameScene::boundLayer(Point pos)
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
