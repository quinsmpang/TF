#include "SpreadButton.h"


SpreadButton::SpreadButton()
{
}


SpreadButton::~SpreadButton()
{
}

SpreadButton* SpreadButton::create()
{
	SpreadButton *spread = new (std::nothrow) SpreadButton();
	if (spread && spread->init())
	{
		spread->autorelease();
		return spread;
	}
	CC_SAFE_DELETE(spread);
	return nullptr;
}

void SpreadButton::initSpread(const std::string &normal, const std::string &down, const std::string &hover)
{
	auto sp = Sprite::create("towerBtn.png");
	this->addChild(sp);
}

void SpreadButton::setItems(std::vector<SpreadItem> items, POSITION position)
{

}



