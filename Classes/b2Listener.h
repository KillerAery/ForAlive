#pragma once
#ifndef _B2LISTENER_H_
#define _B2LISTENER_H_
//��������
#include "Box2D/Box2D.h"

//BOX2D �� ��ײ������
class b2Listener : public b2ContactListener
{
public:
	//��ʼ�Ӵ�  

	virtual void BeginContact(b2Contact *contact)override;

	//�����Ӵ�  

	virtual void EndContact(b2Contact *contact)override;

	//���֮ǰ��  

	virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold)override;

	//���֮���  

	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)override;
};




#endif