#include "ItemAttachment.h"
#include "Biology.h"

ItemAttachment::ItemAttachment(){ }

//使用者对一个物品使用
bool ItemAttachment::useable(Biology* user, Item* preusedItem, int usesum){
	if (!preusedItem||preusedItem->getItemTpye() != ItemTpye::Weapon||usesum>1)return false;
	return true;
}
void ItemAttachment::use(Biology* user, Item* preusedItem, int usesum) {
	if (!useable(user, preusedItem, usesum))return;
	//目标物品：武器物品
	ItemWeapon* preusedweaponitem = static_cast<ItemWeapon*>(preusedItem);

	auto preaddweaponitem = static_cast<ItemAttachment*>(ItemFactory::createItem(m_id, usesum));

	Item* overflowItem = nullptr;
	//添加本物品到目标物品，并得到溢出附件物品
	if(preaddweaponitem)
	overflowItem = preusedweaponitem->addItemAttachment(preaddweaponitem).getValueAndClearProtectedTansfer();

	//若本物品是在自己容器范围内，则按照操作减少
	if (user->findItem(this))user->reduceItemSum(this, usesum);
	else m_sum = m_sum - usesum;

	//如果有溢出物品，则目标添加之
	if(overflowItem)user->addItem(overflowItem);
}