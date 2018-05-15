#ifndef AI_KeepFrom_h__
#define AI_KeepFrom_h__

#include <iostream>
#include "AI_MoveTo.h"
#include "AI_Target.h"


//保持与某个实体的距离
class AI_KeepFrom : public AI_MoveTo {
	using Target = std::shared_ptr<AI_Target>;
	CC_SYNTHESIZE_PASS_BY_REF(Target, m_target, Target);
	CC_SYNTHESIZE(double, m_keepDistance,KeepDistance);
public:
	AI_KeepFrom();
	//static AI_KeepTo* create(Entity* target);
	CREATE_FUNC(AI_KeepFrom);
	virtual void run(NPC* master)override;
	void keepFrom(NPC* master, Entity* targetEntity,double keepDistance,float dt);
	virtual void finish_addtional(NPC* master)override;
};

#endif // AI_KeepTo_h__
#pragma once
