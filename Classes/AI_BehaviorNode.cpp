#include "AI_BehaviorNode.h"

AI_BehaviorNode::AI_BehaviorNode():m_state(BehaviorState::wait),m_finishFunc(nullptr){}

void AI_BehaviorNode::finish(NPC* master){
	finish_addtional(master);
	if (m_finishFunc)m_finishFunc(master);
}

void AI_BehaviorNode::run(NPC* npc) {
	for (auto node : getChildren()) {
		auto AInode = static_cast<AI_BaseNode*>(node);
		if (AInode->getCondition()(npc))
			AInode->run(npc);
	}
}

////��Ϊ�ڵ�ΪҶ�ڵ㣬����������ӽڵ�
//void AI_BehaviorNode::addChild(Node* node){
//	CC_ASSERT("AI_BehaviorNode can't add Child"); 
//}