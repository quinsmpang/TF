#include "StringUtil.h"


StringUtil::StringUtil()
{
}


StringUtil::~StringUtil()
{
}

std::vector<std::string> StringUtil::split(const std::string &str, const std::string &ch)
{
	std::vector<std::string> vec;
	std::string strTmp = str;
	size_t cutAt;
	while ((cutAt = strTmp.find_first_of(ch)) != strTmp.npos)
	{
		if (cutAt > 0)
		{
			const std::string &temp = strTmp.substr(0, cutAt);
			vec.push_back(temp);
		}
		strTmp = strTmp.substr(cutAt + 1);
	}

	if (strTmp.length() > 0)
	{
		vec.push_back(strTmp);
	}
	return vec;
}

std::string StringUtil::valueOf(int val)
{
	char strBuffer[16];
	sprintf(strBuffer, "%d", val);
	return std::string(strBuffer);
}
std::string StringUtil::valueOf(float val)
{
	return "";
}
std::string StringUtil::valueOf(double val)
{
	return "";
}