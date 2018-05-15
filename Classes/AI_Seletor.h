#pragma once
#ifndef AI_Seletor_h__
#define AI_Seletor_h__

#include "AI_ControllNode.h"

class AI_Seletor : public AI_ControllNode{
public:
	AI_Seletor();
	virtual void run(NPC* npc)override;
	CREATE_FUNC(AI_Seletor);
};

#endif // AI_Seletor_h__