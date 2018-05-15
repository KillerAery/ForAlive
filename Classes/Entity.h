#pragma once
#ifndef  _ENTITY_H_
#define  _ENTITY_H_

#include "cocos2d.h"
#include "GameTool.h"

using cocos2d::Node;
using cocos2d::Sprite;
using cocos2d::Vec2;
using cocos2d::Size;
using cocos2d::ValueMap;
using cocos2d::Value;
using cocos2d::ValueVector;


//实体类型
enum class EntityTpye{
	biology = 1,
	container = 2,
	entity = 3,
	bullet = 4,
	drop = 5
};

class Entity :public Node {
protected:
	CC_SYNTHESIZE(b2Body*, m_b2body, b2Body);
	CC_SYNTHESIZE(Sprite*, m_sp, Sprite);
	CC_SYNTHESIZE(EntityTpye, m_entityTpye, EntityTpye);
	CC_SYNTHESIZE(int,m_id,ID);
	CC_SYNTHESIZE(bool, m_ifpredelete,IfPredelete);
/*-------------------基础实体属性初始化部分-------------------------*/
public:	
	Entity();
	virtual ~Entity();
	virtual bool init(ValueMap& obj_valuemap);
	virtual bool initPhysics(ValueMap& obj_valuemap);
public:
	//创造实体
	static Entity* create(ValueMap& obj_valuemap);
	//创造墙体
	static Entity* createWall(ValueVector objects);
	//从场景中移除
	virtual void removeFromScene();
public:
	//重写 设置位置方法
	virtual void setPosition(const Vec2 &point);
	virtual void setPosition(int x, int y);
};

#endif // ! _ENTITY_H_
