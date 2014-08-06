/****************************************************************************
Create:
@author	ybb
@data	2014-07-09
@describe 游戏初始加载对象，保存加载类型，文件目录等信息。
*****************************************************************************/
#ifndef __loader_LoaderItem_H__
#define __loader_LoaderItem_H__
#include "cocos2d.h"

class LoaderItem : public cocos2d::Ref
{
public:
	LoaderItem(void);
	~LoaderItem(void);

public:
	std::string url;
	int type;
};

#endif  // __loader_LoaderItem_H__
