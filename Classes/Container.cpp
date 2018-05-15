#pragma once
#include "Container.h"
#include "Drop.h"


using namespace cocos2d;
using cocos2d::Director;
using cocos2d::NotificationCenter;

Container::Container():m_ifpublic(true),m_maxweight(60.0),m_weight(0.0),m_tabSprite(nullptr){}
Container::~Container() {
	//�ͷ�������item��Դ
	for (auto i : m_itemlist){delete i;}
}

bool Container::init(ValueMap& obj_valuemap){
	obj_valuemap.insert(ValueMap::value_type("groupindex", Value(-obj_valuemap["id"].asInt())));//����groundindex
	if (!Entity::init(obj_valuemap))return false;
	//������������
	this->setName(obj_valuemap["name"].asString());
	this->initItemsByValueMap(obj_valuemap);
	return true;
}

void Container::initItemsByValueMap(ValueMap& obj_valuemap) {
	if (obj_valuemap.find("items")==obj_valuemap.end())return;
	//����items���ַ���Ϊitem��������Ϣ
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
	//����
	m_b2body->SetLinearDamping(5.0f);
	return true;
}

Container* Container::create(ValueMap & obj_valuemap) {
	obj_valuemap.insert(ValueMap::value_type("entitytpye", Value(int(EntityTpye::container))));
	obj_valuemap.insert(ValueMap::value_type("physicstpye", Value(int(b2BodyType::b2_staticBody))));
	obj_valuemap.insert(ValueMap::value_type("maskbit", Value(8)));//1000
	obj_valuemap.insert(ValueMap::value_type("categorybits", Value(8)));//1000
	//��ֵ�bug��tilemap�����ӵ�λ�ú�ʵ��λ����200,100��ƫ��
	//��ʱ��ô�޸�
	obj_valuemap["x"] = obj_valuemap["x"].asInt() + obj_valuemap["width"].asInt()/2 +150;
	obj_valuemap["y"] = obj_valuemap["y"].asInt() + obj_valuemap["height"].asInt()/2+80;

	auto c = new (std::nothrow)Container();
	if (c&&c->init(obj_valuemap)) {c->autorelease(); }
	else { CC_SAFE_DELETE(c); }
	return c;
}

//�ӳ������Ƴ�
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

	//�������Ϊ0����Ʒ
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

//�����������Ϊ0����Ʒ��
void Container::clear0numItems(){
	for (auto it = m_itemlist.begin(); it != m_itemlist.end();){
		if ((*it)->getSum() <= 0) {
			//�� ����Ϊ0 ���ͷ���Ʒ
			delete (*it);
			it = m_itemlist.erase(it);
		}
		else ++it;
	}
}


//�����Ʒ
bool Container::addItem(int id, int sum){
	if (sum <= 0)return false;

	//���ѵ���Ʒ��
	auto MAXS = ItemDataBase::getInstance()->getData(id, e_maxsuperposition).asInt();

	//�����������ʱ  
	while(sum > MAXS){ addItem(id,MAXS); sum = sum - MAXS;}
	//���Ѵ��ڸ�item���ͣ���������� 
	for (auto item : m_itemlist){
		if (item->getID() == id){
			//ͬ��item�����ﵽ���ޣ���������
			if (item->getSum() >= MAXS)continue;
			//ͬ��item����+sum�����ﵽ���ޣ��Ƚ�ͬ��item�����������ٽ�����item���� ������Ʒ��ʽ���
			else if (item->getSum() + sum >MAXS) {
				//����ͬ��item����
				int addition = MAXS - item->getSum();
				sum -= addition;
				addItemSum(item,addition);
				//�������Ʒ �����item����
				return addItem(id, sum);
			}
			//ͬ��item+sum����δ�����ޣ�����ֱ�����
			else {
				addItemSum(item,sum);
				return true;
			}
			}
	}
	//�������ڣ����½�item
	createItem(id,sum);
	return true;
}

//�����Ʒ
bool Container::addItem(ProtectedTransfer<Item> item) {
	createItem(item.getValueAndClearProtectedTansfer());
	return true;
}

//�Ƴ���Ʒ
bool Container::removeItem(int id, int sum){
	int totalsum= 0;
	//ͳ�Ƹ�����Ʒ����������
	for (auto i : m_itemlist)
		if (id == i->getID())totalsum += i->getSum();

	//�Ƴ����� ��������
	if (sum > totalsum)return false;

	int temp;
	//��������֮��
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


//�ƶ���Ʒ����һ������
bool Container::moveItem(int id, int sum, Container* other) {
	//����һ������ Ȩ�޲���������������
	if (!other->getIfPublic())return false;
	//��ѯ�Լ������Ƿ�����ת������
	if (!removeItem(id, sum))return false;
	//��ѯ��һ�������Ƿ�����ת������
	other->addItem(id, sum);
	return true;
}

bool Container::moveItem(Item* item, int sum, Container* other) {
	//����һ������ Ȩ�޲���������������
	if (!other->getIfPublic() || !findItem(item))return false;
	int id = item->getID();
	//��ѯ�Լ������Ƿ�����ת������
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

//��ѯ�Ƿ��������Ʒ
bool Container::ifaddItem(int id, int sum){
	double weight = ItemDataBase::getInstance()->getData(id, e_weight).asDouble();
	if(m_weight + weight * sum > m_maxweight)return false;
	return true;
}

//��ѯ�Ƿ��������Ʒ
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

//���ɵ�����
Container* Container::createDrop(Item* i){
	auto map = ValueMap();
	map.insert(ValueMap::value_type("sprite", Value("Item/"+i->getName()+".png")));

	float dirx = cocos2d::rand_0_1() * 10 - 5;
	float diry = cocos2d::rand_0_1() * 10 - 5;

	//���������λ��һ��������
	map.insert(ValueMap::value_type("x", Value(this->getPositionX() + dirx)));
	map.insert(ValueMap::value_type("y", Value(this->getPositionY() + diry)));

	auto drop = Drop::create(std::move(map));

	//������Ϣ�������㴴�� ������
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

//��������Ʒ
void Container::throwContainerDrop(Item* i, int sum) {
	if (!findItem(i))return;
	auto drop = createDrop(i);
	moveItem(i,sum,drop);
}

//��ʾ/����Tab��
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