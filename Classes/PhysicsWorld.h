#pragma once
#ifndef _PHYSICS_WORLD_H_
#define _PHYSICS_WORLD_H_
#include "cocos2d.h"
//��������
#include "Box2D/Box2D.h"
//���������Զ�����ײ������
#include "b2Listener.h"
#include "GLES-Render.h"//�������������Ⱦ

using cocos2d::Ref;
using cocos2d::Size;
using cocos2d::Node;

class PhysicsWorld : public Node{
	CC_SYNTHESIZE(b2World*, m_b2world, b2World);
	CC_SYNTHESIZE(GLESDebugDraw *, _debugDraw, DebugDraw);//�ǵû����ڴ�
	b2Listener* m_b2listener;
public:
	PhysicsWorld();
	virtual ~PhysicsWorld();
	bool init(const Size& size);
	static PhysicsWorld* create(const Size& size);
	void initWorld(const Size& size);

	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)override;//�ṩ��������DEBUG��ʾ����
	virtual void update(float dt)override;//�����������
};

#endif