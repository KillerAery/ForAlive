#include "Item.h"
#include "Biology.h"


using cocos2d::NotificationCenter;

Item::Item():m_id(0),m_sum(0),m_weight(0.0f),UNITweight(0.0f){}
Item::~Item(){}

bool Item::init(int id, int sum){
	m_id = id;
	m_sum = sum;
	UNITweight = ItemDataBase::getInstance()->getData(m_id, e_weight).asDouble();
	m_weight = UNITweight* sum;
	return true;
}
string Item::getItemTpyeString(int id) {
	if (id < 100)return "ItemWeapon";
	else if (id < 200)return "ItemFood";
	else if (id < 300)return "ItemAmmo";
	else if (id < 400)return "ItemAttachment";
	
	CC_ASSERT("ITEM ID WRONG!!!NO SUCH A ITEM ID!!");
	return nullptr;
}

ItemTpye Item::getItemTpye(int id) {
	if (id < 100)return ItemTpye::Weapon;
	else if (id < 200)return ItemTpye::Food;
	else if (id < 300)return ItemTpye::Ammo;
	else if (id < 400)return ItemTpye::Attachment;
	
	CC_ASSERT("ITEM ID WRONG!!!NO SUCH A ITEM ID!!");
	return ItemTpye::NoTpye;
}

/*------使用方法全部默认无任何效果------*/
//使用者对使用者使用
bool Item::useable(Biology* user, int usesum) { return false; }
void Item::use(Biology* user, int usesum){}
//使用者对生物使用
bool Item::useable(Biology* user, Biology* biology, int usesum) { return false; }
void Item::use(Biology* user, Biology* biology, int usesum){}
//使用者对物体使用
bool Item::useable(Biology* user, Entity* entity, int usesum) { return false; }
void Item::use(Biology* user, Entity* entity, int usesum){}
//使用者对一个方向使用
bool Item::useable(Biology* user, const Vec2& direction, int usesum) { return false; }
void Item::use(Biology* user, const Vec2& direction, int usesum){}
//使用者对一个物品使用
bool Item::useable(Biology* user, Item* preusedItem, int usesum) { return false; }
void Item::use(Biology* user, Item* preusedItem, int usesum){}