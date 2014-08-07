#include "MonsterManager.h"
#include "MapManager.h"
#include "cocostudio/DictionaryHelper.h"
#include "data/DataManager.h"
#include "utils/Tools.h"

using namespace cocostudio;

static MonsterManager* _instance = nullptr;
MonsterManager::MonsterManager(void)
{
	
}


MonsterManager::~MonsterManager(void)
{
}

MonsterManager* MonsterManager::getInstance()
{
	if(_instance == nullptr)
	{
		_instance = new MonsterManager();
	}
	return _instance;
}

void MonsterManager::initStageData(int stage)
{
	auto& data = GET_MONSTERBUILDER_DATA(stage);
	if(&data)
	{
		std::vector<std::string> wave = Tools::splitStr(data.data, "#");
		int i = 1;
		for (auto str : wave)
		{
			log("%d==>>%s", i, str.c_str());
			waveMap[i] = str;
			i++;
		}
	} else {
		log("Error:Stage data is NULL!");
	}
	initMonsterByWave(1);
}

void MonsterManager::initMonsterByWave(int wave)
{
	auto waveStr = waveMap[wave];
	std::vector<std::string> monsters = Tools::splitStr(waveStr, ":");
	for (auto monster : monsters)
	{
		log("monster>>%s", monster.c_str());
		std::vector<std::string> parm = Tools::splitStr(monster, ",");
		auto monster = new Monster();
		monster->id = Tools::str2num(parm[0]);
		monster->delayTime = Tools::str2num(parm[1]);

		//设置怪物行走路线
		TMXObjectGroup *group = MapManager::getInstance()->getCurrMap()->getObjectGroup("way_" + parm[2]);
		monster->createMonster(group);
		monster->retain();
		monsterVec.pushBack(monster);
	}
	monsterVec.reverse();
}


float MonsterManager::addOne(Node *parent)
{
	if (monsterVec.size() <= 0)
	{
		return -1;
	}
	Monster *monster = monsterVec.back();
	monsterVec.popBack();
	monster->initMonster();
	parent->addChild(monster);
	activeMonster.pushBack(monster);
	return monster->delayTime;
}

void MonsterManager::update(float f)
{
	
}

void MonsterManager::test(int type)
{
	for (auto monster : activeMonster)
	{
		monster->addBuff(type);
	}
}




