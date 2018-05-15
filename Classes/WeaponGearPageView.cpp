#include "WeaponGearPageView.h"
#include "Biology.h"
#include "ItemMoveNode.h"

using namespace cocos2d;

WeaponGearPageView::WeaponGearPageView() :m_attachmentpages(5){}

bool WeaponGearPageView::init(Biology* b, int geartpyr, Layer* backpacklayer) {
	if (!Node::init())return false;
	CCASSERT(m_index <= RightHandGear, "m_index out of range!!!!");
	m_biology = b;
	m_index = geartpyr;
	initWeaponGearPageViewUI(backpacklayer);
	initItemPages();
	this->schedule(schedule_selector(WeaponGearPageView::updateRefresh), 0.1f);
	return true;
}

void WeaponGearPageView::initWeaponGearPageViewUI(Layer* backpacklayer) {
	//暂时增加 不推荐
	if (!backpacklayer)return;
	m_sprite = static_cast<ImageView*>(backpacklayer->getChildByTag(1)->getChildByTag(70 + m_index));
	this->setAnchorPoint(Vec2(0.5,0.5));
	this->setPosition(this->convertToNodeSpace(m_sprite->getWorldPosition()));

	//测试体积用
	//setBackGroundColorType(Layout::BackGroundColorType::SOLID);
	//setBackGroundColor(cocos2d::Color3B(255, 255, 255));

	this->setContentSize(Size(m_sprite->getContentSize().width*m_sprite->getParent()->getScaleX(), m_sprite->getContentSize().height*m_sprite->getParent()->getScaleY()));
}

void WeaponGearPageView::initItemPages(){
	if (m_index<GearTpye::LeftHandGear || m_index>GearTpye::RightHandGear || !m_biology->getGearVec()[m_index])return;
	//武器物品
	auto weaponitem = static_cast<ItemWeapon*>(m_biology->getGearVec()[m_index]);
	//武器装备项
	auto weaponitempage = WeaponGearItemPage::create(weaponitem);
	m_itempage = weaponitempage;
	this->addItemPage(m_itempage);
	//武器装备 携带的配件项
	auto weaponattachments = weaponitem->getAttacher().getItemAttachments();
	for (int i = 0; i < 5; ++i)
		if (weaponattachments[i]) {
			m_attachmentpages[i] = GearItemPage::create(weaponattachments[i]);
			m_attachmentpages[i]->setForwardPosition(weaponitempage->getLayout()->getChildByName(StringUtils::format("attachment%d", i))->getPosition() +(m_attachmentpages[i]->getContentSize() - m_itempage->getContentSize())/2);
			m_attachmentpages[i]->setPosition(m_attachmentpages[i]->getForwardPosition());
			this->addAttachmentItemPage(m_attachmentpages[i]);
		}

}

WeaponGearPageView* WeaponGearPageView::create(Biology* b, int geartpyr, Layer* backpacklayer) {
	auto gearpage = new (std::nothrow)WeaponGearPageView();
	if (gearpage &&gearpage->init(b, geartpyr, backpacklayer)) {
		gearpage->autorelease();
		s_itempageview_list.push_back(gearpage);
	}
	else CC_SAFE_DELETE(gearpage);
	return gearpage;
}

Container* WeaponGearPageView::getContainer() { return m_biology; }

//查询是否满足添加物品条件
bool WeaponGearPageView::ifaddItem(int id, int sum) {
	if (sum <= 0)return false;

	bool ret = false;

	double weight = ItemDataBase::getInstance()->getData(id,e_weight).asDouble();
	
	switch (Item::getItemTpye(id))
	{
	case ItemTpye::Weapon:
		ret = true;
		break;
	case ItemTpye::Attachment:
		ret = true;
		break;
	default:
		ret = false;
		break;
	}
	return ret;
}
bool WeaponGearPageView::ifaddItem(Item* item) {
	if (!item||item->getSum() <= 0)return false;

	switch (item->getItemTpye())
	{
	case ItemTpye::Weapon:
		return true;
	case ItemTpye::Attachment:
		return  m_biology->itemUseable(item, m_biology->getGearVec()[m_index], item->getSum());
	default:
		return false;
	}
}


bool WeaponGearPageView::preaddItem(int id, int sum) {
	bool ret = false;

	//auto item = ItemFactory::createItem(id, sum);
	////如果是武器,则 更换上去
	//if (item->getItemTpye() == ItemTpye::Weapon)
	//	ret = m_biology->wearGear(item, (GearTpye)m_index);

	////如果是配件，则使用上去
	//else if (item->getItemTpye() == ItemTpye::Attachment) {
	//	ret = m_biology->itemUseable(item, m_biology->getGearVec()[m_index], item->getSum());
	//	m_biology->useItem(item, m_biology->getGearVec()[m_index], item->getSum());
	//}
	////如果失败了，则回收内存
	//if (!ret)delete item;

	return ret;
}

bool WeaponGearPageView::preaddItem(Item* item) {
	bool ret = false;

	//如果是武器,则 更换上去
	if (item->getItemTpye() == ItemTpye::Weapon)
		ret = m_biology->wearGear(item,(GearTpye)m_index);
	
	//如果是配件，则使用上去
	else if (item->getItemTpye() == ItemTpye::Attachment) {
		ret = m_biology->itemUseable(item, m_biology->getGearVec()[m_index], item->getSum());
		m_biology->useItem(item, m_biology->getGearVec()[m_index],item->getSum());
	}

	return ret;
}




//预转移物品
bool WeaponGearPageView::premoveItem(Item* i, int id, int sum, ItemPageView* otherView) {
	//若被移动的物品是武器项
	if (i->getItemTpye() == ItemTpye::Weapon)return GearPageView::premoveItem(i, id, sum, otherView);
	//断言被移动的物品是武器配件项
	CCASSERT(i->getSum() == sum&&i->getItemTpye() == ItemTpye::Attachment, "premoveItem out of item's sum!");

	bool ret = false;

	auto premoveattachmentitem = static_cast<ItemWeapon*>(m_biology->getGearVec()[m_index])->unwearItemAttachment(i).getValueAndClearProtectedTansfer();
	ret = otherView->preaddItem(premoveattachmentitem);
	
	return ret;
}


void WeaponGearPageView::addAttachmentItemPage(ItemPage * itempage) {
	this->bindItemPageListener(itempage);
	m_itempage->addChild(itempage);
	m_attachmentpages.push_back(itempage);
}

void WeaponGearPageView::removeAttachmentItemPage(ItemPage * itempage) {

}
