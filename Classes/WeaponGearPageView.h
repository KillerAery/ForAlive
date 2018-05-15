#pragma once
#ifndef _WEAPON_GEAR_PAGE_VIEW_H_
#define _WEAPON_GEAR_PAGE_VIEW_H_

#include "GearPageView.h"
#include "WeaponGearItemPage.h"

//武器装备页面
class WeaponGearPageView :public GearPageView{
protected:
	CC_SYNTHESIZE_PASS_BY_REF(std::vector<ItemPage*>,m_attachmentpages,AttachmentPages);
public:
	WeaponGearPageView();
	bool init(Biology* b, int geartpyr, Layer* backpacklayer);
	void initWeaponGearPageViewUI(Layer* backpacklayer);
	virtual void initItemPages()override;
	static WeaponGearPageView* create(Biology* b, int geartpyr, Layer* backpacklayer);
	virtual Container* getContainer()override;

	//查询是否满足添加物品条件
	virtual bool ifaddItem(int id, int sum)override;
	virtual bool ifaddItem(Item* i)override;
	//预添加物品
	virtual bool preaddItem(int id, int sum)override;
	virtual bool preaddItem(Item* i)override;
	////预扔物品
	//virtual bool prethrowItem(ItemPage* i, int sum)override;
	//预转移物品
	virtual bool premoveItem(Item* i, int id, int sum, ItemPageView* otherView)override;
	////预使用物品
	//virtual bool preuseItem(ItemPage* i)override;

	void addAttachmentItemPage(ItemPage * itempage);
	void removeAttachmentItemPage(ItemPage * itempage);
};

#endif // !_WEAPON_GEAR_PAGE_VIEW_H_
