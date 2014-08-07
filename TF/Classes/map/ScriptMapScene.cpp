#include "ScriptMapScene.h"
#include "loader/ResourceType.h"

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

	Button* btn = Button::create(STAGE_1, STAGE_2);
	btn->addTouchEventListener(CC_CALLBACK_2(ScriptMapScene::touchEvent, this));
	btn->setPosition(Vec2(600, 600));
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

