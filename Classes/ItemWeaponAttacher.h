#ifndef _ITEM_WEAPON_ATTACHER_H_
#define _ITEM_WEAPON_ATTACHER_H_

#include "ItemAttacher.h"
#include "ItemAttachment.h"
#include "ProtectedTransfer.h"

using AMIVector = std::vector<ItemAttachment*>;

class ItemWeaponAttacher : public ItemAttacher{
protected:
	CC_SYNTHESIZE_PASS_BY_REF(AMIVector,m_itemattachments,ItemAttachments);	//���
	CC_SYNTHESIZE(bool, m_ifstuck,IfStuck);//����״̬
	CC_SYNTHESIZE(int,m_durability,Durability);//�;�
public:
	ItemWeaponAttacher();
	virtual ~ItemWeaponAttacher();

	ProtectedTransfer<ItemAttachment> addItemAttachment(ProtectedTransfer<ItemAttachment> i);
	ProtectedTransfer<ItemAttachment> unwearItemAttachment(int index);
	ProtectedTransfer<ItemAttachment> unwearItemAttachment(Item* i);

	int getAdditionDamage();//���ӵ������˺�
	float getAdditionAttackTime();//���ӵ������������ʱ��
	int getAdditionSound();//���ӵ���������
	int getAdditionRange();//���ӵ���������
	int getAdditionAccuracy();//���ӵ�������׼��

};

#endif // _WEAPON_ITEM_ATTACHER_H_
