#include "PhysicsWorld.h"
#include "GameManager.h"

PhysicsWorld::PhysicsWorld() :m_b2world(nullptr), m_b2listener(nullptr), _debugDraw(nullptr){}

PhysicsWorld::~PhysicsWorld() {
//���GameTool.h��ȫ�ֱ���world
GameManager::getInstance()->setb2World(nullptr);
//b2world��m_b2listener��_debugDraw ��New������û��cocos2dx ref�ṹ
CC_SAFE_DELETE(m_b2world);
CC_SAFE_DELETE(m_b2listener);
CC_SAFE_DELETE(_debugDraw);
}

bool PhysicsWorld::init(const Size& size) {
	//���ݳߴ紴������
	initWorld(size);	
	//��������debug ��ʾ					
	//---------------�ǵû���new�ڴ�
	_debugDraw = new GLESDebugDraw(PTM_RATIO);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	//flags += b2Draw::e_jointBit; 
	//flags += b2Draw::e_aabbBit; 
	//flags += b2Draw::e_pairBit; 
	//flags += b2Draw::e_centerOfMassBit;
	_debugDraw->SetFlags(flags);
	m_b2world->SetDebugDraw(_debugDraw);
	//��������������� 
	this->scheduleUpdate();
	return true;
}

PhysicsWorld* PhysicsWorld::create(const Size& size) {
	auto m = new (std::nothrow)PhysicsWorld();
	if (m&&m->init(size)) { m->autorelease();}
	else { CC_SAFE_DELETE(m); }
	return m;
}

void PhysicsWorld::initWorld(const Size& size) {
	//��������
	b2Vec2 gravity;
	gravity.Set(0.0f, 0.0f);
	//��������
	//---------------�ǵû���new�ڴ�
	m_b2world = new (std::nothrow) b2World(gravity);
	m_b2world->SetAllowSleeping(true);//���������Ƿ�����
	m_b2world->SetContinuousPhysics(true);//���������������
	//���Դ���B2WORLD
	CCASSERT(m_b2world,"FUCK!!!!m_b2world = nullptr!!!!!!");
	//����ȫ�ֱ���b2world
	GameManager::getInstance()->setb2World(m_b2world);
	//��ײ����
	//---------------�ǵû���new�ڴ�
	m_b2listener = new b2Listener();
	m_b2world->SetContactListener(m_b2listener);

	//�������嶨��
	b2BodyDef groundBodyDef;
	//���½�
	groundBodyDef.position.Set(0, 0);

	//������������
	b2Body* groundBody = m_b2world->CreateBody(&groundBodyDef);
	//��һ���бߵ���״
	b2EdgeShape groundBox;

	//�ײ�
	groundBox.Set(b2Vec2(0, 0), b2Vec2(size.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&groundBox, 0);

	//����
	groundBox.Set(b2Vec2(0, size.height / PTM_RATIO), b2Vec2(size.width / PTM_RATIO, size.height / PTM_RATIO));
	groundBody->CreateFixture(&groundBox, 0);

	//���
	groundBox.Set(b2Vec2(0, size.height / PTM_RATIO), b2Vec2(0, 0));
	groundBody->CreateFixture(&groundBox, 0);

	//�ұ�
	groundBox.Set(b2Vec2(size.width / PTM_RATIO, size.height / PTM_RATIO), b2Vec2(size.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&groundBox, 0);
}

//debug��ͼ����
void PhysicsWorld::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) {
	/*���Ż�*/
	glPushMatrix();
	m_b2world->DrawDebugData();
	glPopMatrix();
	CHECK_GL_ERROR_DEBUG();
	//����2D ����ͶӰ
	cocos2d::Director::getInstance()->setProjection(cocos2d::Director::Projection::_2D);
}


//�����������
void PhysicsWorld::update(float dt) {

	float timestep = 0.03f;
	int32 velocityIterations = 8;
	int32 positionIterations = 1;

	m_b2world->Step(timestep, velocityIterations, positionIterations);
	do {
		Entity * entity = nullptr;
		b2Body* b_next = nullptr;

		for (auto b = m_b2world->GetBodyList(); b; b = b_next) {
			b_next = b->GetNext();
			if (b->GetUserData()){
				entity = static_cast<Entity*>(b->GetUserData());
				//��ʵ��ӳ������Ƴ�
				if (entity->getIfPredelete()) { 
					if (entity->getEntityTpye() == EntityTpye::biology){ b_next = b_next->GetNext(); }
					entity->removeFromScene(); continue; }

				//�������������壬������һ
				if (entity->getEntityTpye() == EntityTpye::biology){
					auto biology = static_cast<Biology*>(entity);
					if (biology->getb2Body() == b)continue;
				}

				entity->setPosition(b->GetPosition().x*PTM_RATIO, b->GetPosition().y*PTM_RATIO);
				entity->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
			}
		}
	} while (0);

}