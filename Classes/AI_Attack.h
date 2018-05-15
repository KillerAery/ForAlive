#ifndef _AI_ATTACK_H_
#define _AI_ATTACK_H_

#include "AI_BehaviorNode.h"

class AI_Attack : public AI_BehaviorNode{
	float m_timer;
public:
	AI_Attack();
	CREATE_FUNC(AI_Attack);
	virtual void run(NPC* master)override;
	void attack(NPC* master);
	bool ifDirectlyAttackTarget(NPC* master, Biology* target);
	virtual void finish_addtional(NPC* master)override;
};


#endif
