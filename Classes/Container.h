#pragma once
#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include "Entity.h"
#include "ItemFactory.h"
#include "ProtectedTransfer.h"
class Item;
using cocos2d::Layer;

class Container :public Entity{
	//初始化部分
public:
	Container();
	virtual ~Container();
	virtual bool init(ValueMap& obj_valuemap);
	virtual bool Container::initPhysics(ValueMap& obj_valuemap)override;
	void initItemsByValueMap(ValueMap& valuemap);
	static Container* create(ValueMap & obj_valuemap);
	//从场景中移除
	virtual void removeFromScene()override;

/*-----------------------------容器模块-----------------------*/
public:
	void addItemSum(Item* i, int sum);
	void reduceItemSum(Item* i, int sum);
	void createItem(int id, int sum);
	void createItem(ProtectedTransfer<Item> item);
	//清理数量为0的物品
	void clear0numItems();
protected:
	CC_SYNTHESIZE_PASS_BY_REF(std::list<Item*>, m_itemlist,ItemList);
	CC_SYNTHESIZE(double, m_maxweight ,Maxweight);
	CC_SYNTHESIZE(double, m_weight, Weight);
	CC_SYNTHESIZE(bool, m_ifpublic, IfPublic);
public:
	/*操作类*/
	//添加物品
	virtual bool addItem(int id,int sum);
	virtual bool addItem(ProtectedTransfer<Item> item);
	//移除物品
	virtual bool removeItem(int id, int sum);
	virtual bool removeItem(Item* item, int sum);
	//转移物品到另一个容器
	virtual bool moveItem(int id, int sum,Container* other);
	virtual bool moveItem(Item* item, int sum, Container* other);
	virtual ProtectedTransfer<Item> moveItem(Item* item);
	//转移所有物品
	virtual bool moveAllItems(Container* other);

	/*查询类*/
	//查询是否能添加物品
	virtual bool ifaddItem(int id, int sum);
	virtual bool ifaddItem(Item* item);
	//查找函数
	Item* findItem(int id);
	Item* findItem(Item* item);
	//扔容器物品
	void throwContainerDrop(Item* i, int sum);
	void throwAllContainerDrops();
	//生成掉落物
	Container* createDrop(Item* i);
	//触发器检测
	virtual void checkTrigger(int id, int num){}
protected:
	CC_SYNTHESIZE(Sprite*, m_tabSprite, TabSprite);
public:
	//显示/隐藏Tab键
	void showTabKey();
	void hideTabKey();
};

#endif // !_CONTAINER_H_
