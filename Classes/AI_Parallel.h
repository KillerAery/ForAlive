#pragma once
#ifndef AI_Parallel_h__
#define AI_Parallel_h__

#include "AI_ControllNode.h"

class AI_Parallel : public AI_ControllNode {
public:
	AI_Parallel();
	virtual void run(NPC* npc)override;
	CREATE_FUNC(AI_Parallel);

};

#endif // AI_Parallel_h__