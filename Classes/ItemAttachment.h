#ifndef _ATTACHMENT_ITEM_H_
#define _ATTACHMENT_ITEM_H_

#include "Item.h"

enum ItemAttachmentTpye{
	gunmouth,gunhandle,gunslens,gunclip,guntail
};

class ItemAttachment :public Item {
public:
	ItemAttachment();
	ItemAttachmentTpye getItemAttachmentTpye() {return ItemAttachmentTpye(ItemDataBase::getInstance()->getData(m_id, e_itemattachmenttpye).asInt());}	//�������
	double getAdditionDamage() { return ItemDataBase::getInstance()->getData(m_id, e_a_damage).asDouble(); }												//���������˺�
	double getAdditionAttackTime() { return ItemDataBase::getInstance()->getData(m_id, e_a_attacktime).asDouble(); }										//���ӹ������ʱ��
	double getAdditionSound() { return ItemDataBase::getInstance()->getData(m_id, e_a_sound).asDouble(); }												//������������
	double getAdditionRange() {return ItemDataBase::getInstance()->getData(m_id, e_a_range).asDouble();}													//������������
	double getAdditionAccuracy() {return ItemDataBase::getInstance()->getData(m_id, e_a_accuracy).asDouble();}											//����������׼��
public:
	//ʹ���߶�һ����Ʒʹ��
	virtual bool useable(Biology* user, Item* preusedItem, int usesum)override;
	virtual void use(Biology* user, Item* preusedItem, int usesum)override;
};


#endif // 
