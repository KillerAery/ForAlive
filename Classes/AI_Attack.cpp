#include "AI_Attack.h"
#include "BattleTimer.h"

AI_Attack::AI_Attack():m_timer(0.0f){
	m_condition = [](NPC* master) {
		if (!master->getPerception()->getNearest(Attitude::against))
			return false;
		return true;
	};
}

void AI_Attack::run(NPC* master){
	attack(master);
	AI_BehaviorNode::run(master);
}

//TODO待优化
//能不能直接攻击到目标
bool AI_Attack::ifDirectlyAttackTarget(NPC* master, Biology* target) {
	b2RayCastInput input;
	input.p1 = b2Vec2(master->getPosition().x/PTM_RATIO, master->getPosition().y / PTM_RATIO);
	input.p2 = b2Vec2(target->getPosition().x / PTM_RATIO, target->getPosition().y / PTM_RATIO);
	input.maxFraction = 1;

	//check every fixture of every body to find closest
	float closestFraction = 1; //start with end of line as p2
	b2Body* closestBody = nullptr;
	b2Vec2 intersectionNormal(0, 0);
	for (b2Body* b = GameManager::getInstance()->getb2World()->GetBodyList(); b; b = b->GetNext()) {
		if(b->GetUserData()==master)continue;
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {
			b2RayCastOutput output;
			if (!f->RayCast(&output, input,0))
				continue;
			if (output.fraction < closestFraction) {
				closestFraction = output.fraction;
				intersectionNormal = output.normal;
				closestBody = b;
			}
		}
	}

	if (closestBody&&closestBody->GetUserData() == target)return true;
	return false;
}

void AI_Attack::attack(NPC* master) {


	//求最近的一个目标
	auto target = master->getPerception()->getNearest(Attitude::against);
	if (!target)return;
	//如果目标是玩家，进入战斗时刻
	if (target == GameManager::getInstance()->getPlayer())BattleTimer::getInstance()->intoBattle();

	//有间断攻击
	if (master->getBiologyTpye() == BiologyTpye::human) {

		m_timer += 1.0f / 60;
		if (m_timer >= 1.3f)
			m_timer = 0.0;
		else if (m_timer >= 1.0f)
			return;

		if (!ifDirectlyAttackTarget(master,target))return;
	}

	auto shotDirection = (target->getPosition() - master->getPosition()).getNormalized();
	
	master->attack(shotDirection);

	this->finish(master);
}

void AI_Attack::finish_addtional(NPC* master) {
	m_state = BehaviorState::finish;
}