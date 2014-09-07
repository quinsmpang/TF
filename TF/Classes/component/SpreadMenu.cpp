
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
	//Init main menu
	auto mainItem = MenuItemImage::create(_normalTexture, _downTexture,
		CC_CALLBACK_1(SpreadMenu::mainMenuCallback, this));
	mainItem->setAnchorPoint(Vec2::ZERO);
	_menuVec.pushBack(mainItem);

	//Init sub menu
	for (auto item : items)
	{
		if (item->id < 0) log("WARN:item's id must be larger than 0.");
		auto subItem = MenuItemImage::create(item->normal, item->down,
			CC_CALLBACK_1(SpreadMenu::menuCallback, this));
		_callback = callback;
		subItem->setTag(item->id);
		_menuVec.pushBack(subItem);
		subItem->setOpacity(0);
		subItem->setEnabled(false);
		subItem->setAnchorPoint(Vec2::ZERO);
		delete item;	//clear
		item = nullptr;		//set null
	}

	auto menu = Menu::createWithArray(_menuVec);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	menu->setName(MAIN_MENU_NAME);
	
	//Setting position.
	initPosition();
}

void SpreadMenu::mainMenuCallback(Ref* sender)
{
	if (_isShow)
	{
		for (auto item : _menuVec)
		{
			int t = item->getTag();
			if (t > 0)
			{
				item->setEnabled(false);
				item->runAction(FadeOut::create(0.3f));
			}
		}
		_isShow = false;
	}
	else {
		for (auto item : _menuVec)
		{
			int t = item->getTag();
			if (t > 0)
			{
				item->setEnabled(true);
				item->runAction(FadeIn::create(0.3f));
			}
		}
		_isShow = true;
	}
}

void SpreadMenu::FadeIn()
{
	_isShow = false;
	mainMenuCallback(nullptr);
}

void SpreadMenu::FadeOut()
{
	_isShow = true;
	mainMenuCallback(nullptr);
}

void SpreadMenu::menuCallback(Ref* sender)
{
	auto item = dynamic_cast<MenuItemImage*>(sender);
	_callback(_mainId, item->getTag());
}

void SpreadMenu::initPosition()
{
	int mwidth = 0, mheight = 0;
	int width = 0;
	int initX = 0, initY = 0;
	int iconut = _menuVec.size() - 1;
	int space = 5;

	for (auto item : _menuVec)
	{
		int t = item->getTag();
		if (t > 0)
		{
			if (width == 0)
			{
				width = item->getContentSize().width;
				auto p = getStartPoint(width, mwidth, mheight, iconut, space);
				initX = p.x;
				initY = p.y;
			}
			item->setPosition(Point(initX, initY));
			initX = initX + space + width;
		}
		else {
			mwidth = item->getContentSize().width;
			mheight = item->getContentSize().height;
		}
	}
}

Point SpreadMenu::getStartPoint(int width, int mwidth, int mheight, int iconut, int space)
{	
	int initX = 0, initY = 0;
	switch (_position)
	{
	case TOP_LEFT:
		initX = -((iconut - 1) * space + (iconut - 1) * width);
		initY = mheight + space;
		break;
	case TOP_RIGHT:
		initX = 0;
		initY = mheight + space;
		break;
	case TOP_CENTER:
		initX = -(((iconut - 1) * space + iconut * width) / 2 - mwidth / 2);
		initY = mheight + space;
		break;
	case DOWN_LEFT:
		initX = -((iconut - 1) * space + (iconut - 1) * width);
		initY = -(mheight + space);
		break;
	case DOWN_RIGHT:
		initX = 0;
		initY = -(mheight + space);
		break;
	default:
		initX = -(((iconut - 1) * space + iconut * width) / 2 - mwidth / 2);
		initY = -(mheight + space);
		break;
	}
	return Point(initX, initY);
}
