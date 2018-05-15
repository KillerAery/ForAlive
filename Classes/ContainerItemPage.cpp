#include "ContainerItemPage.h"
#include "BackPackUITemplate.h"

ContainerItemPage::ContainerItemPage():m_sumlabel(nullptr){}

bool ContainerItemPage::init(Item* item) {
	if (!ItemPage::init(item))return false;
	//获取UI模板
	auto layout = BackPackUITemplate::getInstance()->getBasicContainerItemPage();
	//物品图片
	auto sprite = Sprite::create("Item/" + m_item->getName() + ".png");
	sprite->setPosition(layout->getContentSize().width / 8, layout->getContentSize().height / 2);
	layout->addChild(sprite);
	//物品名字
	auto name = Label::createWithSystemFont(m_item->getName(), "Arial", 20);
	name->setPosition(layout->getContentSize().width / 3, layout->getContentSize().height / 2);
	layout->addChild(name);
	//物品数量
	m_sumlabel = Label::createWithSystemFont("X" + cocos2d::StringUtils::toString(m_item->getSum()), "Arial", 20);
	m_sumlabel->setPosition(layout->getContentSize().width / 1.4, layout->getContentSize().height / 2);
	layout->addChild(m_sumlabel, 0, "num");

	layout->setAnchorPoint(Vec2(0.5, 0.5));
	layout->setVisible(true);

	addChild(layout);
	setAnchorPoint(Vec2(0.5, 0.5));
	setContentSize(layout->getContentSize());

	return true;
}


ContainerItemPage* ContainerItemPage::create(Item* item) {
	auto itempage = new (std::nothrow)ContainerItemPage();
	if (itempage &&itempage->init(item)) {
		itempage->autorelease();
	}
	else CC_SAFE_DELETE(itempage);
	return itempage;
}

void ContainerItemPage::refresh(){
	if (m_item&&m_item->getSum()>0){m_sumlabel->setString(cocos2d::StringUtils::format("X%d", m_item->getSum()));}
}