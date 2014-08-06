#include "GameController.h"
#include "LoadingScene.h"
#include "MainHudScene.h"

GameController* GameController::_shared;

GameController::GameController(void)
{
	stepCount = 0;
}


GameController::~GameController(void)
{
}

GameController* GameController::getInstance(){
	if(_shared == nullptr)
	{
		_shared = new GameController();
	}
	return _shared;
}

void GameController::run()
{
	step(++stepCount);
}

void GameController::step(int step)
{
	switch (step)
	{
	case 1: 
		log("Into loading...");
		Director::getInstance()->runWithScene(LoadingScene::scene());
		break;
	case 2: // cpp
		updateLoading(LoadingEnum::CHECK_UPDATE);
		break;
	case 3: // cpp
		updateLoading(LoadingEnum::LOAD_TABLES);
		break;
	case 4: // cpp
		updateLoading(LoadingEnum::LOAD_RESOURCE);
		break;
	case 5: // lua
		log("Into Login...");
		run();
		break;
	case 6: 
		log("Into Game Hud...");
		Director::getInstance()->replaceScene(MainHudScene::createScene());
		break;
	}
}

void GameController::updateLoading(const int state)
{
	auto scene = Director::getInstance()->getRunningScene();
	auto load = (LoadingScene*)(scene->getChildByTag(1));
	load->updateLoading(state);
}

void GameController::runLuaFile(const std::string &filename)
{

}






