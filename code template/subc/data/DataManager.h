#pragma once
#include "TableBase.h"

#include "MonsterBuilder.h"

USING_NS_CC;

class DataManager
{
public:
	DataManager(void);
	~DataManager(void);

	static DataManager* getInstance();

	void loadTable();

	tables::MonsterBuilder* m_MonsterBuilder;


#define GET_MONSTERBUILDER_DATA(i) (*(DataManager::getInstance()->m_MonsterBuilder->m_data[i]));

};

