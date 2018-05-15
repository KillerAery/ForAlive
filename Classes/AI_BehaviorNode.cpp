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

////行为节点为叶节点，不允许添加子节点
//void AI_BehaviorNode::addChild(Node* node){
//	CC_ASSERT("AI_BehaviorNode can't add Child"); 
//}