#include "Mission.h"
#include "TriggerManager.h"
#include "Logger.h"

Mission::Mission(int _id, const string& _name, const string & _description):m_id(_id), m_name(_name), m_description(_description),m_status(MissionStatus::hide){}

//添加任务目标
void Mission::pushMissionTarget(MissionTarget & missionTarget) {
	m_targets.push_back(missionTarget);
}

//完成任务目标的某个数目
void Mission::finishMissionTarget(int finishNum) {
	//任务已完成，不必检测目标完成
	if (m_status == MissionStatus::finish)return;

	m_currentItr->setNum(finishNum);
	if (m_currentItr->ifAchieve())
	{	
		Logger::log(u8"已完成目标:" + m_currentItr->getDescription());
		unregisterCurrentTrigger(); //注销当前目标
		m_currentItr++;
		if (m_currentItr != m_targets.end())registerCurrentTrigger();  //继续注册新的目标
		else finish();//若所有目标已完成
	}

}

//注册当前任务目标的触发
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

//注销当前任务目标的触发
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
	Logger::log(u8"任务已解决:" + m_name);
	m_currentItr--;
	m_status = MissionStatus::finish;
}