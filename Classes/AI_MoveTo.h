#ifndef AI_MoveTo_h__
#define AI_MoveTo_h__

#include "AI_BehaviorNode.h"
using cocos2d::Vec2;

//移动到某一个点
class AI_MoveTo : public AI_BehaviorNode{
	CC_SYNTHESIZE_PASS_BY_REF(Vec2,m_targetPoint,TargetPoint);
	CC_SYNTHESIZE_PASS_BY_REF(Vec2, m_lastPoint, LastPoint);
	float m_timer;
	bool m_walkAlongTheAstarWay;
public:
	AI_MoveTo();
	virtual void run(NPC* master)override;
	void moveTo(NPC* master,const Vec2& targetpoint,float speedPercent = 1.0f);
	void moveTo_Astar(NPC* master, const Vec2& targetpoint, float dt, float speedPercent = 1.0f);
	virtual void finish_addtional(NPC* master)override;
};

#endif // AI_MoveTo_h__
#pragma once
