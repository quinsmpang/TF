#ifndef __TF_LoadingScene_H__
#define __TF_LoadingScene_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

enum LoadingEnum
{
	CHECK_UPDATE = 1,
	LOAD_TABLES = 2,
	LOAD_RESOURCE = 3,
	LOAD_OVER = 0
};

class LoadingScene : public cocos2d::Layer
{
public:
	LoadingScene();
	~LoadingScene();

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	void update(float dt);

	static cocos2d::Scene* scene();
	CREATE_FUNC(LoadingScene);

	void updateLoading(const int state);
	void touchEvent(Ref *pSender, Widget::TouchEventType type);
	void loadRes();
	void loadResCallback(int p);
	void setProcess(int process);

protected:
	std::thread* _loadingThread;

private:
	
	int currState;
};


#endif // __TF_LoadingScene_H__




