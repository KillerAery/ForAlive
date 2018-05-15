#ifndef AI_TalkTo_h__
#define AI_TalkTo_h__

#include "AI_BehaviorNode.h"
#include "AI_Target.h"
#include "Dialog.h"


class AI_Talk : public AI_BehaviorNode{
	using Target = std::shared_ptr<AI_Target>;
	CC_SYNTHESIZE_PASS_BY_REF(Target, m_target, Target);
	CC_SYNTHESIZE_PASS_BY_REF(Dialog, m_dialog, Dialog);
	CC_SYNTHESIZE(bool,m_ifAskToTalk,IfAskToTalk);
public:
	AI_Talk(bool ifAskToTalk);
	static AI_Talk* create(bool ifAskToTalk = false);
	virtual void run(NPC* master)override;
	void talk(NPC* master,Dialog& dialog);
	virtual void finish_addtional(NPC* master)override;
};


#endif // AI_TalkTo_h__
#pragma once