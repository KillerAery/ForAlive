#include "Bullet.h"

using cocos2d::Color3B;

Bullet::Bullet():m_motionStreak(MotionStreak::create(0.05f,1,3, Color3B::YELLOW,"Entities/bullet.png")),m_damage(0),m_user(nullptr){}
Bullet::~Bullet() {}



bool Bullet::init(Biology* user,const Vec2& position, double damage, int groundeindex , BulletTpye bulletTpye) {
	auto map = ValueMap();
	map.insert(ValueMap::value_type("sprite", Value("Entities/bullet.png")));
	map.insert(ValueMap::value_type("entitytpye", Value((int)EntityTpye::bullet)));
	map.insert(ValueMap::value_type("x", Value(position.x)));
	map.insert(ValueMap::value_type("y", Value(position.y)));
	map.insert(ValueMap::value_type("groupindex", Value(groundeindex)));
	map.insert(ValueMap::value_type("physicstpye", Value(2)));
	map.insert(ValueMap::value_type("maskbit", Value(0x01)));
	map.insert(ValueMap::value_type("categorybits", Value(0x0f)));
	if (!Entity::init(map))return false;
	m_damage = damage;
	m_user = user;
	//this->scheduleOnce([this](float dt) {this->setIfPredelete(true);}, 0.1f, "Bullet");

	return true;
}

bool Bullet::initPhysics(ValueMap& obj_valuemap) {
	if (!Entity::initPhysics(obj_valuemap))return false;

	m_b2body->SetBullet(true);
	m_b2body->GetFixtureList()->SetDensity(5.0f);//子弹密度比一般小，造成击退力相应减少
	return true;
}

Bullet* Bullet::create(Biology* user,const Vec2& position,const Vec2& direction, double damage, int groundeindex , BulletTpye bulletTpye) {
	auto bullet = new (std::nothrow)Bullet();
	if (bullet&&bullet->init(user,position,damage,groundeindex,bulletTpye)) {
		bullet->autorelease(); 
		//射击力度
		auto ShotDir = b2Vec2(direction.x * 2000 / PTM_RATIO, direction.y * 2000 / PTM_RATIO);
		bullet->getb2Body()->SetLinearVelocity(ShotDir);
		//拖尾效果
		bullet->getmotionStreak()->setPosition(bullet->getPosition());
	}
	else { CC_SAFE_DELETE(bullet); }
	return bullet;
}

//从场景中移除
void Bullet::removeFromScene() {
	m_motionStreak->removeFromParent();
	Entity::removeFromScene();
}
//重写 设置位置方法
void Bullet::setPosition(const Vec2 &point){
	m_motionStreak->setPosition(getPosition());
	Entity::setPosition(point);
}
void Bullet::setPosition(int x, int y) {
	m_motionStreak->setPosition(getPositionX(),getPositionY());
	Entity::setPosition(x, y);
}