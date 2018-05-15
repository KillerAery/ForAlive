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


//ʵ������
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
/*-------------------����ʵ�����Գ�ʼ������-------------------------*/
public:	
	Entity();
	virtual ~Entity();
	virtual bool init(ValueMap& obj_valuemap);
	virtual bool initPhysics(ValueMap& obj_valuemap);
public:
	//����ʵ��
	static Entity* create(ValueMap& obj_valuemap);
	//����ǽ��
	static Entity* createWall(ValueVector objects);
	//�ӳ������Ƴ�
	virtual void removeFromScene();
public:
	//��д ����λ�÷���
	virtual void setPosition(const Vec2 &point);
	virtual void setPosition(int x, int y);
};

#endif // ! _ENTITY_H_
