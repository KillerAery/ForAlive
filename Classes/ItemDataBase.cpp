#include "ItemDataBase.h"

ItemDataBase::ItemDataBase(){}
ItemDataBase::~ItemDataBase(){ closeSQL(); }
bool ItemDataBase::init() {
	return loadItemDB();
}

bool ItemDataBase::loadItemDB(){
	//��SQL���ݿ�
	if (!openSQL(cocos2d::FileUtils::getInstance()->fullPathForFilename("SQL/ForAliveItemDataBase.db")))return false;

	loadItemWeaponDB();
	loadItemFoodDB();
	loadItemAmmoDB();
	loadItemAttachmentDB();

	return true;
}


void ItemDataBase::loadItemFoodDB() {
	//��SQL��һ��Table
	if(!initTraversingTableData("ItemFood"))return;
	//��ʼ����
	while (traverNextRowData())
	{
		ItemData data;
		data.insert(std::make_pair(e_name, Value(getTraversingStringData(e_name))));
		data.insert(std::make_pair(e_weight, Value(getTraversingDoubleData(e_weight))));
		data.insert(std::make_pair(e_maxsuperposition, Value(getTraversingIntData(e_maxsuperposition))));
		data.insert(std::make_pair(e_description, Value(getTraversingStringData(e_description))));

		data.insert(std::make_pair(e_health, Value(getTraversingDoubleData(e_health))));
		data.insert(std::make_pair(e_food, Value(getTraversingDoubleData(e_food))));
		data.insert(std::make_pair(e_drink, Value(getTraversingDoubleData(e_drink))));
		data.insert(std::make_pair(e_mood, Value(getTraversingDoubleData(e_mood))));

		auto id = getTraversingIntData(e_id);
		//������Ҫ��ʱ����map������ת������ֵ�ƶ������ݿ�
		m_itemdatabase.insert(std::make_pair(id,std::move(data)));
	}

}
void ItemDataBase::loadItemWeaponDB() {
	//��SQL��һ��Table
	if(!initTraversingTableData("ItemWeapon"))return;
	//��ʼ����
	while (traverNextRowData())
	{
		ItemData data;
		data.insert(std::make_pair(e_name, Value(getTraversingStringData(e_name))));
		data.insert(std::make_pair(e_weight, Value(getTraversingDoubleData(e_weight))));
		data.insert(std::make_pair(e_maxsuperposition, Value(getTraversingIntData(e_maxsuperposition))));
		data.insert(std::make_pair(e_description, Value(getTraversingStringData(e_description))));

		data.insert(std::make_pair(e_damage, Value(getTraversingDoubleData(e_damage))));
		data.insert(std::make_pair(e_sound, Value(getTraversingDoubleData(e_sound))));
		data.insert(std::make_pair(e_weapontpye, Value(getTraversingIntData(e_weapontpye))));
		data.insert(std::make_pair(e_range, Value(getTraversingDoubleData(e_range))));
		data.insert(std::make_pair(e_accuracy, Value(getTraversingDoubleData(e_accuracy))));
		data.insert(std::make_pair(e_hands, Value(getTraversingIntData(e_hands))));
		data.insert(std::make_pair(e_attacktime, Value(getTraversingDoubleData(e_attacktime))));
		data.insert(std::make_pair(e_availableammoid, Value(getTraversingVectorData(e_availableammoid))));

		auto id = getTraversingIntData(e_id);
		//������Ҫ��ʱ����map������ת������ֵ�ƶ������ݿ�
		m_itemdatabase.insert(std::make_pair(id, std::move(data)));
	}

}
void ItemDataBase::loadItemAmmoDB() {
	//��SQL��һ��Table
	if(!initTraversingTableData("ItemAmmo"))return;
	//��ʼ����
	while (traverNextRowData())
	{
		ItemData data;
		data.insert(std::make_pair(e_name, Value(getTraversingStringData(e_name))));
		data.insert(std::make_pair(e_weight, Value(getTraversingDoubleData(e_weight))));
		data.insert(std::make_pair(e_maxsuperposition, Value(getTraversingIntData(e_maxsuperposition))));
		data.insert(std::make_pair(e_description, Value(getTraversingStringData(e_description))));

		auto id = getTraversingIntData(e_id);
		//������Ҫ��ʱ����map������ת������ֵ�ƶ������ݿ�
		m_itemdatabase.insert(std::make_pair(id, std::move(data)));
	}

}
void ItemDataBase::loadItemAttachmentDB() {
	//��SQL��һ��Table
	if(!initTraversingTableData("ItemAttachment"))return;
	//��ʼ����
	while (traverNextRowData())
	{
		ItemData data;
		data.insert(std::make_pair(e_name, Value(getTraversingStringData(e_name))));
		data.insert(std::make_pair(e_weight, Value(getTraversingDoubleData(e_weight))));
		data.insert(std::make_pair(e_maxsuperposition, Value(getTraversingIntData(e_maxsuperposition))));
		data.insert(std::make_pair(e_description, Value(getTraversingStringData(e_description))));

		data.insert(std::make_pair(e_a_damage, Value(getTraversingDoubleData(e_a_damage))));
		data.insert(std::make_pair(e_a_sound, Value(getTraversingDoubleData(e_a_sound))));
		data.insert(std::make_pair(e_a_range, Value(getTraversingDoubleData(e_a_range))));
		data.insert(std::make_pair(e_a_accuracy, Value(getTraversingDoubleData(e_a_accuracy))));
		data.insert(std::make_pair(e_a_attacktime, Value(getTraversingDoubleData(e_a_attacktime))));
		data.insert(std::make_pair(e_itemattachmenttpye, Value(getTraversingIntData(e_itemattachmenttpye))));
		auto id = getTraversingIntData(e_id);
		//������Ҫ��ʱ����map������ת������ֵ�ƶ������ݿ�
		m_itemdatabase.insert(std::make_pair(id, std::move(data)));
	}

}

const Value& ItemDataBase::getData(int id, Itemfield field) {
	return m_itemdatabase[id][field];
}