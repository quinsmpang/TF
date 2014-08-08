#include "DataManager.h"

#define LOAD_TABLE(tablePtr, tableClass, tableFile, callback, count) \
	{\
	std::string jsonpath = FileUtils::getInstance()->fullPathForFilename(str_replace(tableClass::fileName(), localConfig));\
	data = FileUtils::getInstance()->getDataFromFile(jsonpath);\
	tablePtr = new tableClass(data.getBytes(), (int)data.getSize());\
	count++;\
	callback(count);\
	}

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

void DataManager::loadTable(const loadCallback& callback, int localConfig)
{
	int count = 0;
	Data data;
	<#list messages as message>
	LOAD_TABLE(m_${message.name}, tables::${message.name}, str_replace(tables::${message.name}::fileName(), localConfig), callback, count);
	</#list>

}

std::string DataManager::str_replace(std::string str, int config)
{
	std::string toTag;
	if (config == 0)
	{
		toTag = "cnData";
	}else {
		toTag = "enData";
	}
	str.replace(11, 10, toTag);
	return str;
}
