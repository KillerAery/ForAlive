#ifndef _ATTACHMENT_ITEM_H_
#define _ATTACHMENT_ITEM_H_

#include "Item.h"

enum ItemAttachmentTpye{
	gunmouth,gunhandle,gunslens,gunclip,guntail
};

class ItemAttachment :public Item {
public:
	ItemAttachment();
	ItemAttachmentTpye getItemAttachmentTpye() {return ItemAttachmentTpye(ItemDataBase::getInstance()->getData(m_id, e_itemattachmenttpye).asInt());}	//配件类型
	double getAdditionDamage() { return ItemDataBase::getInstance()->getData(m_id, e_a_damage).asDouble(); }												//增加武器伤害
	double getAdditionAttackTime() { return ItemDataBase::getInstance()->getData(m_id, e_a_attacktime).asDouble(); }										//增加攻击间隔时间
	double getAdditionSound() { return ItemDataBase::getInstance()->getData(m_id, e_a_sound).asDouble(); }												//增加武器噪音
	double getAdditionRange() {return ItemDataBase::getInstance()->getData(m_id, e_a_range).asDouble();}													//增加武器距离
	double getAdditionAccuracy() {return ItemDataBase::getInstance()->getData(m_id, e_a_accuracy).asDouble();}											//增加武器精准度
public:
	//使用者对一个物品使用
	virtual bool useable(Biology* user, Item* preusedItem, int usesum)override;
	virtual void use(Biology* user, Item* preusedItem, int usesum)override;
};


#endif // 
