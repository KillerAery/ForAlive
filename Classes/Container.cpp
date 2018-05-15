#pragma once
#include "Container.h"
#include "Drop.h"


using namespace cocos2d;
using cocos2d::Director;
using cocos2d::NotificationCenter;

Container::Container():m_ifpublic(true),m_maxweight(60.0),m_weight(0.0),m_tabSprite(nullptr){}
Container::~Container() {
	//释放容器内item资源
	for (auto i : m_itemlist){delete i;}
}

bool Container::init(ValueMap& obj_valuemap){
	obj_valuemap.insert(ValueMap::value_type("groupindex", Value(-obj_valuemap["id"].asInt())));//负数groundindex
	if (!Entity::init(obj_valuemap))return false;
	//设置容器名字
	this->setName(obj_valuemap["name"].asString());
	this->initItemsByValueMap(obj_valuemap);
	return true;
}

void Container::initItemsByValueMap(ValueMap& obj_valuemap) {
	if (obj_valuemap.find("items")==obj_valuemap.end())return;
	//解析items的字符串为item的数据信息
	string str = obj_valuemap["items"].asString();

	for (size_t i = 0, num = 0, id = 0; i < str.size(); ++i) {
		if (str[i] >= '0'&&str[i] <= '9') {
			num *= 10;
			num += (str[i] - '0');
		}
		else if (str[i] == '*')
		{
			id = num;
			num = 0;
		}
		else if (str[i] == '|')
		{
			addItem(id, num);
			id = 0;
			num = 0;
		}
	}
}

bool Container::initPhysics(ValueMap& obj_valuemap) {
	if (!Entity::initPhysics(obj_valuemap))return false;
	//阻尼
	m_b2body->SetLinearDamping(5.0f);
	return true;
}

Container* Container::create(ValueMap & obj_valuemap) {
	obj_valuemap.insert(ValueMap::value_type("entitytpye", Value(int(EntityTpye::container))));
	obj_valuemap.insert(ValueMap::value_type("physicstpye", Value(int(b2BodyType::b2_staticBody))));
	obj_valuemap.insert(ValueMap::value_type("maskbit", Value(8)));//1000
	obj_valuemap.insert(ValueMap::value_type("categorybits", Value(8)));//1000
	//奇怪的bug，tilemap里箱子的位置和实际位置有200,100的偏移
	//暂时这么修复
	obj_valuemap["x"] = obj_valuemap["x"].asInt() + obj_valuemap["width"].asInt()/2 +150;
	obj_valuemap["y"] = obj_valuemap["y"].asInt() + obj_valuemap["height"].asInt()/2+80;

	auto c = new (std::nothrow)Container();
	if (c&&c->init(obj_valuemap)) {c->autorelease(); }
	else { CC_SAFE_DELETE(c); }
	return c;
}

//从场景中移除
void Container::removeFromScene(){
	NotificationCenter::getInstance()->postNotification("CONTAINER_REMOVE",this);
	Entity::removeFromScene();
}

void Container::addItemSum(Item* i, int sum) {
	i->addSum(sum);
	m_weight = m_weight + (i->UNITweight*sum);

	checkTrigger(i->getID(), i->getSum());
}
void Container::reduceItemSum(Item* i, int sum) {
	m_weight = m_weight - (i->UNITweight*sum);
	i->reduceSum(sum);

	checkTrigger(i->getID(),i->getSum());

	//清除数量为0的物品
	if (i->getSum() <= 0) {
		delete i;
		m_itemlist.remove(i);
	}

}
void Container::createItem(int id, int sum) {
	auto i = ItemFactory::createItem(id, sum);
	if (!i)return;

	m_weight += (i->getWeight());
	m_itemlist.push_back(i);

	checkTrigger(i->getID(), i->getSum());
}
void Container::createItem(ProtectedTransfer<Item> item) {
	auto i = item.getValueAndClearProtectedTansfer();
	if (!i)return;

	m_itemlist.push_back(i);
	m_weight += (i->getWeight());

	checkTrigger(i->getID(),i->getSum());
}

//清除所有数量为0的物品项
void Container::clear0numItems(){
	for (auto it = m_itemlist.begin(); it != m_itemlist.end();){
		if ((*it)->getSum() <= 0) {
			//若 数量为0 ，释放物品
			delete (*it);
			it = m_itemlist.erase(it);
		}
		else ++it;
	}
}


//添加物品
bool Container::addItem(int id, int sum){
	if (sum <= 0)return false;

	//最大堆叠物品数
	auto MAXS = ItemDataBase::getInstance()->getData(id, e_maxsuperposition).asInt();

	//添加数量过多时  
	while(sum > MAXS){ addItem(id,MAXS); sum = sum - MAXS;}
	//若已存在该item类型，则添加数量 
	for (auto item : m_itemlist){
		if (item->getID() == id){
			//同类item数量达到上限，继续遍历
			if (item->getSum() >= MAXS)continue;
			//同类item数量+sum后若达到上限，先将同类item数量填满，再将多余item数量 以新物品方式添加
			else if (item->getSum() + sum >MAXS) {
				//填满同类item数量
				int addition = MAXS - item->getSum();
				sum -= addition;
				addItemSum(item,addition);
				//添加新物品 多余的item数量
				return addItem(id, sum);
			}
			//同类item+sum后仍未达上限，可以直接添加
			else {
				addItemSum(item,sum);
				return true;
			}
			}
	}
	//若不存在，则新建item
	createItem(id,sum);
	return true;
}

//添加物品
bool Container::addItem(ProtectedTransfer<Item> item) {
	createItem(item.getValueAndClearProtectedTansfer());
	return true;
}

//移除物品
bool Container::removeItem(int id, int sum){
	int totalsum= 0;
	//统计该类物品的所有数量
	for (auto i : m_itemlist)
		if (id == i->getID())totalsum += i->getSum();

	//移除超出 存在数量
	if (sum > totalsum)return false;

	int temp;
	//若在数量之内
	for (auto i : m_itemlist)
		if (id == i->getID() && i->getSum()>0){
			temp = i->getSum() - sum;
			if (temp > 0){
				reduceItemSum(i, sum);
				break;
			}
			else{ 
				reduceItemSum(i,i->getSum());
			}
		}

	return true;
}

bool Container::removeItem(Item* i, int sum) {
	if (i->getSum() < sum||!findItem(i))return false;
	reduceItemSum(i,sum);
	return true;
}


//移动物品到另一个容器
bool Container::moveItem(int id, int sum, Container* other) {
	//若另一个容器 权限不公开，则不允许交换
	if (!other->getIfPublic())return false;
	//查询自己容器是否满足转移条件
	if (!removeItem(id, sum))return false;
	//查询另一个容器是否满足转移条件
	other->addItem(id, sum);
	return true;
}

bool Container::moveItem(Item* item, int sum, Container* other) {
	//若另一个容器 权限不公开，则不允许交换
	if (!other->getIfPublic() || !findItem(item))return false;
	int id = item->getID();
	//查询自己容器是否满足转移条件
	if (item->getMaxSuperPosition() == 1) {
		other->addItem(item);
		m_itemlist.remove(item);
		m_weight = m_weight - item->getWeight();
		return true;
	}
	else if(removeItem(item, sum)){
		other->addItem(id, sum);
		return true;
	}
	return false;

}

ProtectedTransfer<Item> Container::moveItem(Item* item) {
	if (!findItem(item))return nullptr;
	m_itemlist.remove(item);
	m_weight = m_weight - item->getWeight();
	return item;
}


bool Container::moveAllItems(Container* other) {
	for (auto itr = m_itemlist.begin(); itr != m_itemlist.end();)
	{
		auto item = *itr;
		if (item->getMaxSuperPosition() == 1) other->addItem(item); 
		else other->addItem(item->getID(), item->getSum());
		itr = m_itemlist.erase(itr);
	}
	m_weight = 0;
	return true;
}

//查询是否能添加物品
bool Container::ifaddItem(int id, int sum){
	double weight = ItemDataBase::getInstance()->getData(id, e_weight).asDouble();
	if(m_weight + weight * sum > m_maxweight)return false;
	return true;
}

//查询是否能添加物品
bool Container::ifaddItem(Item* item) {
	if (m_weight + item->getWeight() > m_maxweight)return false;
	return true;
}


Item* Container::findItem(int id) {
	for (auto i : m_itemlist)
	if (i->getID() == id)return i;
	return nullptr;
}

Item* Container::findItem(Item* item){
	if (!item)return nullptr;
	for (auto i : m_itemlist)
	if (i==item)return item;

	return nullptr;
}

//生成掉落物
Container* Container::createDrop(Item* i){
	auto map = ValueMap();
	map.insert(ValueMap::value_type("sprite", Value("Item/"+i->getName()+".png")));

	float dirx = cocos2d::rand_0_1() * 10 - 5;
	float diry = cocos2d::rand_0_1() * 10 - 5;

	//赋予掉落物位置一点点随机性
	map.insert(ValueMap::value_type("x", Value(this->getPositionX() + dirx)));
	map.insert(ValueMap::value_type("y", Value(this->getPositionY() + diry)));

	auto drop = Drop::create(std::move(map));

	//发送消息，让主层创建 掉落物
	NotificationCenter::getInstance()->postNotification("DROP_CREATE", drop);

	drop->getb2Body()->ApplyForceToCenter(b2Vec2(dirx,diry),true);

	return drop;
}
void Container::throwAllContainerDrops() {
	while (!m_itemlist.empty()) {
		auto item = m_itemlist.front();
		auto drop = createDrop(item);
		moveItem(item,item->getSum(),drop);
	}
}

//扔容器物品
void Container::throwContainerDrop(Item* i, int sum) {
	if (!findItem(i))return;
	auto drop = createDrop(i);
	moveItem(i,sum,drop);
}

//显示/隐藏Tab键
void Container::showTabKey() {
	if (!m_tabSprite)
	{
		m_tabSprite = Sprite::create("UI/png/ButtonTab.png");
		m_tabSprite->setScale(0.1f);
		m_tabSprite->setPositionY(this->getContentSize().height + 20);
		this->addChild(m_tabSprite);
	}
	m_tabSprite->setVisible(true);
}
void Container::hideTabKey() {
	if(m_tabSprite)
	m_tabSprite->setVisible(false);
}