#include "fight/Monster.h"

Monster::Monster(void)
{
	
}


Monster::~Monster(void)
{
	
}

void Monster::createMonster(TMXObjectGroup *group)
{
	auto sp = Sprite::create("menu1.png");
	sp->setAnchorPoint(Point(0, 0));
	this->addChild(sp);
	int count = 1;
	std::string temp = "point" + std::to_string((count));
	auto obj = group->getObject(temp);
	while (obj.begin() != obj.end())
	{
		float x = obj.at("x").asFloat();
		float y = obj.at("y").asFloat();
		
		wayMap.insert(std::map<int, Point>::value_type(count, Point(x, y)));
		count++;
		temp = "point" + std::to_string((count));
		obj = group->getObject(temp);
	}

}

void Monster::initMonster()
{
	speed = 1;
	currPiont = 1;
	modulus = 1;
	std::map<int, Point>::iterator iter = wayMap.find(currPiont);
	if (wayMap.end() != iter)
	{
		Point start = iter->second;
		prePoint = start;
		this->setPosition(start);
		currPiont++;
		move();
	}
}


void Monster::move()
{
	std::map<int, Point>::iterator iter = wayMap.find(currPiont);
	if (wayMap.end() != iter)
	{
		Point to = iter->second;
		float dura = std::sqrt((to.y - prePoint.y) * (to.y - prePoint.y) + (to.x - prePoint.x) * (to.x - prePoint.x)) / (speed * modulus * 100);
		currPiont++;
		auto action = Sequence::create(
			 MoveTo::create(dura, to),
			 CallFuncN::create(CC_CALLBACK_0(Monster::move, this)),
			 NULL);
		this->runAction(action);
		prePoint = to;
	} else {
		this->release();
		this->removeFromParent();
	}
}

void Monster::addBuff(int type)
{
	if (type == 1)
	{
		modulus = 1.5;
	} else if (type == 2) {
		modulus = 0.5;
	}
	auto manager = Director::getInstance()->getActionManager();
	manager->removeAllActionsFromTarget(this);

	Point curr = this->getPosition();
	float dura = std::sqrt((prePoint.y - curr.y) * (prePoint.y - curr.y) + (prePoint.x - curr.x) * (prePoint.x - curr.x)) / (speed * modulus * 100);
	auto action = Sequence::create(
		MoveTo::create(dura, prePoint),
		CallFuncN::create(CC_CALLBACK_0(Monster::move, this)),
		NULL);
	this->runAction(action);
}

