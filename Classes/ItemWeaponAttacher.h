#ifndef _ITEM_WEAPON_ATTACHER_H_
#define _ITEM_WEAPON_ATTACHER_H_

#include "ItemAttacher.h"
#include "ItemAttachment.h"
#include "ProtectedTransfer.h"

using AMIVector = std::vector<ItemAttachment*>;

class ItemWeaponAttacher : public ItemAttacher{
protected:
	CC_SYNTHESIZE_PASS_BY_REF(AMIVector,m_itemattachments,ItemAttachments);	//配件
	CC_SYNTHESIZE(bool, m_ifstuck,IfStuck);//卡壳状态
	CC_SYNTHESIZE(int,m_durability,Durability);//耐久
public:
	ItemWeaponAttacher();
	virtual ~ItemWeaponAttacher();

	ProtectedTransfer<ItemAttachment> addItemAttachment(ProtectedTransfer<ItemAttachment> i);
	ProtectedTransfer<ItemAttachment> unwearItemAttachment(int index);
	ProtectedTransfer<ItemAttachment> unwearItemAttachment(Item* i);

	int getAdditionDamage();//增加的武器伤害
	float getAdditionAttackTime();//增加的武器攻击间隔时间
	int getAdditionSound();//增加的武器噪音
	int getAdditionRange();//增加的武器距离
	int getAdditionAccuracy();//增加的武器精准度

};

#endif // _WEAPON_ITEM_ATTACHER_H_
