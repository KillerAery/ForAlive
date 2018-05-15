#include "WeaponAttachmentItemPage.h"

WeaponAttachmentItemPage::WeaponAttachmentItemPage() :m_itemsprite(nullptr){}

WeaponAttachmentItemPage* WeaponAttachmentItemPage::create(Item* item) {
	auto itempage = new (std::nothrow)WeaponAttachmentItemPage();
	if (itempage &&itempage->init(item)) {itempage->autorelease();}
	else CC_SAFE_DELETE(itempage);
	return itempage;
}

bool WeaponAttachmentItemPage::init(Item* item) {
	if (!ItemPage::init(item))return false;
	setAnchorPoint(Vec2(0.5, 0.5));
	//ÎïÆ·Í¼Æ¬
	m_itemsprite = Sprite::create("Item/" + m_item->getName() + ".png");
	addChild(m_itemsprite);
	setContentSize(m_itemsprite->getContentSize());
	return true;
}

void WeaponAttachmentItemPage::refresh() {
	if (m_itemsprite) { m_itemsprite->removeFromParent(); }
	m_itemsprite = Sprite::create("Item/" + m_item->getName() + ".png");
	addChild(m_itemsprite);
	setContentSize(m_itemsprite->getContentSize());
}