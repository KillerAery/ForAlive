#pragma once
#ifndef _PHYSICS_WORLD_H_
#define _PHYSICS_WORLD_H_
#include "cocos2d.h"
//物理引擎
#include "Box2D/Box2D.h"
//物理引擎自定义碰撞监听器
#include "b2Listener.h"
#include "GLES-Render.h"//物理引擎测试渲染

using cocos2d::Ref;
using cocos2d::Size;
using cocos2d::Node;

class PhysicsWorld : public Node{
	CC_SYNTHESIZE(b2World*, m_b2world, b2World);
	CC_SYNTHESIZE(GLESDebugDraw *, _debugDraw, DebugDraw);//记得回收内存
	b2Listener* m_b2listener;
public:
	PhysicsWorld();
	virtual ~PhysicsWorld();
	bool init(const Size& size);
	static PhysicsWorld* create(const Size& size);
	void initWorld(const Size& size);

	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)override;//提供物理引擎DEBUG显示方法
	virtual void update(float dt)override;//物理世界更新
};

#endif