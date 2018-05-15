#include "GearItemPage.h"

GearItemPage::GearItemPage():m_itemsprite(nullptr){}

GearItemPage* GearItemPage::create(Item* item) {
	auto itempage = new (std::nothrow)GearItemPage();
	if (itempage &&itempage->init(item)){
		itempage->autorelease(); 
	}
	else CC_SAFE_DELETE(itempage);
	return itempage;
}

bool GearItemPage::init(Item* item) {
	if (!ItemPage::init(item))return false;
	setAnchorPoint(Vec2(0.5, 0.5));
	//ÎïÆ·Í¼Æ¬
	m_itemsprite = Sprite::create("Item/"+m_item->getName()+".png");
	addChild(m_itemsprite);
	setContentSize(m_itemsprite->getContentSize());
	return true;
}

void GearItemPage::refresh(){
if (m_itemsprite){m_itemsprite->removeFromParent();}
m_itemsprite = Sprite::create("Item/" + m_item->getName() + ".png");
addChild(m_itemsprite);
setContentSize(m_itemsprite->getContentSize());
}