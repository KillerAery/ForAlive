#pragma once
#ifndef _WEAPON_GEAR_PAGE_VIEW_H_
#define _WEAPON_GEAR_PAGE_VIEW_H_

#include "GearPageView.h"
#include "WeaponGearItemPage.h"

//����װ��ҳ��
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

	//��ѯ�Ƿ����������Ʒ����
	virtual bool ifaddItem(int id, int sum)override;
	virtual bool ifaddItem(Item* i)override;
	//Ԥ�����Ʒ
	virtual bool preaddItem(int id, int sum)override;
	virtual bool preaddItem(Item* i)override;
	////Ԥ����Ʒ
	//virtual bool prethrowItem(ItemPage* i, int sum)override;
	//Ԥת����Ʒ
	virtual bool premoveItem(Item* i, int id, int sum, ItemPageView* otherView)override;
	////Ԥʹ����Ʒ
	//virtual bool preuseItem(ItemPage* i)override;

	void addAttachmentItemPage(ItemPage * itempage);
	void removeAttachmentItemPage(ItemPage * itempage);
};

#endif // !_WEAPON_GEAR_PAGE_VIEW_H_
