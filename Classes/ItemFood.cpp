#include "ItemFood.h"
#include "Biology.h"

ItemFood::ItemFood() :m_attacher() {}
ItemFood::~ItemFood(){}


//ʹ���߶�ʹ����ʹ��
bool ItemFood::useable(Biology* user, int usesum){
	//ʹ������������Χ ���� ����ֵ��������
	if (m_sum < usesum || user->getHealth()>=user->getMaxHealth())return false;

	return true;
}
void ItemFood::use(Biology* user, int usesum){
	if (!useable(user, usesum))return;
	user->setHealth(usesum* getAdditionHealth() + user->getHealth());
	user->reduceItemSum(this, usesum);
}
//ʹ���߶�����ʹ��
bool ItemFood::useable(Biology* user, Biology* biology, int usesum){
	return false;
}
void ItemFood::use(Biology* user, Biology* biology, int usesum) {

}