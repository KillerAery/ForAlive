#ifndef _FOOD_ITEM_H_
#define _FOOD_ITEM_H_

#include "Item.h"
#include "ItemFoodAttacher.h"

class ItemFood : public Item{
protected:
	CC_SYNTHESIZE_PASS_BY_REF(ItemFoodAttacher, m_attacher, Attacher);
public:
	ItemFood();
	virtual ~ItemFood();
	double getAdditionHealth() { return ItemDataBase::getInstance()->getData(m_id, e_health).asDouble(); }	//ʳ����������ֵ
	double getAdditionFood() { return ItemDataBase::getInstance()->getData(m_id, e_food).asDouble(); }		//ʳ�����ӱ���ֵ
	double getAdditionDrink() { return ItemDataBase::getInstance()->getData(m_id, e_drink).asDouble(); }		//ʳ�����ӿڿ�ֵ
	double getAdditionMood() { return ItemDataBase::getInstance()->getData(m_id, e_mood).asDouble(); }		//ʳ����������ֵ
public:
	//ʹ���߶�ʹ����ʹ��
	virtual bool useable(Biology* user, int usesum)override;
	virtual void use(Biology* user, int usesum)override;
	//ʹ���߶�����ʹ��
	virtual bool useable(Biology* user, Biology* biology, int usesum)override;
	virtual void use(Biology* user, Biology* biology, int usesum)override;
};



#endif
