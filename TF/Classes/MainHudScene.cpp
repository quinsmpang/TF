#include "MainHudScene.h"
#include "loader/LoaderManager.h"
#include "loader/ResourceType.h"
#include "map/ScriptMapScene.h"

MainHudScene::MainHudScene()
{
}


MainHudScene::~MainHudScene()
{
}

Scene* MainHudScene::createScene()
{
	auto scene = Scene::create();
	MainHudScene *layer = MainHudScene::create();
	scene->addChild(layer);
	layer->setTag(1);
	return scene;
}

bool MainHudScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//LoaderManager::getInstance()->addSpriteFramesWithFile("compress/test.plist");


	Button* btn = Button::create(STAGE_BTN, STAGE_BTN);
	btn->addTouchEventListener(CC_CALLBACK_2(MainHudScene::touchEvent, this));
	btn->setPosition(Vec2(400, 400));
	this->addChild(btn);


	auto sp = Sprite::create(STAGE_BTN);
	this->addChild(sp);



	return true;
}

void MainHudScene::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		log("=============>>>into scriptMap!");
		Director::getInstance()->replaceScene(ScriptMapScene::scene());
	}

	
}


