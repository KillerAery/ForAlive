#ifndef _ITEM_DATABASE_H_
#define _ITEM_DATABASE_H_

#include <map>
#include "cocos2d.h"
#include "DBHelper.h"
#include "Singleton.h"

using std::string;
using cocos2d::Ref;
using cocos2d::ValueMap;
using cocos2d::ValueVector;
using cocos2d::Value;

using ItemData = std::map<int, Value>;
using ItemDataMap = std::map<int,ItemData>;

/*-------Ϊ�������ͼ��为��---------------
�����ֵ�value���� = string
xx���͵�value���� = int
������value���� = double
*/

//�ֶ�enmu
enum Itemfield{
	e_id = 0, e_name = 1, e_weight = 2, e_maxsuperposition = 3,e_description = 4,
	e_damage = 5, e_weapontpye = 6, e_sound = 7, e_range = 8, e_accuracy = 9, e_hands = 10, e_availableammoid = 11, e_attacktime = 12,
	e_health = 5, e_food = 6, e_drink = 7, e_mood = 8,
	e_a_damage = 5, e_a_sound = 6, e_a_range = 7, e_a_accuracy = 8, e_a_attacktime = 9, e_itemattachmenttpye = 10
};

//������ ItemDateBase
class ItemDataBase :public DBHelper,public Singleton<ItemDataBase>{
private:
	ItemDataBase();
protected:
	CC_SYNTHESIZE_PASS_BY_REF(ItemDataMap,m_itemdatabase,ItemDataBase);
public:
	virtual ~ItemDataBase();
	bool init();
	friend Singleton<ItemDataBase>;
public:
	bool loadItemDB();//����������Ʒ����
	void loadItemFoodDB();//����ʳ������
	void loadItemWeaponDB();//������������
	void loadItemAmmoDB();//�����ӵ�����
	void loadItemAttachmentDB();//���ظ�������

	const Value& getData(int id, Itemfield field);
};


#endif // 
