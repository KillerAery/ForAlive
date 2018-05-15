#include "AI_RootNode.h"

AI_RootNode::AI_RootNode() :m_npc(nullptr) {}

void AI_RootNode::run(NPC* npc) {
	CCASSERT(npc, "AI_RootNode receive a nullptr for npc!!");
	m_npc = npc;
	this->scheduleUpdate();
}

void AI_RootNode::update(float dt) {
	for (auto node : getChildren()) {
		auto AInode = static_cast<AI_BaseNode*>(node);
		AInode->run(m_npc);
	}
}

void AI_RootNode::stopUpdate(){
	this->unscheduleUpdate();
}