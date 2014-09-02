#include "LoadingScene.h"
#include "GameController.h"
#include "loader/LoaderManager.h"
#include "tables/tables/DataManager.h"
#include "utils/StringUtil.h"

LoadingScene::LoadingScene()
{
}


LoadingScene::~LoadingScene()
{
}

Scene* LoadingScene::scene()
{
	auto scene = Scene::create();
	LoadingScene *layer = LoadingScene::create();
	scene->addChild(layer);
	layer->setTag(1);
	return scene;
}

bool LoadingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto size = Director::getInstance()->getWinSize();

	auto label = Label::createWithSystemFont("....", "Arial", 14);
	label->setPosition(Point(size.width/2, size.height/2));
	this->addChild(label);
	label->setTag(99);

	Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);

	return true;
}

void LoadingScene::onEnter()
{
	GameController::getInstance()->run();
}

void LoadingScene::onExit()
{
	_loadingThread->join();
	CC_SAFE_DELETE(_loadingThread);
}

void LoadingScene::setProcess(int p)
{
	auto label = (Label*)(this->getChildByTag(99));
	std::string str = StringUtil::valueOf(p);
	label->setString(str + "%");
}

void LoadingScene::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
	log("==============================");
}

void LoadingScene::updateLoading(const int state)
{
	currState = state;
	switch (state)
	{
	case LoadingEnum::CHECK_UPDATE:
		GameController::getInstance()->run();
		break;
	case LoadingEnum::LOAD_TABLES:
		DataManager::getInstance()->loadTable(CC_CALLBACK_1(LoadingScene::loadTableCallback, this), "staticdata");
		//GameController::getInstance()->run();
		break;
	case LoadingEnum::LOAD_RESOURCE:
		_loadingThread = new std::thread(&LoadingScene::loadRes, this);
		//GameController::getInstance()->run();
		break;
	default:
		break;
	}
}

void LoadingScene::loadRes()
{
	LoaderManager::getInstance()->LoadRes("config/file.xml", CC_CALLBACK_1(LoadingScene::loadResCallback, this));
}

void LoadingScene::loadResCallback(int p)
{
	log("===>>>%d", p);
	setProcess(p);
	if (p >= 100)
	{
		currState = LoadingEnum::LOAD_OVER;
	}
}

void LoadingScene::loadTableCallback(int p)
{
	log("===>>>%d", p);
	
	setProcess(p / TABLESNUM * 100);
	if (p >= TABLESNUM)
	{
		currState = LoadingEnum::LOAD_OVER;
	}
}

void LoadingScene::update(float dt)
{
	if (currState == LoadingEnum::LOAD_OVER)
	{
		GameController::getInstance()->run();
	}
}