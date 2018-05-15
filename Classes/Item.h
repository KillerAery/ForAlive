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
	//��Ʒid
	CC_SYNTHESIZE(int, m_id, ID);
	CC_SYNTHESIZE_READONLY(int,m_sum,Sum);	//ֻ��-�����ṩsetSum����
	CC_SYNTHESIZE(double, m_weight, Weight);//����
	double UNITweight;						//��Ʒ��λ����
public:
	Item();
	virtual ~Item();
	bool init(int id,int sum);
	//��Ʒ����
	static string getItemTpyeString(int id);
	static ItemTpye getItemTpye(int id);
	string getItemTpyeString(){ return getItemTpyeString(m_id); }														//��Ʒ��������
	ItemTpye getItemTpye() { return getItemTpye(m_id); }																//��Ʒ����
	int getMaxSuperPosition() { return ItemDataBase::getInstance()->getData(m_id, e_maxsuperposition).asInt();}//���ѵ�����
	string getName() {return ItemDataBase::getInstance()->getData(m_id, e_name).asString();}					//��Ʒ����
	string getDescription() {return ItemDataBase::getInstance()->getData(m_id, e_description).asString();}			//��Ʒ����

	void addSum(int sum) { m_sum += sum; m_weight = m_weight + UNITweight* sum; }
	void reduceSum(int sum) {m_sum -= sum; m_weight = m_weight - UNITweight* sum;}

	//ʹ���߶�ʹ����ʹ��
	virtual bool useable(Biology* user, int usesum);
	virtual void use(Biology* user, int usesum);
	//ʹ���߶�����ʹ��
	virtual bool useable(Biology* user, Biology* biology, int usesum);
	virtual void use(Biology* user, Biology* biology, int usesum);
	//ʹ���߶�����ʹ��
	virtual bool useable(Biology* user, Entity* entity, int usesum);
	virtual void use(Biology* user, Entity* entity, int usesum);
	//ʹ���߶�һ������ʹ��
	virtual bool useable(Biology* user, const Vec2& direction, int usesum);
	virtual void use(Biology* user, const Vec2& direction, int usesum);
	//ʹ���߶�һ����Ʒʹ��
	virtual bool useable(Biology* user, Item* preusedItem, int usesum);
	virtual void use(Biology* user, Item* preusedItem, int usesum);
};



#endif // !_ITEM_H_
