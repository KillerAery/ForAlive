#include "AI_KeepFrom.h"

AI_KeepFrom::AI_KeepFrom():m_keepDistance(200),m_target(AI_Target::create(-1)){
	m_condition = [this](NPC* master) {
		if (!m_target->getBiologyTarget(master))return false;
		return true; };
}

void AI_KeepFrom::run(NPC* master){
	if (m_state != BehaviorState::finish && m_state != BehaviorState::wait)return;

	if (!m_target->getBiologyTarget(master))return;

	m_lastPoint = master->getPosition();
	m_state = BehaviorState::running;
	this->schedule([master, this](float dt) {keepFrom(master,m_target->getBiologyTarget(master),m_keepDistance,dt);AI_BehaviorNode::run(master); }, "AI_KeepFrom");


}

void AI_KeepFrom::keepFrom(NPC* master, Entity* targetEntity, double keepDistance, float dt){
	if (!targetEntity){ finish(master); return;}

	auto direction = (master->getPosition() - targetEntity->getPosition()).getNormalized();
	moveTo_Astar(master,targetEntity->getPosition() + direction * keepDistance,0.6f);

}

void AI_KeepFrom::finish_addtional(NPC* master) {
	this->unschedule("AI_KeepFrom");
	AI_MoveTo::finish_addtional(master);
}