#pragma once
#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include "Entity.h"
#include "ItemFactory.h"
#include "ProtectedTransfer.h"
class Item;
using cocos2d::Layer;

class Container :public Entity{
	//��ʼ������
public:
	Container();
	virtual ~Container();
	virtual bool init(ValueMap& obj_valuemap);
	virtual bool Container::initPhysics(ValueMap& obj_valuemap)override;
	void initItemsByValueMap(ValueMap& valuemap);
	static Container* create(ValueMap & obj_valuemap);
	//�ӳ������Ƴ�
	virtual void removeFromScene()override;

/*-----------------------------����ģ��-----------------------*/
public:
	void addItemSum(Item* i, int sum);
	void reduceItemSum(Item* i, int sum);
	void createItem(int id, int sum);
	void createItem(ProtectedTransfer<Item> item);
	//��������Ϊ0����Ʒ
	void clear0numItems();
protected:
	CC_SYNTHESIZE_PASS_BY_REF(std::list<Item*>, m_itemlist,ItemList);
	CC_SYNTHESIZE(double, m_maxweight ,Maxweight);
	CC_SYNTHESIZE(double, m_weight, Weight);
	CC_SYNTHESIZE(bool, m_ifpublic, IfPublic);
public:
	/*������*/
	//�����Ʒ
	virtual bool addItem(int id,int sum);
	virtual bool addItem(ProtectedTransfer<Item> item);
	//�Ƴ���Ʒ
	virtual bool removeItem(int id, int sum);
	virtual bool removeItem(Item* item, int sum);
	//ת����Ʒ����һ������
	virtual bool moveItem(int id, int sum,Container* other);
	virtual bool moveItem(Item* item, int sum, Container* other);
	virtual ProtectedTransfer<Item> moveItem(Item* item);
	//ת��������Ʒ
	virtual bool moveAllItems(Container* other);

	/*��ѯ��*/
	//��ѯ�Ƿ��������Ʒ
	virtual bool ifaddItem(int id, int sum);
	virtual bool ifaddItem(Item* item);
	//���Һ���
	Item* findItem(int id);
	Item* findItem(Item* item);
	//��������Ʒ
	void throwContainerDrop(Item* i, int sum);
	void throwAllContainerDrops();
	//���ɵ�����
	Container* createDrop(Item* i);
	//���������
	virtual void checkTrigger(int id, int num){}
protected:
	CC_SYNTHESIZE(Sprite*, m_tabSprite, TabSprite);
public:
	//��ʾ/����Tab��
	void showTabKey();
	void hideTabKey();
};

#endif // !_CONTAINER_H_
