#pragma once
#ifndef _ITEMPAGEVIEW_H_
#define _ITEMPAGEVIEW_H_

#include "ItemPageView.h"
#include "ContainerItemPage.h"

class Container;

using ContainerItemPageList = std::list<ContainerItemPage*>;
using cocos2d::ui::LoadingBar;

//容器页面
class ContainerPageView:public ItemPageView{
protected:
	CC_SYNTHESIZE(Layout*, m_layout,Layout);
	CC_SYNTHESIZE(LoadingBar*, m_weightbar,Weightbar);
	CC_SYNTHESIZE(Container*, m_container, Container);
	CC_SYNTHESIZE_PASS_BY_REF(ContainerItemPageList, m_itempagelist, ContainerItemPageList);
public:
	ContainerPageView();
	bool init(Container* c);
	virtual void initItemPages()override;
	void initContainerPageViewUI();
	static ContainerPageView* create(Container* c);
	virtual Container* getContainer()override;
public:
	void updateRefresh(float dt);
	virtual void reload() override;
	void addItemPage(ContainerItemPage * itempage);
	void removeItemPage(ContainerItemPage * itempage);
	void removeItemPage(typename ContainerItemPageList::iterator itr);
	//ContainerItemPage上浮
	void goUpItemPages(typename ContainerItemPageList::iterator itr);

	//查询是否满足添加物品条件
	virtual bool ifaddItem(int id, int sum)override;
	virtual bool ifaddItem(Item* i)override;
	//预添加物品
	virtual bool preaddItem(int id, int sum)override;
	virtual bool preaddItem(Item* i)override;
	//预扔物品
	virtual bool prethrowItem(ItemPage* i, int sum)override;
	//预转移物品
	virtual bool premoveItem(Item* i, int id, int sum, ItemPageView* otherView)override;
	//预使用物品
	virtual bool preuseItem(ItemPage* i)override;

};

#endif