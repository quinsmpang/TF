#include "MonsterBuilder.h"


namespace tables
{
	MonsterBuilder::MonsterBuilder(std::string *data)
	{
		rapidjson::Document rapidJsonData;
		rapidJsonData.Parse<0>(data->c_str());

		for (int i = 0; i < rapidJsonData.Size(); i++)
		{
			std::unique_ptr<MonsterBuilder_table> r(new MonsterBuilder_table);

			r->id = DICTOOL->getIntValue_json(rapidJsonData[i], "id");
			r->data = DICTOOL->getStringValue_json(rapidJsonData[i], "data");
			m_data[r->id] = std::move(r);
		}
	}


	MonsterBuilder::~MonsterBuilder(void)
	{

	}

	const char* MonsterBuilder::fileName()
	{
		return "data/Stage.json";
	}
}

