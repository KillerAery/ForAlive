#ifndef _WEAPON_ITEM_H_
#define _WEAPON_ITEM_H_

#include "Item.h"
#include "ItemWeaponAttacher.h"

enum class WeaponTpye
{

};


class ItemWeapon : public Item {
protected:
	CC_SYNTHESIZE_PASS_BY_REF(ItemWeaponAttacher, m_attacher, Attacher);
public:
	ItemWeapon();
	virtual ~ItemWeapon();
	//��������	
	int getWeaponTpye() { return ItemDataBase::getInstance()->getData(m_id, e_weapontpye).asInt(); }
	//�����˺�	
	double getDamage() {
		double attacheddamage = 0;
		attacheddamage = m_attacher.getAdditionDamage();
		return ItemDataBase::getInstance()->getData(m_id, e_damage).asDouble() + attacheddamage;
	}
	//�����������õ��ӵ�ID	
	const ValueVector& getAvailableAmmoID(){
		return ItemDataBase::getInstance()->getData(m_id,e_availableammoid).asValueVector();
	}
	//�����������ʱ��	
	double getAttackTime() {
		double attachedattacktime = 0;
		attachedattacktime = m_attacher.getAdditionAttackTime();
		return ItemDataBase::getInstance()->getData(m_id,e_attacktime).asDouble() + attachedattacktime;
	}
	//��������	
	double getSound() {
		double attachedsound = 0;
		attachedsound = m_attacher.getAdditionSound();
		return ItemDataBase::getInstance()->getData(m_id,e_sound).asDouble() + attachedsound;
	}
	//��������	
	double getRange() {
		double attachedrange = 0;
		attachedrange = m_attacher.getAdditionRange();
		return ItemDataBase::getInstance()->getData(m_id,e_range).asDouble() + attachedrange;
	}
	//������׼��	
	double getaccuracy() {
		double attachedaccuracy = 0;
		attachedaccuracy = m_attacher.getAdditionAccuracy();
		return ItemDataBase::getInstance()->getData(m_id,e_accuracy).asDouble() + attachedaccuracy;
	}
private:
	//ʹ����ʹ�ñ���Ʒ��Ч��
	void userAfterUse(Biology* user, const Vec2& direction);
	void useShotGun(Biology* user, const Vec2& direction);
	void usetAutoGun(Biology* user, const Vec2& direction);
public:
	//ʹ���߶�ʹ����ʹ��
	virtual bool useable(Biology* user, int usesum)override;
	virtual void use(Biology* user, int usesum)override;
	//ʹ���߶�����ʹ��
	virtual bool useable(Biology* user, Biology* biology, int usesum)override;
	virtual void use(Biology* user, Biology* biology, int usesum)override;
	//ʹ���߶�����ʹ��
	virtual bool useable(Biology* user, Entity* entity, int usesum)override;
	virtual void use(Biology* user, Entity* entity, int usesum)override;
	//ʹ���߶�һ������ʹ��
	virtual bool useable(Biology* user, const Vec2& direction, int usesum)override;
	virtual void use(Biology* user, const Vec2& direction, int usesum)override;
	//ʹ���߶�һ����Ʒʹ��
	virtual bool useable(Biology* user, Item* preusedItem, int usesum)override;
	virtual void use(Biology* user, Item* preusedItem, int usesum)override;
public:
	ProtectedTransfer<ItemAttachment> addItemAttachment(ProtectedTransfer<ItemAttachment> i);
	ProtectedTransfer<ItemAttachment> unwearItemAttachment(int index);
	ProtectedTransfer<ItemAttachment> unwearItemAttachment(Item* i);
};

#endif
