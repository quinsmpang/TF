/****************************************************************************
Copyright (c) SunnyYue
Date 2014-09-05
Version 1.0.1

http://www.ituuz.com/
http://blog.csdn.net/letthinking

This component is based on the Cocos2d-x 3.2 version.

****************************************************************************/

#ifndef __APP_SpreadMenu_H__
#define __APP_SpreadMenu_H__
#include "cocos2d.h"

USING_NS_CC;

enum POSITION
{
	TOP = 1,
	DOWN = 2,
	LEFT = 3,
	RIGHT = 4,
	CENTER = 0
};

typedef struct s_item
{
	int id;
	std::string normal;
	std::string down;
} SpreadItem;

class SpreadMenu : public Node
{
public:
	SpreadMenu();
	~SpreadMenu();

	static SpreadMenu* create();

	void menuCallback(Ref* sender);

	void mainMenuCallback(Ref* sender);

	void initSpread(const std::string &normal, const std::string &down, POSITION position, int id);

	void setItems(std::vector<SpreadItem*> items, std::function<void(int, int)> callback);
	
private:
	std::function<void(int, int)> _callback;
	std::string _normalTexture;
	std::string _downTexture;
	POSITION _position;
	bool _isShow; 
	int _mainId;
};

#endif  // __APP_SpreadMenu_H__