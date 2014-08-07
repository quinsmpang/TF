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

	//��ʼ������
	void initMonster();
	//�����ƶ�
	void move();

	void addBuff(int type);

private:
	//��һ�������
	Point prePoint;
	//��ǰҪ�ƶ���ȥ�ĵ�
	int currPiont;
	//�����ٶ�
	float speed;
	//�ٶ�ϵ���� Ĭ��Ϊ1
	float modulus;
};

