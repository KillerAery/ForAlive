#include "ItemFactory.h"



Item* ItemFactory::createItem(int id, int sum) {
		Item* i;
		//根据id来构造相应的item类型
		if (id < 100)i = new(std::nothrow)ItemWeapon();
		else if (id < 200)i = new(std::nothrow)ItemFood();
		else if (id < 300)i = new(std::nothrow)ItemAmmo();
		else if (id < 400)i = new(std::nothrow)ItemAttachment();
		else { CC_ASSERT("ITEM ID WRONG!!!NO SUCH A ITEM ID!!"); return nullptr; }

		if(i&&i->init(id,sum))return i;

		if (i)delete i;
		return nullptr;
}