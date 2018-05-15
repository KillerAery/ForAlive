#pragma once
#ifndef _WEAPON_ATTACHMENT_ITEM_PAGE_H_
#define _WEAPON_ATTACHMENT_ITEM_PAGE_H_

#include "ItemPage.h"

class WeaponAttachmentItemPage:public ItemPage{
protected:
	CC_SYNTHESIZE(Sprite*, m_itemsprite, ItemSprite);
public:
	WeaponAttachmentItemPage();
	static WeaponAttachmentItemPage* create(Item* item);
	bool init(Item* item);
	virtual void refresh()override;
};


#endif // !_WEAPON_ATTACHMENT_ITEM_PAGE_H_
