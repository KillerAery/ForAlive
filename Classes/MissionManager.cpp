#include "MissionManager.h"
#include "Logger.h"


MissionManager::MissionManager():m_missions(10),r_missionView(nullptr){
}

bool MissionManager::init(){
	auto mission1 = Mission(0, u8"�����Ż�", u8"����˵С���ϱ������ɥʬ�ǻ���\n��������������ǣ�С����ø���ȫ");
	mission1.pushMissionTarget(MissionTarget_Kill(u8"����С���ϱߵ�����ɥʬ",12,BiologyTpye::zombie));
	registerMission(mission1);

	auto mission2 = Mission(1, u8"���ɵ�����", u8"С������һ���д�����ˣ�����˵��С\n���ұߵ�һ���ֿ��и�ҽ�ư���\n��ϣ�����ܸ���һ��ȥ�á�");
	mission2.pushMissionTarget(MissionTarget_Get(u8"��òֿ��ҽ�ư�",1,104));
	mission2.pushMissionTarget(MissionTarget_Talk(u8"�����˵��",1,30));
	registerMission(mission2);

	return true;
}

//ע������
void MissionManager::registerMission(Mission & mission) {
	m_missions[mission.getID()] = mission;
}

//�����������
void MissionManager::loadMission() {
	//TODO
}

//�����������
void MissionManager::saveMission() {
	//TODO
}

//��ʼ����
void MissionManager::runMission(int MissionID) {
	Logger::log(u8"���ѽ�����������");
	m_missions[MissionID].run();
	r_missionView->addMission(m_missions[MissionID]);
}

void MissionManager::finishKillTrigger(int missionID,int num) {
	m_missions[missionID].finishMissionTarget(m_missions[missionID].getCurrentTarget().getNum()+num);
	r_missionView->updateMission(m_missions[missionID]);
}

void MissionManager::finishGetTrigger(int missionID,int num) {
	m_missions[missionID].finishMissionTarget(num);
	r_missionView->updateMission(m_missions[missionID]);
}

void MissionManager::finishTalkTrigger(int missionID,int num) {
	m_missions[missionID].finishMissionTarget(num);
	r_missionView->updateMission(m_missions[missionID]);
}
