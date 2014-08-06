/****************************************************************************
Create:
@author	ybb
@data	2014-07-08
@describe Resource loading manager.
		  
*****************************************************************************/
#ifndef __loader_LoadingLayer_H__
#define __loader_LoadingLayer_H__

#include "cocos2d.h"
#include "LoaderItem.h"

USING_NS_CC;


enum LoaderEnum
{
	LOAD_IMAGE = 1,
	LOAD_FRAME = 2,
	LOAD_ARMATURE = 3
};

class LoaderManager
{
public:
	LoaderManager(void);
	~LoaderManager(void);

	static LoaderManager* getInstance();

	void LoadRes(const std::string &path, const std::function<void(int)>& callback);

	//////////////////////////////////////////////////////////////////////////

	Texture2D* addImage(const std::string &path);
	void addImageAsync(const std::string &path, const std::function<void(Texture2D*)>& callback);
	void addArmatureFileInfo(const std::string& configFilePath);
	void addArmatureFileInfoAsync(const std::string& configFilePath, Ref *target, SEL_SCHEDULE selector);
	void addArmatureFileInfoAsync(const std::string& imagePath, const std::string& plistPath, const std::string& configFilePath, Ref *target, SEL_SCHEDULE selector);
	void addSpriteFramesWithFile(const std::string& plist);

	void removeImage(const std::string &textureKeyName);
	void removeArmature(const std::string& configFilePath);
	void removeSpriteFrame(const std::string& plist);

	//////////////////////////////////////////////////////////////////////////

	//Show cache stats in the console. It can help us to check the memory leak problem.
	void showCacheStats();

private:
	std::vector<std::string> textureVec;
	std::vector<std::string> armatureVec;
	std::vector<std::string> spriteFramesVec;

private:
	int count;
	std::vector<std::string> vec;
	const std::function<void(int)> _callback;
};

#endif  // __loader_LoadingLayer_H__