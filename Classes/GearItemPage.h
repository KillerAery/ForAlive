#pragma once
#ifndef _GEAR_ITEM_PAGE_H_
#define _GEAR_ITEM_PAGE_H_

#include "ItemPage.h"

class GearItemPage :public ItemPage {
protected:
	CC_SYNTHESIZE(Sprite*, m_itemsprite, ItemSprite);
public:
	GearItemPage();
	static GearItemPage* create(Item* item);
	bool init(Item* item);
	virtual void refresh()override;
};


#endif