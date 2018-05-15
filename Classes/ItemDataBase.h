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

/*-------为避免类型记忆负担---------------
带文字的value类型 = string
xx类型的value类型 = int
其他的value类型 = double
*/

//字段enmu
enum Itemfield{
	e_id = 0, e_name = 1, e_weight = 2, e_maxsuperposition = 3,e_description = 4,
	e_damage = 5, e_weapontpye = 6, e_sound = 7, e_range = 8, e_accuracy = 9, e_hands = 10, e_availableammoid = 11, e_attacktime = 12,
	e_health = 5, e_food = 6, e_drink = 7, e_mood = 8,
	e_a_damage = 5, e_a_sound = 6, e_a_range = 7, e_a_accuracy = 8, e_a_attacktime = 9, e_itemattachmenttpye = 10
};

//单例类 ItemDateBase
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
	bool loadItemDB();//加载所有物品数据
	void loadItemFoodDB();//加载食物数据
	void loadItemWeaponDB();//加载武器数据
	void loadItemAmmoDB();//加载子弹数据
	void loadItemAttachmentDB();//加载附件数据

	const Value& getData(int id, Itemfield field);
};


#endif // 
