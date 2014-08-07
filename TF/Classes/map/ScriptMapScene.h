#ifndef __TF_ScriptMapScene_H__
#define __TF_ScriptMapScene_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class ScriptMapScene : public Layer
{
public:
	ScriptMapScene();
	~ScriptMapScene();

	virtual bool init();
	static Scene* scene();
	CREATE_FUNC(ScriptMapScene);

	void touchEvent(Ref *pSender, Widget::TouchEventType type);
};

#endif // __TF_ScriptMapScene_H__