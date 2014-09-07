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

#define MAIN_MENU_NAME "__APP_SpreadMenu_H__"

enum POSITION
{
	TOP_LEFT = 1,
	TOP_RIGHT = 2,
	TOP_CENTER = 3,
	DOWN_LEFT = 4,
	DOWN_RIGHT = 5,
	DOWN_CENTER = 6
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

	//WARN:item's id must be larger than 0.
	void setItems(std::vector<SpreadItem*> items, std::function<void(int, int)> callback);

	void FadeIn();

	void FadeOut();
private:
	Point getStartPoint(int w, int mw, int mh, int icount, int space);
	//init sub items position
	void initPosition();

private:
	Vector<MenuItem*> _menuVec;
	std::function<void(int, int)> _callback;
	std::string _normalTexture;
	std::string _downTexture;
	POSITION _position;
	bool _isShow; 
	int _mainId;
};

#endif  // __APP_SpreadMenu_H__