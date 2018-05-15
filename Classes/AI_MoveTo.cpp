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
	//����ڸ�Ŀ�긽������Ϊ���
	if ((targetpoint - master->getPosition()).lengthSquared() < 100){
			this->finish(master);
			return;
	}
	//���� ִ�� �ƶ�
	auto direction = (targetpoint - master->getPosition()).getNormalized();
	master->setVeclocity(direction * master->getSpeed()* speedPercent);
}

void AI_MoveTo::moveTo_Astar(NPC* master, const Vec2& finnalpoint, float dt, float speedPercent){
	//��ȡѰ·��
	auto & wayCaculator = master->getWayCaculator();
	//Ŀ���
	Point targetpoint;
	//����ڸ�Ŀ�긽������Ϊ���
	if (finnalpoint.getDistanceSq(master->getPosition()) <= 100) {
			this->finish(master);
			return;
	}
	//���Ҫ��·��������
	else if (wayCaculator.ifHaveNextTargetPos())
	{	
		targetpoint = wayCaculator.getNextTargetPos();
		//�����·����ĳһ���㸽������ǰ����һ����
		if (targetpoint.getDistanceSq(master->getPosition()) <= 100){
			wayCaculator.reachNextTargetPos();
		}
	}
	else
	{
		targetpoint = finnalpoint;
	}

	//ÿN�� ������һ·��
	m_timer += dt;
	if (m_timer >= 0.3f) {
		m_timer = 0.0f;
		wayCaculator.findWay(master->getPosition(), finnalpoint);
	}
	//ִ�� �ƶ�
	auto direction = (targetpoint - master->getPosition()).getNormalized();
	master->setVeclocity(direction * master->getSpeed()* speedPercent);
}

void AI_MoveTo::finish_addtional(NPC* master){
	this->unschedule("AI_MoveTo");
	this->setState(BehaviorState::finish);
	master->setVeclocity(Vec2::ZERO);
}
