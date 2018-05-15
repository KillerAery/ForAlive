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
	//����
	void finish(NPC* master);
	//����Ľ���Ч��
	virtual void finish_addtional(NPC* master) = 0;
//private:
//	//��Ϊ�ڵ�ΪҶ�ڵ㣬����������ӽڵ�
//	//������������ӽڵ���
//	virtual void addChild(Node* node)override;

};

#endif // AI_BehaviorNode_h__
