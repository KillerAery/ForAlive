#include "ItemWeapon.h"
#include "Biology.h"
#include "Bullet.h"

ItemWeapon::ItemWeapon() :m_attacher() {}
ItemWeapon::~ItemWeapon(){}

//使用者使用本物品后效果
void ItemWeapon::userAfterUse(Biology* user, const Vec2& direction) {
	//如果方向朝某一边，则图像翻转至该边
	if (direction.x < 0)user->getSprite()->setFlipX(true);
	else if (direction.x > 0)user->getSprite()->setFlipX(false);
	//设置冷却时间
	user->setIfCoolTime(false);
	user->scheduleOnce([user](float dt) {user->unschedule("cooltime_attack"); user->setIfCoolTime(true); }, getAttackTime(), "cooltime_attack");
}

//使用散弹枪
void ItemWeapon::useShotGun(Biology* user, const Vec2& direction) {
	//射击音乐
	GameTool::getInstance()->playEffect("Music/shotgun.mp3");

	for (auto i = 0; i <= 5; ++i){
		auto accuracy = getaccuracy();
		auto ShotDir = Vec2(direction.x - accuracy/2 + cocos2d::rand_0_1()*accuracy, direction.y - accuracy/2 + cocos2d::rand_0_1() *accuracy).getNormalized();
		auto bullet = Bullet::create(user,Vec2(user->getPositionX(),user->getPositionY()+user->getContentSize().height/2), ShotDir,getDamage(), -user->getID());//负数groundindex
		user->getParent()->addChild(bullet);
		user->getParent()->addChild(bullet->getmotionStreak());
	}
}

//使用自动武器
void ItemWeapon::usetAutoGun(Biology* user, const Vec2& direction) {
	//射击音乐
	GameTool::getInstance()->playEffect("Music/gunshot.mp3");
	auto bullet = Bullet::create(user, Vec2(user->getPositionX(), user->getPositionY() + user->getContentSize().height / 2), direction, getDamage(), -user->getID());//负数groundindex
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



//使用者对使用者使用
bool ItemWeapon::useable(Biology* user, int usesum) { return false; }
void ItemWeapon::use(Biology* user, int usesum){}
//使用者对生物使用
bool ItemWeapon::useable(Biology* user, Biology* biology, int usesum){ return false; }
void ItemWeapon::use(Biology* user, Biology* biology, int usesum){}
//使用者对物体使用
bool ItemWeapon::useable(Biology* user, Entity* entity, int usesum){ return false; }
void ItemWeapon::use(Biology* user, Entity* entity, int usesum){}
//使用者对一个方向使用
bool ItemWeapon::useable(Biology* user, const Vec2& direction, int usesum){
	//判断武器是否有相配的子弹
	auto matchableAmmoIds = getAvailableAmmoID();
	Item* foundedItem = nullptr;
	for (auto matchAmmoId : matchableAmmoIds) {
		//找到相应的子弹物品
		if ((foundedItem = user->findItem(matchAmmoId.asInt())))break;
	}
	//若找到物品并且物品能使用，则成功
	if (foundedItem&&foundedItem->useable(user, this, usesum))return true;
	return false;
}
void ItemWeapon::use(Biology* user, const Vec2& direction, int usesum){
	//判断武器是否有相配的子弹
	auto matchableAmmoIds = getAvailableAmmoID();
	Item* foundedItem = nullptr;
	for (auto matchAmmoId : matchableAmmoIds) {
		//找到相应的子弹物品
		if ((foundedItem = user->findItem(matchAmmoId.asInt())))break;
	}
	//若找不到物品或者物品不能使用，则失败
	if (!foundedItem||!foundedItem->useable(user, this, usesum))return;

	//消耗物品
	foundedItem->use(user, this, usesum);

	//根据ID判断武器类型
	switch (m_id)
	{
	//98K Glock27
	case 1:case 3:
		usetAutoGun(user, direction);
		break;
	//散弹枪
	case 2:
		useShotGun(user, direction);
		break;
	}
	//使用者使用本物品后效果
	userAfterUse(user,direction);
}
//使用者对一个物品使用
bool ItemWeapon::useable(Biology* user, Item* preusedItem, int usesum){ return false; }
void ItemWeapon::use(Biology* user, Item* preusedItem, int usesum){}