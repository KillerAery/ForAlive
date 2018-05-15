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
	//武器类型	
	int getWeaponTpye() { return ItemDataBase::getInstance()->getData(m_id, e_weapontpye).asInt(); }
	//武器伤害	
	double getDamage() {
		double attacheddamage = 0;
		attacheddamage = m_attacher.getAdditionDamage();
		return ItemDataBase::getInstance()->getData(m_id, e_damage).asDouble() + attacheddamage;
	}
	//武器可允许用的子弹ID	
	const ValueVector& getAvailableAmmoID(){
		return ItemDataBase::getInstance()->getData(m_id,e_availableammoid).asValueVector();
	}
	//武器攻击间隔时间	
	double getAttackTime() {
		double attachedattacktime = 0;
		attachedattacktime = m_attacher.getAdditionAttackTime();
		return ItemDataBase::getInstance()->getData(m_id,e_attacktime).asDouble() + attachedattacktime;
	}
	//武器噪音	
	double getSound() {
		double attachedsound = 0;
		attachedsound = m_attacher.getAdditionSound();
		return ItemDataBase::getInstance()->getData(m_id,e_sound).asDouble() + attachedsound;
	}
	//武器距离	
	double getRange() {
		double attachedrange = 0;
		attachedrange = m_attacher.getAdditionRange();
		return ItemDataBase::getInstance()->getData(m_id,e_range).asDouble() + attachedrange;
	}
	//武器精准度	
	double getaccuracy() {
		double attachedaccuracy = 0;
		attachedaccuracy = m_attacher.getAdditionAccuracy();
		return ItemDataBase::getInstance()->getData(m_id,e_accuracy).asDouble() + attachedaccuracy;
	}
private:
	//使用者使用本物品后效果
	void userAfterUse(Biology* user, const Vec2& direction);
	void useShotGun(Biology* user, const Vec2& direction);
	void usetAutoGun(Biology* user, const Vec2& direction);
public:
	//使用者对使用者使用
	virtual bool useable(Biology* user, int usesum)override;
	virtual void use(Biology* user, int usesum)override;
	//使用者对生物使用
	virtual bool useable(Biology* user, Biology* biology, int usesum)override;
	virtual void use(Biology* user, Biology* biology, int usesum)override;
	//使用者对物体使用
	virtual bool useable(Biology* user, Entity* entity, int usesum)override;
	virtual void use(Biology* user, Entity* entity, int usesum)override;
	//使用者对一个方向使用
	virtual bool useable(Biology* user, const Vec2& direction, int usesum)override;
	virtual void use(Biology* user, const Vec2& direction, int usesum)override;
	//使用者对一个物品使用
	virtual bool useable(Biology* user, Item* preusedItem, int usesum)override;
	virtual void use(Biology* user, Item* preusedItem, int usesum)override;
public:
	ProtectedTransfer<ItemAttachment> addItemAttachment(ProtectedTransfer<ItemAttachment> i);
	ProtectedTransfer<ItemAttachment> unwearItemAttachment(int index);
	ProtectedTransfer<ItemAttachment> unwearItemAttachment(Item* i);
};

#endif
