#ifndef __TF_MainHudScene_H__
#define __TF_MainHudScene_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class MainHudScene : public cocos2d::Layer
{
public:
	MainHudScene();
	~MainHudScene();

	virtual bool init();
	//virtual void onEnter();
	//virtual void onExit();

	static Scene* createScene();
	CREATE_FUNC(MainHudScene);

	void touchEvent(Ref *pSender, Widget::TouchEventType type);
};
#endif // __TF_MainHudScene_H__
