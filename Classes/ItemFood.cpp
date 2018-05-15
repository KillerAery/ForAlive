#include "ItemFood.h"
#include "Biology.h"

ItemFood::ItemFood() :m_attacher() {}
ItemFood::~ItemFood(){}


//使用者对使用者使用
bool ItemFood::useable(Biology* user, int usesum){
	//使用数量超出范围 或者 生命值到达上限
	if (m_sum < usesum || user->getHealth()>=user->getMaxHealth())return false;

	return true;
}
void ItemFood::use(Biology* user, int usesum){
	if (!useable(user, usesum))return;
	user->setHealth(usesum* getAdditionHealth() + user->getHealth());
	user->reduceItemSum(this, usesum);
}
//使用者对生物使用
bool ItemFood::useable(Biology* user, Biology* biology, int usesum){
	return false;
}
void ItemFood::use(Biology* user, Biology* biology, int usesum) {

}