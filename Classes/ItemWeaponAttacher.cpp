#include "ItemWeaponAttacher.h"

//配件最多只有5个
ItemWeaponAttacher::ItemWeaponAttacher():m_durability(100),m_ifstuck(false),m_itemattachments(5){}
//析构时释放所有存在的配件物品
ItemWeaponAttacher::~ItemWeaponAttacher(){
	for (auto itemattachment : m_itemattachments){
		if (itemattachment)delete itemattachment;
	}
}

ProtectedTransfer<ItemAttachment> ItemWeaponAttacher::addItemAttachment(ProtectedTransfer<ItemAttachment> i){
	auto item = i.getValueAndClearProtectedTansfer();
	if (!item)return nullptr;
	auto temp = m_itemattachments[item->getItemAttachmentTpye()];
	m_itemattachments[item->getItemAttachmentTpye()] = item;
	return ProtectedTransfer<ItemAttachment>(temp);
}

ProtectedTransfer<ItemAttachment> ItemWeaponAttacher::unwearItemAttachment(int index){
	auto temp = m_itemattachments[index];
	m_itemattachments[index] = nullptr;
	return ProtectedTransfer<ItemAttachment>(temp);
}


ProtectedTransfer<ItemAttachment> ItemWeaponAttacher::unwearItemAttachment(Item* item) {
	for (auto & m_i : m_itemattachments)
		if (m_i == item) {
			m_i = nullptr;
			return static_cast<ItemAttachment*>(item);
		}
	return nullptr;
}

//增加的武器伤害
int ItemWeaponAttacher::getAdditionDamage(){
	int total = 0;
	for (auto i : m_itemattachments)
		if (i)total += i->getAdditionDamage();
	return total;
}
//增加的武器攻击间隔时间
float ItemWeaponAttacher::getAdditionAttackTime() {
	float total = 0;
	for (auto i : m_itemattachments)
		if (i)total += i->getAdditionAttackTime();
	return total;
}
//增加的武器噪音
int ItemWeaponAttacher::getAdditionSound() {
	int total = 0;
	for (auto i : m_itemattachments)
		if (i)total += i->getAdditionSound();
	return total;
}
//增加的武器距离
int ItemWeaponAttacher::getAdditionRange() {
	int total = 0;
	for (auto i : m_itemattachments)
		if (i)total += i->getAdditionRange();
	return total;
}
//增加的武器精准度
int ItemWeaponAttacher::getAdditionAccuracy() {
	int total = 0;
	for (auto i : m_itemattachments)
		if (i)total += i->getAdditionAccuracy();
	return total;
}