#include "PlayerPerception.h"

PlayerPerception::PlayerPerception(){}

PlayerPerception::~PlayerPerception(){
	NotificationCenter::getInstance()->removeObserver(this,"CONTAINER_REMOVE");
}

bool PlayerPerception::init() {
	if (!HumanPerception::init())return false;
	//���ܵ������Ƴ���Ϣ
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(PlayerPerception::DeleteContainerTargets), "CONTAINER_REMOVE", nullptr);

	this->scheduleCheckIfLosingContainerTargets(0.1f);

	return true;
}

PlayerPerception* PlayerPerception::create(Biology* biology) {
	PlayerPerception * pRet = new(std::nothrow)PlayerPerception();
	if (pRet && pRet->init()) { pRet->autorelease(); pRet->setMaster(biology); }
	else CC_SAFE_DELETE(pRet);
	return pRet;
}

//�������
void PlayerPerception::CheckContainer(Container* target) {
	if (target == m_master||!ifInTheRange(target, m_master, m_perceptionRangeSq))return;
	//�����������
	if (target->getEntityTpye() == EntityTpye::biology)CheckBiology(target);
	else if (target->getEntityTpye() == EntityTpye::container){
		//�ڼ�С��Χ����ʾtab����ʾ��
		if (ifInTheRange(target, m_master,2500))target->showTabKey();
		else target->hideTabKey();
	}
	//�����������
	//�������ڸø�֪Ŀ�꣬�������Ϊ��֪Ŀ��
	if (std::find(m_containerTargets.begin(), m_containerTargets.end(), target) == m_containerTargets.end())
		m_containerTargets.push_back(target);

}

//��֪����Ŀ���������ص�ɾ��
void PlayerPerception::DeleteContainerTargets(Ref * r) {
	if (r == m_master) return; 
	m_containerTargets.remove(static_cast<Container*>(r));
}
//����֪����Ŀ���Ƿ���ʧ
void PlayerPerception::CheckIfLosingContainerTargets(float dt) {
	//�������Ŀ�궪ʧ
	for (auto itr = m_containerTargets.begin(); itr != m_containerTargets.end(); ++itr)
		if (!ifInTheRange(*itr, m_master, m_perceptionMaxRangeSq)) {
			m_containerTargets.erase(itr);
			return;
		}
}

//��������
void PlayerPerception::CheckDrop(Container* arg_target) {
	auto drop = static_cast<Drop*>(arg_target);

	if (!ifInTheRange(drop, m_master, m_perceptionRangeSq)){ 
		drop->undisplayerItemName();	//˳��رյ����������
		return; }
	//�������ڸø�֪Ŀ�꣬�������Ϊ��֪Ŀ��
	if (std::find(m_dropTargets.begin(), m_dropTargets.end(), drop) == m_dropTargets.end())
	{
		m_dropTargets.push_back(drop); 
		drop->displayItemName();		//˳����ʾ�����������
	}

}