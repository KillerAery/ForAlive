#include "Biology.h"
#include "GameManager.h"
#include "TriggerManager.h"

using cocos2d::Director;
using cocos2d::NotificationCenter;
//观测各实体 移动

Biology::Biology() :m_velocity(Vec2(0, 0)), m_attack(10), m_speed(2), m_biologytpye(BiologyTpye::player), m_ifcooltime(true),m_maxhealth(130), m_health(100), m_hungry(100), m_direction(Vec2(0,0)),
m_gearvec(RightHandGear+1), m_inhandindex(RightHandGear),m_relationship(nullptr),m_perception(nullptr),m_speakWords(nullptr),m_ifRequireToTalk(false){}

Biology::~Biology() {
	for (auto i : m_gearvec)
		if(i)delete i;
}

bool Biology::init(ValueMap& obj_valuemap) {
	if (!Container::init(obj_valuemap))return false;
	//————————生物属性
	m_speed = obj_valuemap["speed"].asFloat();
	m_biologytpye = static_cast<BiologyTpye>(obj_valuemap["biologytpye"].asInt());
	//-----------------生物 添加血条模块
	this->initBloodBar();
	//--------------------生物更新
	this->scheduleUpdate();
	//每n秒发出一次脚步声
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

//生物的物理身体初始化方式和实体不同
bool Biology::initPhysics(ValueMap& obj_valuemap) {
	this->setAnchorPoint(Vec2(0, 0));//使精灵和物理身体的坐标同步一致

	b2BodyDef BodyDef;
	//物理body类型
	BodyDef.type = static_cast<b2BodyType>(obj_valuemap["physicstpye"].asInt());
	BodyDef.position.Set((this->getPositionX()) / PTM_RATIO, (this->getPositionY()) / PTM_RATIO);
	BodyDef.fixedRotation = true;
	//物理夹具 
	b2FixtureDef fixtureDef;
	//密度
	fixtureDef.density = 1.0f;
	//摩擦因数
	fixtureDef.friction = 0.3f;
	fixtureDef.filter.groupIndex = obj_valuemap["groupindex"].asInt();

	//---------------------身体碰撞------------------
	m_b2body = GameManager::getInstance()->getb2World()->CreateBody(&BodyDef);
	m_b2body->SetUserData(this);
	//方形物理体积
	b2PolygonShape dynamicBox;
	//BOX(1,1)相当于2*2的BOX
	dynamicBox.SetAsBox(this->getContentSize().width / PTM_RATIO / 2, this->getContentSize().height / PTM_RATIO / 2);
	fixtureDef.shape = &dynamicBox;
	//掩码   负数相等时永远不会碰撞   正数相等时永远会碰撞
	fixtureDef.filter.maskBits = 0x02;//0010
	fixtureDef.filter.categoryBits = 0x01;
	m_b2body->CreateFixture(&fixtureDef);

	//---------------------脚步碰撞------------------
	auto b2bodyA = GameManager::getInstance()->getb2World()->CreateBody(&BodyDef);
	b2bodyA->SetUserData(this);
	b2bodyA->SetTransform(b2bodyA->GetPosition() - b2Vec2(0, this->getContentSize().height / PTM_RATIO / 2), b2bodyA->GetAngle());
	//方形物理体积--脚步碰撞
	b2PolygonShape footShape;
	footShape.SetAsBox(this->getContentSize().width / PTM_RATIO / 2.5, this->getContentSize().height / PTM_RATIO / 7);
	fixtureDef.shape = &footShape;
	fixtureDef.filter.maskBits = 0x08;
	fixtureDef.filter.categoryBits = 0x08;
	b2bodyA->CreateFixture(&fixtureDef);


	//定义一个连接刚体
	b2RevoluteJointDef jointDef;
	jointDef.Initialize(b2bodyA, m_b2body, m_b2body->GetWorldCenter());
	//通过CreateJoint建立关节
	GameManager::getInstance()->getb2World()->CreateJoint(&jointDef);

	return true;
}

//死亡--预移除
void Biology::die() {
	setIfPredelete(true);

	//尸体图片留在地图上
	string deadBodySpriteFile;
	if (m_biologytpye == BiologyTpye::zombie)deadBodySpriteFile = "Entities/zombie_die.png";
	else deadBodySpriteFile = cocos2d::StringUtils::format("Entities/human%d_die.png", m_id);

	auto deadBody = Sprite::create(deadBodySpriteFile);
	this->getParent()->addChild(deadBody);
	deadBody->setFlipX(m_sp->isFlipX());
	deadBody->setPosition(Vec2(getPositionX(),getPositionY()+20));
	deadBody->setPositionZ(-(deadBody->getPositionY() + 80) / 40);
	deadBody->setZOrder(INT_MAX - deadBody->getPositionY()-100);

	//死亡音乐
	if (m_biologytpye == BiologyTpye::zombie)GameManager::getInstance()->playEffect("Music/zombie_die.mp3",getPosition());
}

//从场景中移除
void Biology::removeFromScene() {
//针对生物 的物理形状
	auto jointList = m_b2body->GetJointList();
	//有关节的话
	if (jointList) {
		auto joint = jointList->joint;
		auto bodyA = joint->GetBodyA();
		auto bodyB = joint->GetBodyB();
		//必须先摧毁关节
		m_b2body->GetWorld()->DestroyJoint(joint);
		//再摧毁身体
		if (bodyA != m_b2body)	m_b2body->GetWorld()->DestroyBody(bodyA);
		else m_b2body->GetWorld()->DestroyBody(bodyB);
	}

	throwContainer();
	//触发检测
	TriggerManager::getInstance()->checkKillTrigger(m_biologytpye);
	//发出移除消息
	NotificationCenter::getInstance()->postNotification("BIOLOGY_REMOVE", this);
	Container::removeFromScene();
}

//每秒更新 生物 移动速度方向
void Biology::update(float dt){
	m_b2body->SetLinearVelocity(b2Vec2(m_velocity.x, m_velocity.y));
	//如果方向朝某一边，则图像翻转至该边
	if (m_velocity.x < 0)m_sp->setFlipX(true);
	else if (m_velocity.x >0) m_sp->setFlipX(false);
}
//脚步声音
void Biology::makeFootEffect(float dt) {
	if (m_velocity.getLengthSq() >= 0.7)
		GameManager::getInstance()->playFootEffect(this->getPosition());
}

double Biology::getHealth(){
	return m_health;
}

//血量改变时  显示血量条
void Biology::setHealth(double i) {
	if (i <= 0){
	this->die();
	return;
	}
	//被攻击音乐
	if(i<m_health&&m_biologytpye == BiologyTpye::zombie)GameManager::getInstance()->playEffect("Music/zombie_underattack.mp3", getPosition());

	m_health = i;

	m_bloodbar->showBloodBar(this);
}

int Biology::getInHandIndex(){
	return m_inhandindex;
}

void Biology::setInHandIndex(int i) {
	CCASSERT(i == LeftHandGear || i == RightHandGear, "ERROR!!!!!!你的手太多了，i超出了左手和右手");
	//如果不同手
	if (m_inhandindex != i){
		GameTool::getInstance()->playEffect("Music/switchgun.mp3");
		m_inhandindex = i;

		checkTexture();
	}
}

//射出一发锁定目标的 子弹
void Biology::attack(const Vec2& dir) {
	if (!m_ifcooltime)return;

	if (m_gearvec[m_inhandindex]){
		//使用手里的武器
		this->useItem(m_gearvec[m_inhandindex], dir, 1);
		return;
	}

	if (m_biologytpye == BiologyTpye::zombie|| m_biologytpye == BiologyTpye::player){
		auto nearestEnemy = m_perception->getNearest(Attitude::against);
		if (!nearestEnemy)return;
		//如果有感知目标，求最近的一个目标

		//最近的一个感知目标
		if (nearestEnemy->getPosition().getDistanceSq(getPosition()) <= 35 * 35) {
			nearestEnemy->setHealth(nearestEnemy->getHealth() - getAttack());
			m_ifcooltime = false;

			//如果方向朝某一边，则图像翻转至该边
			if (dir.x < 0)m_sp->setFlipX(true);
			else if (dir.x > 0) m_sp->setFlipX(false);

			this->scheduleOnce([this](float dt) {m_ifcooltime = true;}, 0.4f, "cooltime_attack");
		}
	}
	else if (m_biologytpye == BiologyTpye::human) {}
}

//射出一发锁定方向的 子弹
void Biology::attack(){
	attack(m_direction);
}



/*-----------------------------装备模块-----------------------*/


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
	//不同持武器，不同图像
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

//使用者对使用者使用
bool Biology::itemUseable(Item* i, int usesum) { return i->useable(this, usesum); }
void Biology::useItem(Item* i, int usesum) {i->use(this, usesum);}
//使用者对生物使用
bool Biology::itemUseable(Item* i, Biology* biology, int usesum) { return i->useable(this, biology, usesum); }
void Biology::useItem(Item* i, Biology* biology, int usesum) { i->use(this, biology, usesum);}
//使用者对物体使用
bool Biology::itemUseable(Item* i, Entity* entity, int usesum) { return i->useable(this, entity, usesum); }
void Biology::useItem(Item* i, Entity* entity, int usesum) {i->use(this, entity, usesum);}
//使用者对一个方向使用
bool Biology::itemUseable(Item* i, const Vec2& direction, int usesum) {return  i->useable(this, direction, usesum); }
void Biology::useItem(Item* i, const Vec2& direction, int usesum) {i->use(this, direction, usesum);}
//使用者对一个物品使用
bool Biology::itemUseable(Item* i, Item* preusedItem, int usesum) { return i->useable(this, preusedItem, usesum); }
void Biology::useItem(Item* i, Item* preusedItem, int usesum) {i->use(this, preusedItem, usesum);}

//查找函数
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

//生成骨灰盒
void Biology::throwContainer() {
	//扔容器上的物品
	this->throwAllContainerDrops();

	//扔身上的装备物品
	for(int i = GearTpye::BodyGear ; i <= GearTpye::RightHandGear ; ++i)
		if(m_gearvec[i])this->throwGearDrop(GearTpye(i),m_gearvec[i]->getSum());

	
}

//捡起最近的掉落物
void Biology::pickupNearestDrop() {
	auto drop = m_perception->getNearestDrop();
	if (!drop)return;
	//超出重量则不拾取
	if (m_weight + drop->getWeight() > m_maxweight)return;
	drop->moveAllItems(this);
}

//生成掉落物
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

/*-----------------------------血条模块-----------------------*/
void Biology::initBloodBar() {
	//初始化血条
	m_bloodbar = BloodBar::create();
	m_bloodbar->setPositionY(getContentSize().height);
	m_bloodbar->setVisible(false);
	this->addChild(m_bloodbar);
}

/*-----------------------------AI所需的感知模块-----------------------*/

Perceptionable* Biology::getPerception() {
	return m_perception;
}

void Biology::setPerception(Perceptionable* percetion) {
	if (m_perception)m_perception->removeFromParent();
	m_perception = percetion;
	this->addChild(m_perception);
}

/*--------------------------说话模块-------------------*/
//说额外的话，原来的话语往上移动，新增话语
void Biology::speakAdditionWords(const string& words){
	if (!m_speakWords) { speakWords(words); return; }
	m_speakWords->pushAdditionWords(words);
}
//直接说话，覆盖原来的话语
void Biology::speakWords(const string& words) {
	if (m_speakWords)this->removeChild(m_speakWords);

	m_speakWords = SpeakWords::create();
	this->addChild(m_speakWords);
	m_speakWords->pushAdditionWords(words);
}