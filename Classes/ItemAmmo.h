#ifndef _AMMO_ITEM_H_
#define _AMMO_ITEM_H_

#include "Item.h"

class ItemAmmo :public Item{
public:
	ItemAmmo();
	virtual ~ItemAmmo();
public:
	//ʹ���߶�һ����Ʒʹ��
	virtual bool useable(Biology* user, Item* preusedItem, int usesum)override;
	virtual void use(Biology* user, Item* preusedItem, int usesum)override;
};

#endif 
