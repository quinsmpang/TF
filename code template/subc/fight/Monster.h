#include "cocos2d.h"
USING_NS_CC;

class Monster : public cocos2d::Node
{
public:
	Monster(void);
	~Monster(void);
	//////////////////////////////////////////////////////////////////////////

	int id;
	float delayTime;

	//////////////////////////////////////////////////////////////////////////

	std::map<int, Point> wayMap;

	void createMonster(TMXObjectGroup *group);

	//初始化怪物
	void initMonster();
	//怪物移动
	void move();

	void addBuff(int type);

private:
	//上一个坐标点
	Point prePoint;
	//当前要移动过去的点
	int currPiont;
	//怪物速度
	float speed;
	//速度系数， 默认为1
	float modulus;
};

