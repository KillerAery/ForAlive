#ifndef AI_ControllNode_h__
#define AI_ControllNode_h__

#include "AI_BaseNode.h"

class AI_ControllNode : public AI_BaseNode{
public:
	AI_ControllNode();
	virtual void run(NPC* master) = 0;
};

#endif // AI_ControllNode_h__
#pragma once
