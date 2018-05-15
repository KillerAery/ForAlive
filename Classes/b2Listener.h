#pragma once
#ifndef _B2LISTENER_H_
#define _B2LISTENER_H_
//物理引擎
#include "Box2D/Box2D.h"

//BOX2D 的 碰撞监听器
class b2Listener : public b2ContactListener
{
public:
	//开始接触  

	virtual void BeginContact(b2Contact *contact)override;

	//结束接触  

	virtual void EndContact(b2Contact *contact)override;

	//求解之前的  

	virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold)override;

	//求解之后的  

	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)override;
};




#endif