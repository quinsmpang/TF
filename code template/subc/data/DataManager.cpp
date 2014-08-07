#include "DataManager.h"

#define LOAD_TABLE(tablePtr, tableClass, tableFile) std::string jsonpath = FileUtils::getInstance()->fullPathForFilename(tableFile);\
	std::string load_str = FileUtils::getInstance()->getStringFromFile(jsonpath.c_str());\
	tablePtr = new tableClass(&load_str);

static DataManager* _instance = nullptr;

DataManager::DataManager(void)
{
}


DataManager::~DataManager(void)
{

}

DataManager* DataManager::getInstance()
{
	if(_instance == nullptr)
	{
		_instance = new DataManager();
	}
	return _instance;
}

void DataManager::loadTable()
{
	LOAD_TABLE(m_MonsterBuilder, tables::MonsterBuilder, tables::MonsterBuilder::fileName());


}






