#ifndef __APP_MonsterBuilder_H__
#define __APP_MonsterBuilder_H__
#include "TableBase.h"

namespace tables
{
	class MonsterBuilder_table : public TableBase
	{
	public:
		int id;
		std::string data;

		MonsterBuilder_table()
		{
			memset(&id, 0, sizeof(id));
			memset(&data, 0, sizeof(data));
		}
	};

	class MonsterBuilder
	{
	public:
		MonsterBuilder(std::string *data);
		~MonsterBuilder(void);
		std::map<int, std::unique_ptr<MonsterBuilder_table>> m_data;
		static const char* fileName();
	};
}


#endif  // __APP_MonsterBuilder_H__
