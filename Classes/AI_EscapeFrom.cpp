#include "AI_EscapeFrom.h"

AI_EscapeFrom::AI_EscapeFrom():m_target(){
	m_condition = [this](NPC* master) {
		if (!m_target->getBiologyTarget(master))return false;
		return true; };
}

void AI_EscapeFrom::run(NPC* master) {
	if (m_state != BehaviorState::finish && m_state != BehaviorState::wait)return;

	m_lastPoint = master->getPosition();
	m_state = BehaviorState::running;
	this->schedule([master, this](float dt) {escapeFrom(master, m_target->getBiologyTarget(master),dt); }, "AI_EscapeFrom");

	AI_BehaviorNode::run(master);
}

void AI_EscapeFrom::escapeFrom(NPC* master, Entity* targetEntity, float dt){
	if (!targetEntity) { finish(master); return; }

	auto direction = (master->getPosition() - targetEntity->getPosition()).getNormalized();
	moveTo_Astar(master, targetEntity->getPosition() + direction * 400,dt);
}

void AI_EscapeFrom::finish_addtional(NPC* master) {
	this->unschedule("AI_EscapeFrom");
	AI_MoveTo::finish_addtional(master);
}