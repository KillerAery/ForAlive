#include "MissionManager.h"
#include "Logger.h"


MissionManager::MissionManager():m_missions(10),r_missionView(nullptr){
}

bool MissionManager::init(){
	auto mission1 = Mission(0, u8"清理门户", u8"你听说小镇南边有许多丧尸徘徊，\n如果你能消灭它们，小镇会变得更安全");
	mission1.pushMissionTarget(MissionTarget_Kill(u8"消灭小镇南边的若干丧尸",12,BiologyTpye::zombie));
	registerMission(mission1);

	auto mission2 = Mission(1, u8"可疑的请求", u8"小镇里有一个叫戴夫的人，跟我说，小\n镇右边的一个仓库有个医疗包，\n他希望我能跟他一起去拿。");
	mission2.pushMissionTarget(MissionTarget_Get(u8"获得仓库的医疗包",1,104));
	mission2.pushMissionTarget(MissionTarget_Talk(u8"与戴夫说话",1,30));
	registerMission(mission2);

	return true;
}

//注册任务
void MissionManager::registerMission(Mission & mission) {
	m_missions[mission.getID()] = mission;
}

//载入任务情况
void MissionManager::loadMission() {
	//TODO
}

//保存任务情况
void MissionManager::saveMission() {
	//TODO
}

//开始任务
void MissionManager::runMission(int MissionID) {
	Logger::log(u8"你已接受了新任务");
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
