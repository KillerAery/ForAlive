#pragma once
#ifndef _DROP_H_
#define _DROP_H_

#include "Container.h"


using cocos2d::Label;

class Drop : public Container {
protected:
	CC_SYNTHESIZE(Label*, m_namelabel, NameLabel);
//初始化部分
public:
	Drop();
	virtual bool init(ValueMap& obj_valuemap);
	static Drop* create(ValueMap & obj_valuemap);
	virtual void removeFromScene()override;
	//检查还有没有物品,没有则自我释放
	void checkNothingItemLeft();
	//显示物品名字
	void displayItemName();
	//隐藏物品名字
	void undisplayerItemName();
	/*操作类*/
	//添加物品
	virtual bool addItem(int id, int sum)override;
	virtual bool addItem(ProtectedTransfer<Item> item)override;
	//移除物品
	virtual bool removeItem(int id, int sum)override;
	virtual bool removeItem(Item* item, int sum)override;
	//转移物品到另一个容器
	virtual	bool moveItem(int id, int sum, Container* other)override;
	virtual bool moveItem(Item* item, int sum, Container* other)override;
	virtual	ProtectedTransfer<Item> moveItem(Item* item)override;
	//转移所有物品
	virtual	bool moveAllItems(Container* other)override;
	/*查询类*/
	//查询是否能添加物品
	virtual bool ifaddItem(int id, int sum)override;
	virtual bool ifaddItem(Item* item)override;
};


#endif