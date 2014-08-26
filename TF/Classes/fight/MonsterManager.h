#include "cocos2d.h"
#include "Monster.h"

USING_NS_CC;
class MonsterManager
{
public:
	MonsterManager(void);
	~MonsterManager(void);

	static MonsterManager* getInstance();

	void initStageData(int stage);

	void initMonsterByWave(int wave);

	float addOne(Node *parent);

	void update(float f);

	void test(int type);

private:

	//Vector<std::unique_ptr<Monster>> monsterVec;
	Vector<Monster*> monsterVec;

	Vector<Monster*> activeMonster;

	std::map<int, std::string> waveMap;
};

