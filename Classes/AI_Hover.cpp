#include "AI_Hover.h"
#include "GameManager.h"

AI_Hover::AI_Hover():m_runningTime(2.0f){}
void AI_Hover::run(NPC* master) {
	if (m_state != BehaviorState::finish && m_state != BehaviorState::wait)return;

	m_runningTime += 1.0f/60;
	//当徘徊时间到达一段时间  或者  到达目标地点附近   就重新改变方向
	if (m_targetPoint.getDistance(master->getPosition()) < 20 || m_runningTime > 2.0f) {
		m_targetPoint = Vec2(Vec2(rand()%300-150,rand()%300-150) + master->getPosition());
		m_runningTime = 0;
	}
	//徘徊速度 = 普通速度*0.3倍
	moveTo(master, m_targetPoint,0.3f);

	AI_BehaviorNode::run(master);
	//m_state = BehaviorState::running;
	//startHover(master);
}
//开启徘徊
void AI_Hover::startHover(NPC* master) {
	//this->schedule([master, this](float dt) {
	//	m_runningTime += dt;
	//	//当徘徊时间到达一段时间  或者  到达目标地点附近   就重新改变方向
	//	if (m_targetPoint.getDistance(master->getPosition()) < 20 || m_runningTime > 2.0f) {
	//		m_targetPoint = Vec2(rand() % 2500, rand() % 1600);
	//		m_runningTime = 0;
	//	}
	//	//徘徊速度 = 普通速度*0.3倍
	//	moveTo(master,m_targetPoint);
	//}, "AI_Hover");
}


void AI_Hover::finish_addtional(NPC* master){
	//徘徊永远不会结束
	AI_MoveTo::finish_addtional(master);
}