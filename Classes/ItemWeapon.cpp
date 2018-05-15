#include "ItemWeapon.h"
#include "Biology.h"
#include "Bullet.h"

ItemWeapon::ItemWeapon() :m_attacher() {}
ItemWeapon::~ItemWeapon(){}

//ʹ����ʹ�ñ���Ʒ��Ч��
void ItemWeapon::userAfterUse(Biology* user, const Vec2& direction) {
	//�������ĳһ�ߣ���ͼ��ת���ñ�
	if (direction.x < 0)user->getSprite()->setFlipX(true);
	else if (direction.x > 0)user->getSprite()->setFlipX(false);
	//������ȴʱ��
	user->setIfCoolTime(false);
	user->scheduleOnce([user](float dt) {user->unschedule("cooltime_attack"); user->setIfCoolTime(true); }, getAttackTime(), "cooltime_attack");
}

//ʹ��ɢ��ǹ
void ItemWeapon::useShotGun(Biology* user, const Vec2& direction) {
	//�������
	GameTool::getInstance()->playEffect("Music/shotgun.mp3");

	for (auto i = 0; i <= 5; ++i){
		auto accuracy = getaccuracy();
		auto ShotDir = Vec2(direction.x - accuracy/2 + cocos2d::rand_0_1()*accuracy, direction.y - accuracy/2 + cocos2d::rand_0_1() *accuracy).getNormalized();
		auto bullet = Bullet::create(user,Vec2(user->getPositionX(),user->getPositionY()+user->getContentSize().height/2), ShotDir,getDamage(), -user->getID());//����groundindex
		user->getParent()->addChild(bullet);
		user->getParent()->addChild(bullet->getmotionStreak());
	}
}

//ʹ���Զ�����
void ItemWeapon::usetAutoGun(Biology* user, const Vec2& direction) {
	//�������
	GameTool::getInstance()->playEffect("Music/gunshot.mp3");
	auto bullet = Bullet::create(user, Vec2(user->getPositionX(), user->getPositionY() + user->getContentSize().height / 2), direction, getDamage(), -user->getID());//����groundindex
	user->getParent()->addChild(bullet);
	user->getParent()->addChild(bullet->getmotionStreak());
}

ProtectedTransfer<ItemAttachment> ItemWeapon::addItemAttachment(ProtectedTransfer<ItemAttachment> i) {
	return m_attacher.addItemAttachment(i.getValueAndClearProtectedTansfer());
}

ProtectedTransfer<ItemAttachment> ItemWeapon::unwearItemAttachment(int index) {
	return m_attacher.unwearItemAttachment(index);
}
ProtectedTransfer<ItemAttachment> ItemWeapon::unwearItemAttachment(Item* i){
	return m_attacher.unwearItemAttachment(i);
}



//ʹ���߶�ʹ����ʹ��
bool ItemWeapon::useable(Biology* user, int usesum) { return false; }
void ItemWeapon::use(Biology* user, int usesum){}
//ʹ���߶�����ʹ��
bool ItemWeapon::useable(Biology* user, Biology* biology, int usesum){ return false; }
void ItemWeapon::use(Biology* user, Biology* biology, int usesum){}
//ʹ���߶�����ʹ��
bool ItemWeapon::useable(Biology* user, Entity* entity, int usesum){ return false; }
void ItemWeapon::use(Biology* user, Entity* entity, int usesum){}
//ʹ���߶�һ������ʹ��
bool ItemWeapon::useable(Biology* user, const Vec2& direction, int usesum){
	//�ж������Ƿ���������ӵ�
	auto matchableAmmoIds = getAvailableAmmoID();
	Item* foundedItem = nullptr;
	for (auto matchAmmoId : matchableAmmoIds) {
		//�ҵ���Ӧ���ӵ���Ʒ
		if ((foundedItem = user->findItem(matchAmmoId.asInt())))break;
	}
	//���ҵ���Ʒ������Ʒ��ʹ�ã���ɹ�
	if (foundedItem&&foundedItem->useable(user, this, usesum))return true;
	return false;
}
void ItemWeapon::use(Biology* user, const Vec2& direction, int usesum){
	//�ж������Ƿ���������ӵ�
	auto matchableAmmoIds = getAvailableAmmoID();
	Item* foundedItem = nullptr;
	for (auto matchAmmoId : matchableAmmoIds) {
		//�ҵ���Ӧ���ӵ���Ʒ
		if ((foundedItem = user->findItem(matchAmmoId.asInt())))break;
	}
	//���Ҳ�����Ʒ������Ʒ����ʹ�ã���ʧ��
	if (!foundedItem||!foundedItem->useable(user, this, usesum))return;

	//������Ʒ
	foundedItem->use(user, this, usesum);

	//����ID�ж���������
	switch (m_id)
	{
	//98K Glock27
	case 1:case 3:
		usetAutoGun(user, direction);
		break;
	//ɢ��ǹ
	case 2:
		useShotGun(user, direction);
		break;
	}
	//ʹ����ʹ�ñ���Ʒ��Ч��
	userAfterUse(user,direction);
}
//ʹ���߶�һ����Ʒʹ��
bool ItemWeapon::useable(Biology* user, Item* preusedItem, int usesum){ return false; }
void ItemWeapon::use(Biology* user, Item* preusedItem, int usesum){}