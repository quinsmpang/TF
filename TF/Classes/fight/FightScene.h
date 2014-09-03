#ifndef __TF_FightScene_H__
#define __TF_FightScene_H__

#include "cocos2d.h"
USING_NS_CC;

class FightScene : public Layer
{
public:
	FightScene();
	~FightScene();

	virtual bool init();

	static cocos2d::Scene* scene();

	CREATE_FUNC(FightScene);

	void onceUpdate(float f);

	void quickCallback(Ref* sender);
	void slowCallback(Ref* sender);

	void initTowerBtn();

	//touch
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);

	//еп╤о╠ъ╫Г
	Point boundLayer(Point pos);
};

#endif // __TF_FightScene_H__
