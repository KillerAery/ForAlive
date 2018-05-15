#include "Entity.h"
#include "GameManager.h"

using cocos2d::Director;

Entity::Entity():m_b2body(nullptr),m_sp(nullptr),m_entityTpye(EntityTpye::entity),m_ifpredelete(false),m_id(0){}

Entity::~Entity(){}

bool Entity::init(ValueMap& obj_valuemap){
	if(!Node::init())return false;
	//设置精灵
	//this->setSprite(Sprite::create("human4.png"));
	auto str = obj_valuemap["sprite"].asString();
	this->setSprite(Sprite::create(obj_valuemap["sprite"].asString()));
	m_sp->setAnchorPoint(Vec2(0.5,0));
	this->addChild(m_sp);
	//设置实体类型
	this->setEntityTpye(static_cast<EntityTpye>(obj_valuemap["entitytpye"].asInt()));
	//设置位置
	this->setPosition(obj_valuemap["x"].asFloat(), obj_valuemap["y"].asFloat());
	//设置id
	this->setID(obj_valuemap["id"].asInt());
	//设置体积
	if (obj_valuemap["width"].asFloat()>1.0f) this->setContentSize(Size(obj_valuemap["width"].asFloat(), obj_valuemap["height"].asFloat()));
	else this->setContentSize(m_sp->getContentSize());
	//初始化物理
	this->initPhysics(obj_valuemap);

	return true;
}

/*--------------碰撞掩码--------------
子弹 0001,1111
人身体 0010,0001
人脚 1000,1000
墙体 1000,1001
容器 1000,1000
*/

//实体物理身体初始化
bool Entity::initPhysics(ValueMap& obj_valuemap) {
	this->setAnchorPoint(Vec2(0, 0.5));//使精灵和物理身体的坐标同步一致

	b2BodyDef bodyDef;
	//物理body类型
	bodyDef.type = static_cast<b2BodyType>(obj_valuemap["physicstpye"].asInt());
	bodyDef.position.Set(this->getPositionX() / PTM_RATIO, this->getPositionY()/ PTM_RATIO);

	bodyDef.fixedRotation = true;
	m_b2body = GameManager::getInstance()->getb2World()->CreateBody(&bodyDef);
	m_b2body->SetUserData(this);
	this->setb2Body(m_b2body);

	//方形物理体积
	b2PolygonShape dynamicBox;

	//BOX(1,1)相当于2*2的BOX
	dynamicBox.SetAsBox(this->getContentSize().width / PTM_RATIO / 2, this->getContentSize().height / PTM_RATIO / 2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	//密度
	fixtureDef.density = 1.0f;
	//摩擦因数
	fixtureDef.friction = 0.3f;

	//掩码   负数相等时永远不会碰撞   正数相等时永远会碰撞
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

//特殊方法  创建墙   而只涉及物理模型  不涉及Entity
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
		//密度
		fixtureDef.density = 1.0f;
		//摩擦因数
		fixtureDef.friction = 0.3f;
		fixtureDef.filter.maskBits = 0x08;
		fixtureDef.filter.categoryBits = 0x09;

		body->CreateFixture(&fixtureDef);
	}
	//墙体暂时不需要对象
	return nullptr;
}

//从场景中移除
void Entity::removeFromScene() {
	m_b2body->GetWorld()->DestroyBody(m_b2body);	//销毁物理身体

	this->removeFromParent();
}


void Entity::setPosition(const Vec2 & point) {
	Node::setPosition(point);
	this->setPositionZ(-((point.y + 80) / 40));
	//ZOrder与position绘制顺序会冲突，产生BUG，故重设ZORDER
	this->setZOrder(INT_MAX -point.y);
}
void Entity::setPosition(int x, int y) {
	Node::setPosition(x, y);
	this->setPositionZ(-((y + 80) / 40));
	//ZOrder与position绘制顺序会冲突，产生BUG，故重设ZORDER
	this->setZOrder(INT_MAX-y);
}