#pragma once
#ifndef _ITEM_H_
#define _ITEM_H_

#include  "cocos2d.h"
#include "ItemDataBase.h"

using std::string;
using cocos2d::Ref;
using cocos2d::Vec2;
using cocos2d::Value;

class Biology;
class Entity;

enum class ItemTpye{
	NoTpye,Weapon,Food,Ammo,Attachment,Armor
};

class Item{
protected:
	//物品id
	CC_SYNTHESIZE(int, m_id, ID);
	CC_SYNTHESIZE_READONLY(int,m_sum,Sum);	//只读-不再提供setSum方法
	CC_SYNTHESIZE(double, m_weight, Weight);//重量
	double UNITweight;						//物品单位重量
public:
	Item();
	virtual ~Item();
	bool init(int id,int sum);
	//物品访问
	static string getItemTpyeString(int id);
	static ItemTpye getItemTpye(int id);
	string getItemTpyeString(){ return getItemTpyeString(m_id); }														//物品类型名字
	ItemTpye getItemTpye() { return getItemTpye(m_id); }																//物品类型
	int getMaxSuperPosition() { return ItemDataBase::getInstance()->getData(m_id, e_maxsuperposition).asInt();}//最大堆叠数量
	string getName() {return ItemDataBase::getInstance()->getData(m_id, e_name).asString();}					//物品名字
	string getDescription() {return ItemDataBase::getInstance()->getData(m_id, e_description).asString();}			//物品描述

	void addSum(int sum) { m_sum += sum; m_weight = m_weight + UNITweight* sum; }
	void reduceSum(int sum) {m_sum -= sum; m_weight = m_weight - UNITweight* sum;}

	//使用者对使用者使用
	virtual bool useable(Biology* user, int usesum);
	virtual void use(Biology* user, int usesum);
	//使用者对生物使用
	virtual bool useable(Biology* user, Biology* biology, int usesum);
	virtual void use(Biology* user, Biology* biology, int usesum);
	//使用者对物体使用
	virtual bool useable(Biology* user, Entity* entity, int usesum);
	virtual void use(Biology* user, Entity* entity, int usesum);
	//使用者对一个方向使用
	virtual bool useable(Biology* user, const Vec2& direction, int usesum);
	virtual void use(Biology* user, const Vec2& direction, int usesum);
	//使用者对一个物品使用
	virtual bool useable(Biology* user, Item* preusedItem, int usesum);
	virtual void use(Biology* user, Item* preusedItem, int usesum);
};



#endif // !_ITEM_H_
