#pragma once
#ifndef _DROP_H_
#define _DROP_H_

#include "Container.h"


using cocos2d::Label;

class Drop : public Container {
protected:
	CC_SYNTHESIZE(Label*, m_namelabel, NameLabel);
//��ʼ������
public:
	Drop();
	virtual bool init(ValueMap& obj_valuemap);
	static Drop* create(ValueMap & obj_valuemap);
	virtual void removeFromScene()override;
	//��黹��û����Ʒ,û���������ͷ�
	void checkNothingItemLeft();
	//��ʾ��Ʒ����
	void displayItemName();
	//������Ʒ����
	void undisplayerItemName();
	/*������*/
	//�����Ʒ
	virtual bool addItem(int id, int sum)override;
	virtual bool addItem(ProtectedTransfer<Item> item)override;
	//�Ƴ���Ʒ
	virtual bool removeItem(int id, int sum)override;
	virtual bool removeItem(Item* item, int sum)override;
	//ת����Ʒ����һ������
	virtual	bool moveItem(int id, int sum, Container* other)override;
	virtual bool moveItem(Item* item, int sum, Container* other)override;
	virtual	ProtectedTransfer<Item> moveItem(Item* item)override;
	//ת��������Ʒ
	virtual	bool moveAllItems(Container* other)override;
	/*��ѯ��*/
	//��ѯ�Ƿ��������Ʒ
	virtual bool ifaddItem(int id, int sum)override;
	virtual bool ifaddItem(Item* item)override;
};


#endif