#ifndef __APP_GameController_H__
#define __APP_GameController_H__
#include "cocos2d.h"

USING_NS_CC;

class GameController : public cocos2d::Ref
{
public:
	GameController(void);
	~GameController(void);

	static GameController* getInstance();

	void run();

	void step(int step);
private:
	int stepCount;
	static GameController* _shared;

	void updateLoading(const int state);

	void runLuaFile(const std::string &filename);
};

#endif  // __APP_GameController_H__