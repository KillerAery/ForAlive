#include "AI_Hover.h"
#include "GameManager.h"

AI_Hover::AI_Hover():m_runningTime(2.0f){}
void AI_Hover::run(NPC* master) {
	if (m_state != BehaviorState::finish && m_state != BehaviorState::wait)return;

	m_runningTime += 1.0f/60;
	//���ǻ�ʱ�䵽��һ��ʱ��  ����  ����Ŀ��ص㸽��   �����¸ı䷽��
	if (m_targetPoint.getDistance(master->getPosition()) < 20 || m_runningTime > 2.0f) {
		m_targetPoint = Vec2(Vec2(rand()%300-150,rand()%300-150) + master->getPosition());
		m_runningTime = 0;
	}
	//�ǻ��ٶ� = ��ͨ�ٶ�*0.3��
	moveTo(master, m_targetPoint,0.3f);

	AI_BehaviorNode::run(master);
	//m_state = BehaviorState::running;
	//startHover(master);
}
//�����ǻ�
void AI_Hover::startHover(NPC* master) {
	//this->schedule([master, this](float dt) {
	//	m_runningTime += dt;
	//	//���ǻ�ʱ�䵽��һ��ʱ��  ����  ����Ŀ��ص㸽��   �����¸ı䷽��
	//	if (m_targetPoint.getDistance(master->getPosition()) < 20 || m_runningTime > 2.0f) {
	//		m_targetPoint = Vec2(rand() % 2500, rand() % 1600);
	//		m_runningTime = 0;
	//	}
	//	//�ǻ��ٶ� = ��ͨ�ٶ�*0.3��
	//	moveTo(master,m_targetPoint);
	//}, "AI_Hover");
}


void AI_Hover::finish_addtional(NPC* master){
	//�ǻ���Զ�������
	AI_MoveTo::finish_addtional(master);
}