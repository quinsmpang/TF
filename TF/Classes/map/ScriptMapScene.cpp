#include "ScriptMapScene.h"
#include "loader/ResourceType.h"
#include "fight/FightScene.h"

ScriptMapScene::ScriptMapScene()
{
}


ScriptMapScene::~ScriptMapScene()
{
}

Scene* ScriptMapScene::scene()
{
	auto scene = Scene::create();
	ScriptMapScene *layer = ScriptMapScene::create();
	scene->addChild(layer);
	layer->setTag(1);
	return scene;
}

bool ScriptMapScene::init(){
	if (!Layer::init())
	{
		return false;
	}

	Button* btn = Button::create(STAGE_BTN, STAGE_BTN);
	btn->addTouchEventListener(CC_CALLBACK_2(ScriptMapScene::touchEvent, this));
	btn->setPosition(Vec2(100, 100));
	this->addChild(btn);

	return true;
}

void ScriptMapScene::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		log("=============>>>into script!");
		
	}


}

