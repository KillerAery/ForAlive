#pragma once
#ifndef AI_BehaviorNode_h__
#define AI_BehaviorNode_h__

#include <functional>
#include "AI_BaseNode.h"



enum class BehaviorState
{
	wait,running,finish,unable
};

class AI_BehaviorNode : public AI_BaseNode {
protected:
	using FinishFunc = std::function<void(Biology*)>;
	CC_SYNTHESIZE(BehaviorState, m_state, State);
	CC_SYNTHESIZE(FinishFunc,m_finishFunc,FinishFunc);
public:
	AI_BehaviorNode();
	virtual void run(NPC* master);
	//结束
	void finish(NPC* master);
	//额外的结束效果
	virtual void finish_addtional(NPC* master) = 0;
//private:
//	//行为节点为叶节点，不允许添加子节点
//	//现在允许添加子节点了
//	virtual void addChild(Node* node)override;

};

#endif // AI_BehaviorNode_h__
