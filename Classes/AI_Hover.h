#pragma once
#ifndef AI_Hover_h__
#define AI_Hover_h__
#include "AI_MoveTo.h"

class AI_Hover : public AI_MoveTo {
	CC_SYNTHESIZE_PASS_BY_REF(Vec2, m_targetPoint, TargetPoint);
	CC_SYNTHESIZE(double, m_runningTime,RunningTime);
public:
	AI_Hover();
	CREATE_FUNC(AI_Hover);
	virtual void run(NPC* master)override;
	void startHover(NPC* master);	//¿ªÆôÅÇ»²
	virtual void finish_addtional(NPC* master)override;
};



#endif // AI_Hover_h__