#include "WeaponGearItemPage.h"
#include "BackPackUITemplate.h"

using namespace cocos2d;

WeaponGearItemPage::WeaponGearItemPage() :m_layout(nullptr) {}

WeaponGearItemPage* WeaponGearItemPage::create(Item* item) {
	auto itempage = new (std::nothrow)WeaponGearItemPage();
	if (itempage &&itempage->init(item)) {
		itempage->autorelease();
	}
	else CC_SAFE_DELETE(itempage);
	return itempage;
}

bool WeaponGearItemPage::init(Item* item) {
	if (!ItemPage::init(item))return false;
	setAnchorPoint(Vec2(0.5,0.5));
	//获取UI模板
	m_layout = BackPackUITemplate::getInstance()->getBasicWeaponGearItemPage();
	m_layout->setAnchorPoint(Vec2(0.5, 0.5));
	m_layout->setVisible(true);
	this->addChild(m_layout);
	setContentSize(m_layout->getContentSize());

	//物品图片
	m_itemsprite = Sprite::create("Item/" + m_item->getName() + ".png");
	m_itemsprite->setAnchorPoint(Vec2(0,0.5));
	m_itemsprite->setPositionX(-getContentSize().width/2);
	this->addChild(m_itemsprite);
	//物品名字
	auto name = Label::createWithSystemFont(m_item->getName(), "Arial", 20);
	name->setPositionX(-getContentSize().width / 4);
	this->addChild(name);
	
	return true;
}
void WeaponGearItemPage::refresh() {
}