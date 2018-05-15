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
	//��ʱ���� ���Ƽ�
	if (!backpacklayer)return;
	m_sprite = static_cast<ImageView*>(backpacklayer->getChildByTag(1)->getChildByTag(70 + m_index));
	this->setAnchorPoint(Vec2(0.5,0.5));
	this->setPosition(this->convertToNodeSpace(m_sprite->getWorldPosition()));

	//���������
	//setBackGroundColorType(Layout::BackGroundColorType::SOLID);
	//setBackGroundColor(cocos2d::Color3B(255, 255, 255));

	this->setContentSize(Size(m_sprite->getContentSize().width*m_sprite->getParent()->getScaleX(), m_sprite->getContentSize().height*m_sprite->getParent()->getScaleY()));
}

void WeaponGearPageView::initItemPages(){
	if (m_index<GearTpye::LeftHandGear || m_index>GearTpye::RightHandGear || !m_biology->getGearVec()[m_index])return;
	//������Ʒ
	auto weaponitem = static_cast<ItemWeapon*>(m_biology->getGearVec()[m_index]);
	//����װ����
	auto weaponitempage = WeaponGearItemPage::create(weaponitem);
	m_itempage = weaponitempage;
	this->addItemPage(m_itempage);
	//����װ�� Я���������
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

//��ѯ�Ƿ����������Ʒ����
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
	////���������,�� ������ȥ
	//if (item->getItemTpye() == ItemTpye::Weapon)
	//	ret = m_biology->wearGear(item, (GearTpye)m_index);

	////������������ʹ����ȥ
	//else if (item->getItemTpye() == ItemTpye::Attachment) {
	//	ret = m_biology->itemUseable(item, m_biology->getGearVec()[m_index], item->getSum());
	//	m_biology->useItem(item, m_biology->getGearVec()[m_index], item->getSum());
	//}
	////���ʧ���ˣ�������ڴ�
	//if (!ret)delete item;

	return ret;
}

bool WeaponGearPageView::preaddItem(Item* item) {
	bool ret = false;

	//���������,�� ������ȥ
	if (item->getItemTpye() == ItemTpye::Weapon)
		ret = m_biology->wearGear(item,(GearTpye)m_index);
	
	//������������ʹ����ȥ
	else if (item->getItemTpye() == ItemTpye::Attachment) {
		ret = m_biology->itemUseable(item, m_biology->getGearVec()[m_index], item->getSum());
		m_biology->useItem(item, m_biology->getGearVec()[m_index],item->getSum());
	}

	return ret;
}




//Ԥת����Ʒ
bool WeaponGearPageView::premoveItem(Item* i, int id, int sum, ItemPageView* otherView) {
	//�����ƶ�����Ʒ��������
	if (i->getItemTpye() == ItemTpye::Weapon)return GearPageView::premoveItem(i, id, sum, otherView);
	//���Ա��ƶ�����Ʒ�����������
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
