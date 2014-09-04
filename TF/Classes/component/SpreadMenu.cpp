
#include "SpreadMenu.h"


SpreadMenu::SpreadMenu()
{
}


SpreadMenu::~SpreadMenu()
{
}

SpreadMenu* SpreadMenu::create()
{
	SpreadMenu *spread = new (std::nothrow) SpreadMenu();
	if (spread && spread->init())
	{
		spread->autorelease();
		return spread;
	}
	CC_SAFE_DELETE(spread);
	return nullptr;
}

void SpreadMenu::initSpread(const std::string &normal, const std::string &down, POSITION position, int id)
{
	_normalTexture = normal;
	_downTexture = down;
	_position = position;
	_isShow = false;
	_mainId = id;
}

void SpreadMenu::setItems(std::vector<SpreadItem*> items, std::function<void(int, int)> callback)
{
	Vector<MenuItem*> menuVec;

	//Init main menu
	auto mainItem = MenuItemImage::create(_normalTexture, _downTexture,
		CC_CALLBACK_1(SpreadMenu::mainMenuCallback, this));
	mainItem->setAnchorPoint(Vec2::ZERO);
	menuVec.pushBack(mainItem);

	//Init sub menu
	for (auto item : items)
	{
		auto subItem = MenuItemImage::create(item->normal, item->down,
			CC_CALLBACK_1(SpreadMenu::menuCallback, this));
		_callback = callback;
		subItem->setAnchorPoint(Vec2::ZERO);
		subItem->setPosition(Point(100, 100));
		subItem->setTag(item->id);
		menuVec.pushBack(subItem);
		delete item;	//clear
		item = nullptr;		//set null
	}

	auto menu = Menu::createWithArray(menuVec);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

void SpreadMenu::mainMenuCallback(Ref* sender)
{
	if (_isShow)
	{

		_isShow = false;
	}
	else {

		_isShow = true;
	}
}

void SpreadMenu::menuCallback(Ref* sender)
{
	auto item = dynamic_cast<MenuItemImage*>(sender);
	_callback(_mainId, item->getTag());
}
