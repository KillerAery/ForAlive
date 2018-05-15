#include "Entity.h"
#include "GameManager.h"

using cocos2d::Director;

Entity::Entity():m_b2body(nullptr),m_sp(nullptr),m_entityTpye(EntityTpye::entity),m_ifpredelete(false),m_id(0){}

Entity::~Entity(){}

bool Entity::init(ValueMap& obj_valuemap){
	if(!Node::init())return false;
	//���þ���
	//this->setSprite(Sprite::create("human4.png"));
	auto str = obj_valuemap["sprite"].asString();
	this->setSprite(Sprite::create(obj_valuemap["sprite"].asString()));
	m_sp->setAnchorPoint(Vec2(0.5,0));
	this->addChild(m_sp);
	//����ʵ������
	this->setEntityTpye(static_cast<EntityTpye>(obj_valuemap["entitytpye"].asInt()));
	//����λ��
	this->setPosition(obj_valuemap["x"].asFloat(), obj_valuemap["y"].asFloat());
	//����id
	this->setID(obj_valuemap["id"].asInt());
	//�������
	if (obj_valuemap["width"].asFloat()>1.0f) this->setContentSize(Size(obj_valuemap["width"].asFloat(), obj_valuemap["height"].asFloat()));
	else this->setContentSize(m_sp->getContentSize());
	//��ʼ������
	this->initPhysics(obj_valuemap);

	return true;
}

/*--------------��ײ����--------------
�ӵ� 0001,1111
������ 0010,0001
�˽� 1000,1000
ǽ�� 1000,1001
���� 1000,1000
*/

//ʵ�����������ʼ��
bool Entity::initPhysics(ValueMap& obj_valuemap) {
	this->setAnchorPoint(Vec2(0, 0.5));//ʹ������������������ͬ��һ��

	b2BodyDef bodyDef;
	//����body����
	bodyDef.type = static_cast<b2BodyType>(obj_valuemap["physicstpye"].asInt());
	bodyDef.position.Set(this->getPositionX() / PTM_RATIO, this->getPositionY()/ PTM_RATIO);

	bodyDef.fixedRotation = true;
	m_b2body = GameManager::getInstance()->getb2World()->CreateBody(&bodyDef);
	m_b2body->SetUserData(this);
	this->setb2Body(m_b2body);

	//�����������
	b2PolygonShape dynamicBox;

	//BOX(1,1)�൱��2*2��BOX
	dynamicBox.SetAsBox(this->getContentSize().width / PTM_RATIO / 2, this->getContentSize().height / PTM_RATIO / 2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	//�ܶ�
	fixtureDef.density = 1.0f;
	//Ħ������
	fixtureDef.friction = 0.3f;

	//����   �������ʱ��Զ������ײ   �������ʱ��Զ����ײ
	fixtureDef.filter.groupIndex = obj_valuemap["groupindex"].asInt();
	fixtureDef.filter.maskBits = obj_valuemap["maskbit"].asInt();
	fixtureDef.filter.categoryBits = obj_valuemap["categorybits"].asInt();

	m_b2body->CreateFixture(&fixtureDef);
	
	return true;
}

Entity* Entity::create(ValueMap& obj_valuemap){
	obj_valuemap.insert(ValueMap::value_type("entitytpye", Value(int(EntityTpye::entity))));

	auto e = new (std::nothrow)Entity();
	if (e&&e->init(obj_valuemap)) {e->autorelease(); }
	else { CC_SAFE_DELETE(e); }
	return e;
}

//���ⷽ��  ����ǽ   ��ֻ�漰����ģ��  ���漰Entity
Entity*  Entity::createWall(ValueVector objects) {
	for (auto object : objects) {
		int x = object.asValueMap().at("x").asFloat();
		int y = object.asValueMap().at("y").asFloat();
		auto pointsVector = object.asValueMap().at("polylinePoints").asValueVector();


		b2Vec2 * vs = new b2Vec2[pointsVector.size()];
		int i = 0;

		for (auto point : pointsVector) {
			auto valuemap = point.asValueMap();
			vs[i] = b2Vec2((valuemap["x"].asFloat() + x) / PTM_RATIO, (-valuemap["y"].asFloat() + y) / PTM_RATIO);
			++i;
		}

		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.position.Set(0, 0);

		b2Body* body = GameManager::getInstance()->getb2World()->CreateBody(&bodyDef);
		body->SetUserData(nullptr);

		b2ChainShape chain;
		chain.CreateChain(vs, pointsVector.size());

		CC_SAFE_DELETE(vs);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &chain;
		//�ܶ�
		fixtureDef.density = 1.0f;
		//Ħ������
		fixtureDef.friction = 0.3f;
		fixtureDef.filter.maskBits = 0x08;
		fixtureDef.filter.categoryBits = 0x09;

		body->CreateFixture(&fixtureDef);
	}
	//ǽ����ʱ����Ҫ����
	return nullptr;
}

//�ӳ������Ƴ�
void Entity::removeFromScene() {
	m_b2body->GetWorld()->DestroyBody(m_b2body);	//������������

	this->removeFromParent();
}


void Entity::setPosition(const Vec2 & point) {
	Node::setPosition(point);
	this->setPositionZ(-((point.y + 80) / 40));
	//ZOrder��position����˳����ͻ������BUG��������ZORDER
	this->setZOrder(INT_MAX -point.y);
}
void Entity::setPosition(int x, int y) {
	Node::setPosition(x, y);
	this->setPositionZ(-((y + 80) / 40));
	//ZOrder��position����˳����ͻ������BUG��������ZORDER
	this->setZOrder(INT_MAX-y);
}