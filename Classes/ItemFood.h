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
	double getAdditionHealth() { return ItemDataBase::getInstance()->getData(m_id, e_health).asDouble(); }	//食物增加生命值
	double getAdditionFood() { return ItemDataBase::getInstance()->getData(m_id, e_food).asDouble(); }		//食物增加饱腹值
	double getAdditionDrink() { return ItemDataBase::getInstance()->getData(m_id, e_drink).asDouble(); }		//食物增加口渴值
	double getAdditionMood() { return ItemDataBase::getInstance()->getData(m_id, e_mood).asDouble(); }		//食物增加心情值
public:
	//使用者对使用者使用
	virtual bool useable(Biology* user, int usesum)override;
	virtual void use(Biology* user, int usesum)override;
	//使用者对生物使用
	virtual bool useable(Biology* user, Biology* biology, int usesum)override;
	virtual void use(Biology* user, Biology* biology, int usesum)override;
};



#endif
