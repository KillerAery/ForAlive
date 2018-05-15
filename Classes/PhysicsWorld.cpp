#include "PhysicsWorld.h"
#include "GameManager.h"

PhysicsWorld::PhysicsWorld() :m_b2world(nullptr), m_b2listener(nullptr), _debugDraw(nullptr){}

PhysicsWorld::~PhysicsWorld() {
//清除GameTool.h的全局变量world
GameManager::getInstance()->setb2World(nullptr);
//b2world、m_b2listener、_debugDraw 用New创建，没有cocos2dx ref结构
CC_SAFE_DELETE(m_b2world);
CC_SAFE_DELETE(m_b2listener);
CC_SAFE_DELETE(_debugDraw);
}

bool PhysicsWorld::init(const Size& size) {
	//根据尺寸创造世界
	initWorld(size);	
	//物理引擎debug 显示					
	//---------------记得回收new内存
	_debugDraw = new GLESDebugDraw(PTM_RATIO);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	//flags += b2Draw::e_jointBit; 
	//flags += b2Draw::e_aabbBit; 
	//flags += b2Draw::e_pairBit; 
	//flags += b2Draw::e_centerOfMassBit;
	_debugDraw->SetFlags(flags);
	m_b2world->SetDebugDraw(_debugDraw);
	//开启物理世界更新 
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
	//重力参数
	b2Vec2 gravity;
	gravity.Set(0.0f, 0.0f);
	//创建世界
	//---------------记得回收new内存
	m_b2world = new (std::nothrow) b2World(gravity);
	m_b2world->SetAllowSleeping(true);//允许物体是否休眠
	m_b2world->SetContinuousPhysics(true);//开启连续物理测试
	//断言存在B2WORLD
	CCASSERT(m_b2world,"FUCK!!!!m_b2world = nullptr!!!!!!");
	//设置全局变量b2world
	GameManager::getInstance()->setb2World(m_b2world);
	//碰撞监听
	//---------------记得回收new内存
	m_b2listener = new b2Listener();
	m_b2world->SetContactListener(m_b2listener);

	//地面物体定义
	b2BodyDef groundBodyDef;
	//左下角
	groundBodyDef.position.Set(0, 0);

	//创建地面物体
	b2Body* groundBody = m_b2world->CreateBody(&groundBodyDef);
	//顶一个有边的形状
	b2EdgeShape groundBox;

	//底部
	groundBox.Set(b2Vec2(0, 0), b2Vec2(size.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&groundBox, 0);

	//顶部
	groundBox.Set(b2Vec2(0, size.height / PTM_RATIO), b2Vec2(size.width / PTM_RATIO, size.height / PTM_RATIO));
	groundBody->CreateFixture(&groundBox, 0);

	//左边
	groundBox.Set(b2Vec2(0, size.height / PTM_RATIO), b2Vec2(0, 0));
	groundBody->CreateFixture(&groundBox, 0);

	//右边
	groundBox.Set(b2Vec2(size.width / PTM_RATIO, size.height / PTM_RATIO), b2Vec2(size.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&groundBox, 0);
}

//debug绘图方法
void PhysicsWorld::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) {
	/*待优化*/
	glPushMatrix();
	m_b2world->DrawDebugData();
	glPopMatrix();
	CHECK_GL_ERROR_DEBUG();
	//设置2D 正交投影
	cocos2d::Director::getInstance()->setProjection(cocos2d::Director::Projection::_2D);
}


//物理世界更新
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
				//将实体从场景中移除
				if (entity->getIfPredelete()) { 
					if (entity->getEntityTpye() == EntityTpye::biology){ b_next = b_next->GetNext(); }
					entity->removeFromScene(); continue; }

				//生物有两个身体，跳过其一
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