/****************************************************************************
Create:
@author	ybb
@data	2014-07-09
@describe ��Ϸ��ʼ���ض��󣬱���������ͣ��ļ�Ŀ¼����Ϣ��
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
