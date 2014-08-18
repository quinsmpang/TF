#include "${className}.h"

#define KEY ${key}

namespace tables
{
	${className}::${className}(unsigned const char* data, size_t size)
	{
		InterDataCarrier carrier(data, size, fileName());
		Error = carrier.Error;
		if (!Error.empty())
		{
			return;
		}

		for (size_t i = 0; i < carrier.GetRecordCount(); i++)
		{
			std::unique_ptr<${className}_table> r(new ${className}_table);
			<#list messages as message>
			r->${message.name} = ${message.method}
			</#list>

			m_data[KEY] = std::move(r);
		}
	}

	${className}::~${className}(void)
	{

	}

	${className}_table* ${className}::get${className}Vo(${parameter})
	{
		auto it = m_data.find(${dynamicKey});
		if (it == m_data.end())
		{
			return nullptr;
		} else {
			return &(*(*it).second);
		}
	}

	std::string ${className}::int2String(int num)
	{
		std::stringstream ss;
		std::string str;
		ss<<num;
		ss>>str;
		return str;
	}

	const char* ${className}::fileName()
	{
		return "${className}.csv";
	}
}