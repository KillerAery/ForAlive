#include "ItemAmmo.h"
#include "Biology.h"

ItemAmmo::ItemAmmo(){}
ItemAmmo::~ItemAmmo(){}


//ʹ���߶�һ����Ʒʹ��
bool ItemAmmo::useable(Biology* user, Item* preusedItem, int usesum) {
	//���������Ƿ��ӵ�������������
	return true;
}
void ItemAmmo::use(Biology* user, Item* preusedItem, int usesum) {
	//����N���ӵ�
	if (m_sum >= usesum)user->reduceItemSum(this,usesum);
}