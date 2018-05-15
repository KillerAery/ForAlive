#pragma once
#ifndef MissionManager_h__
#define MissionManager_h__

#include "cocos2d.h"
#include "Singleton.h"
#include "Mission.h"
#include "MissionView.h"

using std::vector;

class MissionManager : public cocos2d::Ref, public Singleton<MissionManager>{
	CC_SYNTHESIZE_PASS_BY_REF(std::vector<Mission>, m_missions, AllMissions);
	CC_SYNTHESIZE(MissionView*,r_missionView,MissionView);
public:
	MissionManager();
	bool init();
	void registerMission(Mission & mission);//注册任务
	void loadMission();	  //载入任务情况
	void saveMission();	  //保存任务情况
public:
	void runMission(int MissionID);
public:
	void finishKillTrigger(int missionID,int num);
	void finishGetTrigger(int missionID,int num);
	void finishTalkTrigger(int missionID,int num);
};


#endif // MissionManager_h__