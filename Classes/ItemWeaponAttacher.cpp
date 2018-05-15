#include "ItemWeaponAttacher.h"

//������ֻ��5��
ItemWeaponAttacher::ItemWeaponAttacher():m_durability(100),m_ifstuck(false),m_itemattachments(5){}
//����ʱ�ͷ����д��ڵ������Ʒ
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

//���ӵ������˺�
int ItemWeaponAttacher::getAdditionDamage(){
	int total = 0;
	for (auto i : m_itemattachments)
		if (i)total += i->getAdditionDamage();
	return total;
}
//���ӵ������������ʱ��
float ItemWeaponAttacher::getAdditionAttackTime() {
	float total = 0;
	for (auto i : m_itemattachments)
		if (i)total += i->getAdditionAttackTime();
	return total;
}
//���ӵ���������
int ItemWeaponAttacher::getAdditionSound() {
	int total = 0;
	for (auto i : m_itemattachments)
		if (i)total += i->getAdditionSound();
	return total;
}
//���ӵ���������
int ItemWeaponAttacher::getAdditionRange() {
	int total = 0;
	for (auto i : m_itemattachments)
		if (i)total += i->getAdditionRange();
	return total;
}
//���ӵ�������׼��
int ItemWeaponAttacher::getAdditionAccuracy() {
	int total = 0;
	for (auto i : m_itemattachments)
		if (i)total += i->getAdditionAccuracy();
	return total;
}