#ifndef _AI_ROOT_NODE_H_
#define _AI_ROOT_NODE_H_

#include "AI_BaseNode.h"

class AI_RootNode : public AI_BaseNode{
	CC_SYNTHESIZE(NPC*, m_npc, NPC);
public:
	CREATE_FUNC(AI_RootNode);
	AI_RootNode();
	virtual void run(NPC* npc)override;
	virtual void update(float dt)override;
	void stopUpdate();
};

#endif
