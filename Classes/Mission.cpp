#include "Mission.h"
#include "TriggerManager.h"
#include "Logger.h"

Mission::Mission(int _id, const string& _name, const string & _description):m_id(_id), m_name(_name), m_description(_description),m_status(MissionStatus::hide){}

//�������Ŀ��
void Mission::pushMissionTarget(MissionTarget & missionTarget) {
	m_targets.push_back(missionTarget);
}

//�������Ŀ���ĳ����Ŀ
void Mission::finishMissionTarget(int finishNum) {
	//��������ɣ����ؼ��Ŀ�����
	if (m_status == MissionStatus::finish)return;

	m_currentItr->setNum(finishNum);
	if (m_currentItr->ifAchieve())
	{	
		Logger::log(u8"�����Ŀ��:" + m_currentItr->getDescription());
		unregisterCurrentTrigger(); //ע����ǰĿ��
		m_currentItr++;
		if (m_currentItr != m_targets.end())registerCurrentTrigger();  //����ע���µ�Ŀ��
		else finish();//������Ŀ�������
	}

}

//ע�ᵱǰ����Ŀ��Ĵ���
void Mission::registerCurrentTrigger(){
	switch (m_currentItr->getMissionTargetTpye())
	{
	case MissionTargetTpye::Get:
		TriggerManager::getInstance()->registerGetTrigger(m_currentItr->getRequire().ID ,m_id);
		break;
	case MissionTargetTpye::Kill:
		TriggerManager::getInstance()->registerKillTrigger(m_currentItr->getRequire().Tpye ,m_id);
		break;
	case MissionTargetTpye::Talk:
		TriggerManager::getInstance()->registerTalkTrigger(m_currentItr->getRequire().ID ,m_id);
		break;
	}
}

//ע����ǰ����Ŀ��Ĵ���
void Mission::unregisterCurrentTrigger() {
	switch (m_currentItr->getMissionTargetTpye())
	{
	case MissionTargetTpye::Get:
		TriggerManager::getInstance()->unregisterGetTrigger(m_currentItr->getRequire().ID, m_id);
		break;
	case MissionTargetTpye::Kill:
		TriggerManager::getInstance()->unregisterKillTrigger(m_currentItr->getRequire().Tpye, m_id);
		break;
	case MissionTargetTpye::Talk:
		TriggerManager::getInstance()->unregisterTalkTrigger(m_currentItr->getRequire().ID, m_id);
		break;
	}
}

MissionTarget& Mission::getCurrentTarget() {
	return *m_currentItr;
}

void Mission::run() {
	m_status = MissionStatus::running;
	m_currentItr = m_targets.begin();
	registerCurrentTrigger();
}

void Mission::finish() {
	Logger::log(u8"�����ѽ��:" + m_name);
	m_currentItr--;
	m_status = MissionStatus::finish;
}