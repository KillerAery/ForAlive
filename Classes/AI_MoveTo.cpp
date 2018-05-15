#include "AI_MoveTo.h"

AI_MoveTo::AI_MoveTo():m_targetPoint(Vec2::ZERO),m_timer(0.0f), m_walkAlongTheAstarWay(false){}

void AI_MoveTo::run(NPC* master){
	if (m_state != BehaviorState::finish && m_state != BehaviorState::wait)return;

	m_lastPoint = master->getPosition();
	m_state = BehaviorState::running;

	this->schedule([master, this](float dt) {
		moveTo_Astar(master, m_targetPoint,dt);
	},"AI_MoveTo");

	AI_BehaviorNode::run(master);
}

void AI_MoveTo::moveTo(NPC* master, const Vec2& targetpoint, float speedPercent) {
	//如果在该目标附近，行为完成
	if ((targetpoint - master->getPosition()).lengthSquared() < 100){
			this->finish(master);
			return;
	}
	//否则 执行 移动
	auto direction = (targetpoint - master->getPosition()).getNormalized();
	master->setVeclocity(direction * master->getSpeed()* speedPercent);
}

void AI_MoveTo::moveTo_Astar(NPC* master, const Vec2& finnalpoint, float dt, float speedPercent){
	//获取寻路器
	auto & wayCaculator = master->getWayCaculator();
	//目标点
	Point targetpoint;
	//如果在该目标附近，行为完成
	if (finnalpoint.getDistanceSq(master->getPosition()) <= 100) {
			this->finish(master);
			return;
	}
	//如果要按路径继续走
	else if (wayCaculator.ifHaveNextTargetPos())
	{	
		targetpoint = wayCaculator.getNextTargetPos();
		//如果在路径的某一个点附近，则前往下一个点
		if (targetpoint.getDistanceSq(master->getPosition()) <= 100){
			wayCaculator.reachNextTargetPos();
		}
	}
	else
	{
		targetpoint = finnalpoint;
	}

	//每N秒 重新算一路径
	m_timer += dt;
	if (m_timer >= 0.3f) {
		m_timer = 0.0f;
		wayCaculator.findWay(master->getPosition(), finnalpoint);
	}
	//执行 移动
	auto direction = (targetpoint - master->getPosition()).getNormalized();
	master->setVeclocity(direction * master->getSpeed()* speedPercent);
}

void AI_MoveTo::finish_addtional(NPC* master){
	this->unschedule("AI_MoveTo");
	this->setState(BehaviorState::finish);
	master->setVeclocity(Vec2::ZERO);
}
