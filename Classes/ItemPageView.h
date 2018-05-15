#pragma once
#ifndef _PAGE_VIEW_H_
#define _PAGE_VIEW_H_

#include "ItemPage.h"

using cocos2d::Layer;

class Container;
class ItemPageView;
using ItemPageViewList = std::list<ItemPageView*>;

class ItemPageView : public cocos2d::ui::Layout{
public:
	static ItemPageViewList s_itempageview_list;
public:
	ItemPageView();
	virtual ~ItemPageView();
	virtual void initItemPages() = 0;
public:
	void bindItemPageListener(ItemPage* itemPage);
	virtual void reload() = 0;
	virtual Container* getContainer() = 0;
public:
	//��ѯ�Ƿ����������Ʒ����
	virtual bool ifaddItem(int id, int sum)=0;
	virtual bool ifaddItem(Item* i)=0;
	//Ԥ�����Ʒ
	virtual bool preaddItem(int id, int sum)=0;
	virtual bool preaddItem(Item* i)=0;
	//Ԥ����Ʒ
	virtual bool prethrowItem(ItemPage* i,int sum)=0;
	//Ԥת����Ʒ
	virtual bool premoveItem(Item* i, int id, int sum, ItemPageView* otherView)=0;
	//Ԥʹ����Ʒ
	virtual bool preuseItem(ItemPage* i)=0;

	bool requestMoveItem(ItemPage* i, ItemPageView* otherView);
	bool requestUseItem(ItemPage* i,const Vec2& touchpoint);
	bool requestThrowItem(ItemPage* i);
};

#endif