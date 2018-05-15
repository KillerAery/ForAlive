#pragma once
#ifndef Mission_h__
#define Mission_h__

#include "cocos2d.h"
#include "MissionTarget.h"

using std::string;
using std::list;

//任务状态
enum class MissionStatus{hide,running,finish};

class Mission {
	CC_SYNTHESIZE(MissionStatus, m_status, Status);						//任务状态
	CC_SYNTHESIZE(int, m_id, ID);									    //任务ID
	CC_SYNTHESIZE_PASS_BY_REF(string, m_name, Name);				  	//任务名字
	CC_SYNTHESIZE_PASS_BY_REF(string, m_description, Description);	 	 //任务描述	
	CC_SYNTHESIZE_PASS_BY_REF(list<MissionTarget>, m_targets, Targets);//任务目标s
	CC_SYNTHESIZE(list<MissionTarget>::iterator, m_currentItr, CurrentItr);//当前任务目标
public:
	Mission(int _id = -1, const string& _name = "Error", const string & _description = "Error");
	void pushMissionTarget(MissionTarget& missionTarget);				//添加任务目标
	void finishMissionTarget(int finishNum);							//完成任务目标的某个数目
	void registerCurrentTrigger();										//注册当前任务目标的触发
	void unregisterCurrentTrigger();									//注销当前任务目标的触发
	MissionTarget& getCurrentTarget();
public:
	void run();	
	void finish();
};

#endif // Mission_h__