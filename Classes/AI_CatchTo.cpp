#include "AI_CatchTo.h"


AI_CatchTo::AI_CatchTo():m_target(nullptr){
	m_condition = [this](NPC* master) {
		if (!m_target->getBiologyTarget(master))return false;
		return true; };
}

void AI_CatchTo::run(NPC* master) {
	if (m_state != BehaviorState::finish && m_state != BehaviorState::wait)return;

	if (!m_target->getBiologyTarget(master))return;

	m_lastPoint = master->getPosition();
	m_state = BehaviorState::running;
	this->schedule([master,this](float dt) {catchTo(master, m_target->getBiologyTarget(master),dt); }, "AI_CatchTo");

	AI_BehaviorNode::run(master);
}

void AI_CatchTo::catchTo(NPC* master,Entity* target, float dt){
	if (!target) {finish(master); return;}

	moveTo_Astar(master, target->getPosition(),dt);
}

void AI_CatchTo::finish_addtional(NPC* master){
	this->unschedule("AI_CatchTo");
	AI_MoveTo::finish_addtional(master);
}
