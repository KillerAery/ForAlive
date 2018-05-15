#include "ItemAmmo.h"
#include "Biology.h"

ItemAmmo::ItemAmmo(){}
ItemAmmo::~ItemAmmo(){}


//使用者对一个物品使用
bool ItemAmmo::useable(Biology* user, Item* preusedItem, int usesum) {
	//待加入检查是否子弹配属武器函数
	return true;
}
void ItemAmmo::use(Biology* user, Item* preusedItem, int usesum) {
	//消耗N颗子弹
	if (m_sum >= usesum)user->reduceItemSum(this,usesum);
}