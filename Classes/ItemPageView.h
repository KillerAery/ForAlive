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
	//查询是否满足添加物品条件
	virtual bool ifaddItem(int id, int sum)=0;
	virtual bool ifaddItem(Item* i)=0;
	//预添加物品
	virtual bool preaddItem(int id, int sum)=0;
	virtual bool preaddItem(Item* i)=0;
	//预扔物品
	virtual bool prethrowItem(ItemPage* i,int sum)=0;
	//预转移物品
	virtual bool premoveItem(Item* i, int id, int sum, ItemPageView* otherView)=0;
	//预使用物品
	virtual bool preuseItem(ItemPage* i)=0;

	bool requestMoveItem(ItemPage* i, ItemPageView* otherView);
	bool requestUseItem(ItemPage* i,const Vec2& touchpoint);
	bool requestThrowItem(ItemPage* i);
};

#endif