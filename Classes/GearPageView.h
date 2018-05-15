#pragma once
#ifndef _GEAR_PAGE_VIEW_H_
#define _GEAR_PAGE_VIEW_H_

#include "ItemPageView.h"
#include "GearItemPage.h"

using cocos2d::Node;
using cocos2d::ui::ImageView;
using cocos2d::Sprite;

class Biology;

//װ��ҳ��
class GearPageView:public ItemPageView{
protected:
	CC_SYNTHESIZE(Biology*, m_biology,Biology);
	CC_SYNTHESIZE(int, m_index,Index);
	CC_SYNTHESIZE(ImageView*, m_sprite, Sprite);
	CC_SYNTHESIZE(GearItemPage*, m_itempage,ItemPage);
public:
	GearPageView();
	bool init(Biology* b,int geartpyr, Layer* backpacklayer);
	void initGearPageViewUI(Layer* backpacklayer);
	virtual void initItemPages()override;
	static GearPageView* create(Biology* b, int geartpyr, Layer* backpacklayer);
	virtual Container* getContainer()override;

	virtual void reload() override;
	void updateRefresh(float dt);
	//��ѯ�Ƿ����������Ʒ����
	virtual bool ifaddItem(int id, int sum)override;
	virtual bool ifaddItem(Item* i)override;
	//Ԥ�����Ʒ
	virtual bool preaddItem(int id, int sum)override;
	virtual bool preaddItem(Item* i)override;
	//Ԥ����Ʒ
	virtual bool prethrowItem(ItemPage* i, int sum)override;
	//Ԥת����Ʒ
	virtual bool premoveItem(Item* i, int id, int sum, ItemPageView* otherView)override;
	//Ԥʹ����Ʒ
	virtual bool preuseItem(ItemPage* i)override;

	void addItemPage(GearItemPage * itempage);
	void removeItemPage(GearItemPage * itempage);

};

#endif