#pragma once
#include "cocos2d.h"
USING_NS_CC;
class GameScene : public cocos2d::Layer
{
public:

	GameScene(void);
	~GameScene(void);

	virtual bool init();

	static cocos2d::Scene* scene();

	CREATE_FUNC(GameScene);

	void onceUpdate(float f);

	void quickCallback(Ref* sender);
	void slowCallback(Ref* sender);

	//touch
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);

	//еп╤о╠ъ╫Г
	Point boundLayer(Point pos);

};

