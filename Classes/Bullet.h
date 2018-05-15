#pragma once
#ifndef Bullet_h__
#define Bullet_h__

#include "Entity.h"

using cocos2d::MotionStreak;

enum class BulletTpye {
	default,arrow
};

class Biology;

class Bullet : public Entity{
	CC_SYNTHESIZE(Biology*, m_user, User);
	CC_SYNTHESIZE(MotionStreak*, m_motionStreak, motionStreak);
	CC_SYNTHESIZE(double,m_damage,Damage);
public:
	Bullet();
	virtual ~Bullet();
	virtual bool init(Biology* user,const Vec2& position,double damage,int groundeindex, BulletTpye bulletTpye);
	virtual bool initPhysics(ValueMap& obj_valuemap)override;
	static Bullet* create(Biology* user,const Vec2& position, const Vec2& direction,double damage,int groundeindex,BulletTpye bulletTpye = BulletTpye::default);
	//从场景中移除
	virtual void removeFromScene();
public:
	//重写 设置位置方法
	virtual void setPosition(const Vec2 & point);
	virtual void setPosition(int x, int y);
};

#endif // Bullet_h__