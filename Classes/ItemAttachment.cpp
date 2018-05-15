#include "ItemAttachment.h"
#include "Biology.h"

ItemAttachment::ItemAttachment(){ }

//ʹ���߶�һ����Ʒʹ��
bool ItemAttachment::useable(Biology* user, Item* preusedItem, int usesum){
	if (!preusedItem||preusedItem->getItemTpye() != ItemTpye::Weapon||usesum>1)return false;
	return true;
}
void ItemAttachment::use(Biology* user, Item* preusedItem, int usesum) {
	if (!useable(user, preusedItem, usesum))return;
	//Ŀ����Ʒ��������Ʒ
	ItemWeapon* preusedweaponitem = static_cast<ItemWeapon*>(preusedItem);

	auto preaddweaponitem = static_cast<ItemAttachment*>(ItemFactory::createItem(m_id, usesum));

	Item* overflowItem = nullptr;
	//��ӱ���Ʒ��Ŀ����Ʒ�����õ����������Ʒ
	if(preaddweaponitem)
	overflowItem = preusedweaponitem->addItemAttachment(preaddweaponitem).getValueAndClearProtectedTansfer();

	//������Ʒ�����Լ�������Χ�ڣ����ղ�������
	if (user->findItem(this))user->reduceItemSum(this, usesum);
	else m_sum = m_sum - usesum;

	//����������Ʒ����Ŀ�����֮
	if(overflowItem)user->addItem(overflowItem);
}