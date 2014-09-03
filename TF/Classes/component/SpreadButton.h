#ifndef __APP_SpreadButton_H__
#define __APP_SpreadButton_H__
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
	std::string hover;
	std::function<void()> callback;
} SpreadItem;

class SpreadButton : public Node
{
public:
	SpreadButton();
	~SpreadButton();

	static SpreadButton* create();

	void initSpread(const std::string &normal, const std::string &down, const std::string &hover);

	void setItems(std::vector<SpreadItem> items, POSITION position);
	
};

#endif  // __APP_SpreadButton_H__