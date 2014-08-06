#include "LoaderManager.h"
#include "cocostudio/CocoStudio.h"
#include "utils/pugixml.hpp"


#define REMOVE_ELE_FROM_VEC(vec, str) \
	std::vector<std::string>::iterator iter;\
	for (iter = vec.begin(); iter != vec.end(); iter++)\
	{\
	if (str == *iter)\
		{\
		vec.erase(iter);\
		break;\
		}\
	}

#define SHOW_VEC(vec) \
	{\
		std::vector<std::string>::iterator iter;\
		for (iter = vec.begin(); iter != vec.end(); iter++)\
		{\
			log("==%s", (*iter).c_str());\
		}\
	}
	

using namespace cocostudio;

static LoaderManager* _instance = nullptr;

LoaderManager::LoaderManager(void)
{
	
}

LoaderManager::~LoaderManager(void)
{
}

LoaderManager* LoaderManager::getInstance()
{
	if(_instance == nullptr)
	{
		_instance = new LoaderManager();
	}
	return _instance;
}

void LoaderManager::LoadRes(const std::string &path, const std::function<void(int)>& callback)
{
	count = 0;
	auto fullpath = FileUtils::getInstance()->fullPathForFilename(path);
	auto data = FileUtils::getInstance()->getDataFromFile(fullpath);

	pugi::xml_document* doc;
	if (&data == nullptr) log("file.xml loading error!");
	doc = new pugi::xml_document();
	doc->load_buffer(data.getBytes(), data.getSize());

	pugi::xml_node root = doc->child("files");
	pugi::xml_node syncItems = root.child("synchronizationLoader");
	for (pugi::xml_node item = syncItems.child("item"); item; item = item.next_sibling("item"))
	{
		std::string url = FileUtils::getInstance()->fullPathForFilename(item.attribute("url").as_string());
		vec.push_back(url);
	}

	for (auto url : vec)
	{
		addImage(url);
		count++;
		callback((float)count/(float)vec.size() * 100);
	}
}


Texture2D* LoaderManager::addImage(const std::string &path)
{
	textureVec.push_back(path);
	return Director::getInstance()->getTextureCache()->addImage(path);
}

void LoaderManager::addImageAsync(const std::string &path, const std::function<void(Texture2D*)>& callback)
{
	textureVec.push_back(path);
	Director::getInstance()->getTextureCache()->addImageAsync(path, callback);
}

void LoaderManager::addArmatureFileInfo(const std::string& configFilePath)
{
	armatureVec.push_back(configFilePath);
	ArmatureDataManager::getInstance()->addArmatureFileInfo(configFilePath);
}

void LoaderManager::addArmatureFileInfoAsync(const std::string& configFilePath, Ref *target, SEL_SCHEDULE selector)
{
	armatureVec.push_back(configFilePath);
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(configFilePath, target, selector);
}

void LoaderManager::addArmatureFileInfoAsync(const std::string& imagePath, const std::string& plistPath, const std::string& configFilePath, Ref *target, SEL_SCHEDULE selector)
{
	armatureVec.push_back(imagePath);
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(imagePath, plistPath, configFilePath, target, selector);
}

void LoaderManager::addSpriteFramesWithFile(const std::string& plist)
{
	spriteFramesVec.push_back(plist);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
}

void LoaderManager::removeImage(const std::string &textureKeyName)
{
	REMOVE_ELE_FROM_VEC(textureVec, textureKeyName);
	Director::getInstance()->getTextureCache()->removeTextureForKey(textureKeyName);
}

void LoaderManager::removeArmature(const std::string& configFilePath)
{
	REMOVE_ELE_FROM_VEC(armatureVec, configFilePath);
	ArmatureDataManager::getInstance()->removeArmatureFileInfo(configFilePath);
}

void LoaderManager::removeSpriteFrame(const std::string& plist)
{
	REMOVE_ELE_FROM_VEC(spriteFramesVec, plist);
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(plist);
}


void LoaderManager::showCacheStats()
{
	log("**************************************************************************");
	log("The texture size:%d", textureVec.size());
	SHOW_VEC(textureVec);
	log("--------------------------------------------------------------------------");
	log("The armature size:%d", armatureVec.size());
	SHOW_VEC(armatureVec);
	log("--------------------------------------------------------------------------");
	log("The spriteFrames size:%d", spriteFramesVec.size());
	SHOW_VEC(spriteFramesVec);
	log("**************************************************************************");
}

