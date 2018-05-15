#pragma once
#ifndef _WEAPON_GEAR_ITEM_PAGE_H_
#define _WEAPON_GEAR_ITEM_PAGE_H_

#include "GearItemPage.h"

class WeaponGearItemPage : public GearItemPage {
/*------WeaponGearItemPage¿‡-------*/
protected:
	CC_SYNTHESIZE(Layout*,m_layout,Layout);
public:
	WeaponGearItemPage();
	static WeaponGearItemPage* create(Item* item);
	bool init(Item* item);
	virtual void refresh()override;
};

#endif // !_WEAPON_GEAR_ITEM_PAGE_H_
