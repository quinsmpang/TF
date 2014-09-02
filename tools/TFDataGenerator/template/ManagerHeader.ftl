#ifndef __APP_DataManager_H__
#define __APP_DataManager_H__

<#list messages as message>
#include "${message.name}.h"
</#list>

USING_NS_CC;

#define TABLESNUM ${fileSize}
typedef std::function<void(int)> loadCallback;

class DataManager
{
public:
	DataManager(void);
	~DataManager(void);

	static DataManager* getInstance();

	void loadTable(const loadCallback& callback, std::string localConfig);
	
	<#list messages as message>
	tables::${message.name}* m_${message.name};
	</#list>

<#list messages as message>
#define ${message.attributeType}_TABLE (DataManager::getInstance()->m_${message.name})
#define GET_${message.attributeType}_DATA	(&(DataManager::getInstance()->m_${message.name}->m_data))
</#list>
};

#endif  // __APP_DataManager_H__