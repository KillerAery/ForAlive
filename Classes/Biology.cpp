#include "Biology.h"
#include "GameManager.h"
#include "TriggerManager.h"

using cocos2d::Director;
using cocos2d::NotificationCenter;
//�۲��ʵ�� �ƶ�

Biology::Biology() :m_velocity(Vec2(0, 0)), m_attack(10), m_speed(2), m_biologytpye(BiologyTpye::player), m_ifcooltime(true),m_maxhealth(130), m_health(100), m_hungry(100), m_direction(Vec2(0,0)),
m_gearvec(RightHandGear+1), m_inhandindex(RightHandGear),m_relationship(nullptr),m_perception(nullptr),m_speakWords(nullptr),m_ifRequireToTalk(false){}

Biology::~Biology() {
	for (auto i : m_gearvec)
		if(i)delete i;
}

bool Biology::init(ValueMap& obj_valuemap) {
	if (!Container::init(obj_valuemap))return false;
	//������������������������
	m_speed = obj_valuemap["speed"].asFloat();
	m_biologytpye = static_cast<BiologyTpye>(obj_valuemap["biologytpye"].asInt());
	//-----------------���� ���Ѫ��ģ��
	this->initBloodBar();
	//--------------------�������
	this->scheduleUpdate();
	//ÿn�뷢��һ�νŲ���
	this->schedule(CC_SCHEDULE_SELECTOR(Biology::makeFootEffect),0.3f,UINT_MAX,0);
	switch (m_biologytpye)
	{
	case BiologyTpye::zombie:
		addItem(101, cocos2d::rand_0_1() * 2);
		addItem(105, cocos2d::rand_0_1() * 2);
		addItem(103, cocos2d::rand_0_1() * 2);
		addItem(201, cocos2d::rand_0_1() * 4);
		addItem(202, cocos2d::rand_0_1() * 2);
		setIfPublic(false);
		break;
	case BiologyTpye::human:
		if ( m_id == 30)wearGear(1, 1, RightHandGear);
		else if(m_id == 171)wearGear(2, 1, RightHandGear);
		break;
	default:
		break;
	}
	return true;
}

//��������������ʼ����ʽ��ʵ�岻ͬ
bool Biology::initPhysics(ValueMap& obj_valuemap) {
	this->setAnchorPoint(Vec2(0, 0));//ʹ������������������ͬ��һ��

	b2BodyDef BodyDef;
	//����body����
	BodyDef.type = static_cast<b2BodyType>(obj_valuemap["physicstpye"].asInt());
	BodyDef.position.Set((this->getPositionX()) / PTM_RATIO, (this->getPositionY()) / PTM_RATIO);
	BodyDef.fixedRotation = true;
	//����о� 
	b2FixtureDef fixtureDef;
	//�ܶ�
	fixtureDef.density = 1.0f;
	//Ħ������
	fixtureDef.friction = 0.3f;
	fixtureDef.filter.groupIndex = obj_valuemap["groupindex"].asInt();

	//---------------------������ײ------------------
	m_b2body = GameManager::getInstance()->getb2World()->CreateBody(&BodyDef);
	m_b2body->SetUserData(this);
	//�����������
	b2PolygonShape dynamicBox;
	//BOX(1,1)�൱��2*2��BOX
	dynamicBox.SetAsBox(this->getContentSize().width / PTM_RATIO / 2, this->getContentSize().height / PTM_RATIO / 2);
	fixtureDef.shape = &dynamicBox;
	//����   �������ʱ��Զ������ײ   �������ʱ��Զ����ײ
	fixtureDef.filter.maskBits = 0x02;//0010
	fixtureDef.filter.categoryBits = 0x01;
	m_b2body->CreateFixture(&fixtureDef);

	//---------------------�Ų���ײ------------------
	auto b2bodyA = GameManager::getInstance()->getb2World()->CreateBody(&BodyDef);
	b2bodyA->SetUserData(this);
	b2bodyA->SetTransform(b2bodyA->GetPosition() - b2Vec2(0, this->getContentSize().height / PTM_RATIO / 2), b2bodyA->GetAngle());
	//�����������--�Ų���ײ
	b2PolygonShape footShape;
	footShape.SetAsBox(this->getContentSize().width / PTM_RATIO / 2.5, this->getContentSize().height / PTM_RATIO / 7);
	fixtureDef.shape = &footShape;
	fixtureDef.filter.maskBits = 0x08;
	fixtureDef.filter.categoryBits = 0x08;
	b2bodyA->CreateFixture(&fixtureDef);


	//����һ�����Ӹ���
	b2RevoluteJointDef jointDef;
	jointDef.Initialize(b2bodyA, m_b2body, m_b2body->GetWorldCenter());
	//ͨ��CreateJoint�����ؽ�
	GameManager::getInstance()->getb2World()->CreateJoint(&jointDef);

	return true;
}

//����--Ԥ�Ƴ�
void Biology::die() {
	setIfPredelete(true);

	//ʬ��ͼƬ���ڵ�ͼ��
	string deadBodySpriteFile;
	if (m_biologytpye == BiologyTpye::zombie)deadBodySpriteFile = "Entities/zombie_die.png";
	else deadBodySpriteFile = cocos2d::StringUtils::format("Entities/human%d_die.png", m_id);

	auto deadBody = Sprite::create(deadBodySpriteFile);
	this->getParent()->addChild(deadBody);
	deadBody->setFlipX(m_sp->isFlipX());
	deadBody->setPosition(Vec2(getPositionX(),getPositionY()+20));
	deadBody->setPositionZ(-(deadBody->getPositionY() + 80) / 40);
	deadBody->setZOrder(INT_MAX - deadBody->getPositionY()-100);

	//��������
	if (m_biologytpye == BiologyTpye::zombie)GameManager::getInstance()->playEffect("Music/zombie_die.mp3",getPosition());
}

//�ӳ������Ƴ�
void Biology::removeFromScene() {
//������� ��������״
	auto jointList = m_b2body->GetJointList();
	//�йؽڵĻ�
	if (jointList) {
		auto joint = jointList->joint;
		auto bodyA = joint->GetBodyA();
		auto bodyB = joint->GetBodyB();
		//�����ȴݻٹؽ�
		m_b2body->GetWorld()->DestroyJoint(joint);
		//�ٴݻ�����
		if (bodyA != m_b2body)	m_b2body->GetWorld()->DestroyBody(bodyA);
		else m_b2body->GetWorld()->DestroyBody(bodyB);
	}

	throwContainer();
	//�������
	TriggerManager::getInstance()->checkKillTrigger(m_biologytpye);
	//�����Ƴ���Ϣ
	NotificationCenter::getInstance()->postNotification("BIOLOGY_REMOVE", this);
	Container::removeFromScene();
}

//ÿ����� ���� �ƶ��ٶȷ���
void Biology::update(float dt){
	m_b2body->SetLinearVelocity(b2Vec2(m_velocity.x, m_velocity.y));
	//�������ĳһ�ߣ���ͼ��ת���ñ�
	if (m_velocity.x < 0)m_sp->setFlipX(true);
	else if (m_velocity.x >0) m_sp->setFlipX(false);
}
//�Ų�����
void Biology::makeFootEffect(float dt) {
	if (m_velocity.getLengthSq() >= 0.7)
		GameManager::getInstance()->playFootEffect(this->getPosition());
}

double Biology::getHealth(){
	return m_health;
}

//Ѫ���ı�ʱ  ��ʾѪ����
void Biology::setHealth(double i) {
	if (i <= 0){
	this->die();
	return;
	}
	//����������
	if(i<m_health&&m_biologytpye == BiologyTpye::zombie)GameManager::getInstance()->playEffect("Music/zombie_underattack.mp3", getPosition());

	m_health = i;

	m_bloodbar->showBloodBar(this);
}

int Biology::getInHandIndex(){
	return m_inhandindex;
}

void Biology::setInHandIndex(int i) {
	CCASSERT(i == LeftHandGear || i == RightHandGear, "ERROR!!!!!!�����̫���ˣ�i���������ֺ�����");
	//�����ͬ��
	if (m_inhandindex != i){
		GameTool::getInstance()->playEffect("Music/switchgun.mp3");
		m_inhandindex = i;

		checkTexture();
	}
}

//���һ������Ŀ��� �ӵ�
void Biology::attack(const Vec2& dir) {
	if (!m_ifcooltime)return;

	if (m_gearvec[m_inhandindex]){
		//ʹ�����������
		this->useItem(m_gearvec[m_inhandindex], dir, 1);
		return;
	}

	if (m_biologytpye == BiologyTpye::zombie|| m_biologytpye == BiologyTpye::player){
		auto nearestEnemy = m_perception->getNearest(Attitude::against);
		if (!nearestEnemy)return;
		//����и�֪Ŀ�꣬�������һ��Ŀ��

		//�����һ����֪Ŀ��
		if (nearestEnemy->getPosition().getDistanceSq(getPosition()) <= 35 * 35) {
			nearestEnemy->setHealth(nearestEnemy->getHealth() - getAttack());
			m_ifcooltime = false;

			//�������ĳһ�ߣ���ͼ��ת���ñ�
			if (dir.x < 0)m_sp->setFlipX(true);
			else if (dir.x > 0) m_sp->setFlipX(false);

			this->scheduleOnce([this](float dt) {m_ifcooltime = true;}, 0.4f, "cooltime_attack");
		}
	}
	else if (m_biologytpye == BiologyTpye::human) {}
}

//���һ����������� �ӵ�
void Biology::attack(){
	attack(m_direction);
}



/*-----------------------------װ��ģ��-----------------------*/


bool Biology::wearGear(ProtectedTransfer<Item> i, GearTpye gtpye) {
	if (m_gearvec[gtpye]) {
		this->addItem(m_gearvec[gtpye]);
		m_gearvec[gtpye]=nullptr;
	}

	m_gearvec[gtpye] = i.getValueAndClearProtectedTansfer();

	GameManager::getInstance()->playEffect("Music/switchgun.mp3",getPosition());

	checkTexture();

	return true;
}

bool Biology::wearGear(int id, int sum, GearTpye gtpye) {
	auto i = ItemFactory::createItem(id,sum);
	if (!i)return false;

	return wearGear(i, gtpye);
}

bool Biology::removeGear(GearTpye tpye, int num) {
	if (!m_gearvec[tpye])return false;
	m_gearvec[tpye]->reduceSum(num);
	if (m_gearvec[tpye]->getSum() <= 0)CC_SAFE_DELETE(m_gearvec[tpye]);
	checkTexture();
	return true;
}

bool Biology::removeGear(GearTpye gtpye) {
	if(!m_gearvec[gtpye])return false;
	delete m_gearvec[gtpye];
	m_gearvec[gtpye] = nullptr;
	checkTexture();
	return true;
}

ProtectedTransfer<Item> Biology::moveGear(GearTpye tpye) {
	auto item = m_gearvec[tpye];
	m_gearvec[tpye] = nullptr;
	checkTexture();
	return item;
}

void Biology::checkTexture(){
	//��ͬ����������ͬͼ��
	string str;
	if (m_biologytpye != BiologyTpye::zombie) {
		str = cocos2d::StringUtils::format("human%d", m_id);
		if (!m_gearvec[m_inhandindex])str += ".png";
		else if (m_gearvec[m_inhandindex]->getID() == 1)str += "_ak.png";
		else if (m_gearvec[m_inhandindex]->getID() == 2)str += "_shotgun.png";
	}
	else
	{
		str = "zombie.png";
	}
	m_sp->setTexture(str);
}

//ʹ���߶�ʹ����ʹ��
bool Biology::itemUseable(Item* i, int usesum) { return i->useable(this, usesum); }
void Biology::useItem(Item* i, int usesum) {i->use(this, usesum);}
//ʹ���߶�����ʹ��
bool Biology::itemUseable(Item* i, Biology* biology, int usesum) { return i->useable(this, biology, usesum); }
void Biology::useItem(Item* i, Biology* biology, int usesum) { i->use(this, biology, usesum);}
//ʹ���߶�����ʹ��
bool Biology::itemUseable(Item* i, Entity* entity, int usesum) { return i->useable(this, entity, usesum); }
void Biology::useItem(Item* i, Entity* entity, int usesum) {i->use(this, entity, usesum);}
//ʹ���߶�һ������ʹ��
bool Biology::itemUseable(Item* i, const Vec2& direction, int usesum) {return  i->useable(this, direction, usesum); }
void Biology::useItem(Item* i, const Vec2& direction, int usesum) {i->use(this, direction, usesum);}
//ʹ���߶�һ����Ʒʹ��
bool Biology::itemUseable(Item* i, Item* preusedItem, int usesum) { return i->useable(this, preusedItem, usesum); }
void Biology::useItem(Item* i, Item* preusedItem, int usesum) {i->use(this, preusedItem, usesum);}

//���Һ���
Item* Biology::findGearItem(int id) {
	for (auto item : m_gearvec)
		if (item&&item->getID() == id)return item;

	return nullptr;
}
Item* Biology::findGearItem(Item* item) {
	if (!item)return nullptr;

	for (auto i : m_gearvec)
		if (i == item)return item;

	return nullptr;
}

//���ɹǻҺ�
void Biology::throwContainer() {
	//�������ϵ���Ʒ
	this->throwAllContainerDrops();

	//�����ϵ�װ����Ʒ
	for(int i = GearTpye::BodyGear ; i <= GearTpye::RightHandGear ; ++i)
		if(m_gearvec[i])this->throwGearDrop(GearTpye(i),m_gearvec[i]->getSum());

	
}

//��������ĵ�����
void Biology::pickupNearestDrop() {
	auto drop = m_perception->getNearestDrop();
	if (!drop)return;
	//����������ʰȡ
	if (m_weight + drop->getWeight() > m_maxweight)return;
	drop->moveAllItems(this);
}

//���ɵ�����
void Biology::throwGearDrop(GearTpye gtpye,int sum) {
	if (!m_gearvec[gtpye])return;
	auto drop = createDrop(m_gearvec[gtpye]);
	if(sum== m_gearvec[gtpye]->getSum())
	drop->addItem(moveGear(gtpye).getValueAndClearProtectedTansfer());
	else
	{
		removeGear(gtpye, sum);
		drop->addItem(m_gearvec[gtpye]->getID(),sum);
	}
}

/*-----------------------------Ѫ��ģ��-----------------------*/
void Biology::initBloodBar() {
	//��ʼ��Ѫ��
	m_bloodbar = BloodBar::create();
	m_bloodbar->setPositionY(getContentSize().height);
	m_bloodbar->setVisible(false);
	this->addChild(m_bloodbar);
}

/*-----------------------------AI����ĸ�֪ģ��-----------------------*/

Perceptionable* Biology::getPerception() {
	return m_perception;
}

void Biology::setPerception(Perceptionable* percetion) {
	if (m_perception)m_perception->removeFromParent();
	m_perception = percetion;
	this->addChild(m_perception);
}

/*--------------------------˵��ģ��-------------------*/
//˵����Ļ���ԭ���Ļ��������ƶ�����������
void Biology::speakAdditionWords(const string& words){
	if (!m_speakWords) { speakWords(words); return; }
	m_speakWords->pushAdditionWords(words);
}
//ֱ��˵��������ԭ���Ļ���
void Biology::speakWords(const string& words) {
	if (m_speakWords)this->removeChild(m_speakWords);

	m_speakWords = SpeakWords::create();
	this->addChild(m_speakWords);
	m_speakWords->pushAdditionWords(words);
}