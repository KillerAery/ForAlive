#include "Drop.h"


using namespace cocos2d;


Drop::Drop():m_namelabel(nullptr){}

bool Drop::init(ValueMap& obj_valuemap) {
	//物理碰撞体积
	if (!Container::init(obj_valuemap))return false;
	//物品图片缩小
	m_sp->setScale(0.5f);

	return true;
}
Drop* Drop::create(ValueMap & obj_valuemap) {
	obj_valuemap.insert(ValueMap::value_type("physicstpye", Value(int(b2BodyType::b2_dynamicBody))));
	obj_valuemap.insert(ValueMap::value_type("width", Value(10.0f)));
	obj_valuemap.insert(ValueMap::value_type("height", Value(10.0f)));
	obj_valuemap.insert(ValueMap::value_type("entitytpye", Value(int(EntityTpye::drop))));
	obj_valuemap.insert(ValueMap::value_type("maskbit", Value(0x08)));//1000
	obj_valuemap.insert(ValueMap::value_type("categorybits", Value(0x08)));//1000

	auto d = new (std::nothrow)Drop();
	if (d&&d->init(obj_valuemap)) { d->autorelease(); }
	else { CC_SAFE_DELETE(d); }
	return d;
}

void Drop::removeFromScene() {
	NotificationCenter::getInstance()->postNotification("DROP_REMOVE", this);
	Entity::removeFromScene();
}


//检查还有没有物品
void Drop::checkNothingItemLeft(){
	if (m_itemlist.empty())this->setIfPredelete(true);
}

//显示物品名字
void Drop::displayItemName(){
	if (m_itemlist.empty()||m_namelabel)return;
	auto item = m_itemlist.front();
	m_namelabel = Label::createWithSystemFont(item->getName(),"Arial",18);
	//位置稍微高点
	m_namelabel->setPositionY(20);
	//黄色
	switch (item->getItemTpye())
	{
	case ItemTpye::Weapon:
		//蓝色
		m_namelabel->setColor(Color3B(0,0,255));
		break;
	case ItemTpye::Food:
		//绿色
		m_namelabel->setColor(Color3B(144, 255, 144));
		break;
	default:
		//白色
		m_namelabel->setColor(Color3B(255, 255, 255));
		break;
	}
	this->addChild(m_namelabel);
}
//隐藏名字
void Drop::undisplayerItemName(){
	if (!m_namelabel)return;
	m_namelabel->removeFromParent();
	m_namelabel = nullptr;
}

/*操作类*/
//添加物品
bool Drop::addItem(int id, int sum) {
	bool ret = Container::addItem(id,sum);
	//displayItemName();
	return ret;
}
bool Drop::addItem(ProtectedTransfer<Item> item) {
	bool ret = Container::addItem(item.getValueAndClearProtectedTansfer());
	//displayItemName();
	return ret;
}

//移除物品
bool Drop::removeItem(int id, int sum) {
	bool ret = Container::removeItem(id, sum);
	checkNothingItemLeft();
	return ret;
}
bool Drop::removeItem(Item* item, int sum) {
	bool ret = Container::removeItem(item, sum);
	checkNothingItemLeft();
	return ret;
}
//转移物品到另一个容器
bool Drop::moveItem(int id, int sum, Container* other) {
	bool ret = Container::moveItem(id, sum, other);
	checkNothingItemLeft();
	return ret;
}
bool Drop::moveItem(Item* item, int sum, Container* other) {
	bool ret = Container::moveItem(item, sum, other);
	checkNothingItemLeft();
	return ret;
}
ProtectedTransfer<Item> Drop::moveItem(Item* item) {
	auto temp = Container::moveItem(item).getValueAndClearProtectedTansfer();
	checkNothingItemLeft();
	return temp;
}
//转移所有物品
bool Drop::moveAllItems(Container* other) {
	bool ret = Container::moveAllItems(other);
	checkNothingItemLeft();
	return ret;
}


/*查询类*/
//查询是否能添加物品
bool Drop::ifaddItem(int id, int sum) {
	return false;
}
bool Drop::ifaddItem(Item* item) {
	return false;
}