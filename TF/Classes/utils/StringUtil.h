#ifndef __TF_StringUtil_H__
#define __TF_StringUtil_H__
#include "cocos2d.h"

class StringUtil
{
public:
	StringUtil();
	~StringUtil();

	//split string
	static std::vector<std::string> split(const std::string &str, const std::string &ch);

	static std::string valueOf(int val);
	static std::string valueOf(float val);
	static std::string valueOf(double val);
};

#endif // __TF_StringUtil_H__