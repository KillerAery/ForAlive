#ifndef _ITEM_FACTORY_H_
#define _ITEM_FACTORY_H_

#include "ItemAmmo.h"
#include "ItemFood.h"
#include "ItemWeapon.h"
#include "ItemAttachment.h"

//Item工厂，负责创建Item
class ItemFactory{
public:
	static Item* createItem(int id, int sum = 1);//创建物品
};

#endif
