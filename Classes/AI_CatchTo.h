#ifndef AI_CatchTo_h__
#define AI_CatchTo_h__

#include "AI_MoveTo.h"
#include "AI_Target.h"

//追赶某一个实体
class AI_CatchTo : public AI_MoveTo {
	using Target = std::shared_ptr<AI_Target>;
	CC_SYNTHESIZE_PASS_BY_REF(Target, m_target, Target);
public:
	AI_CatchTo();
	CREATE_FUNC(AI_CatchTo);
	virtual void run(NPC* master)override;
	void catchTo(NPC* master,Entity* targetEntity, float dt);
	virtual void finish_addtional(NPC* master)override;
};

#endif // AI_CatchTo_h__
