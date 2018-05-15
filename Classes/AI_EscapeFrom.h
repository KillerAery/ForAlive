#ifndef AI_EscapeFrom_h__
#define AI_EscapeFrom_h__

#include <iostream>
#include "AI_MoveTo.h"
#include "AI_Target.h"


//保持与某个实体的距离
class AI_EscapeFrom : public AI_MoveTo {
	using Target = std::shared_ptr<AI_Target>;
	CC_SYNTHESIZE_PASS_BY_REF(Target, m_target, Target);
public:
	AI_EscapeFrom();
	CREATE_FUNC(AI_EscapeFrom);
	virtual void run(NPC* master)override;
	void escapeFrom(NPC* master, Entity* targetEntity, float dt);
	virtual void finish_addtional(NPC* master)override;
};

#endif // AI_EscapeFrom_h__
#pragma once
