#pragma once
#ifndef Mission_h__
#define Mission_h__

#include "cocos2d.h"
#include "MissionTarget.h"

using std::string;
using std::list;

//����״̬
enum class MissionStatus{hide,running,finish};

class Mission {
	CC_SYNTHESIZE(MissionStatus, m_status, Status);						//����״̬
	CC_SYNTHESIZE(int, m_id, ID);									    //����ID
	CC_SYNTHESIZE_PASS_BY_REF(string, m_name, Name);				  	//��������
	CC_SYNTHESIZE_PASS_BY_REF(string, m_description, Description);	 	 //��������	
	CC_SYNTHESIZE_PASS_BY_REF(list<MissionTarget>, m_targets, Targets);//����Ŀ��s
	CC_SYNTHESIZE(list<MissionTarget>::iterator, m_currentItr, CurrentItr);//��ǰ����Ŀ��
public:
	Mission(int _id = -1, const string& _name = "Error", const string & _description = "Error");
	void pushMissionTarget(MissionTarget& missionTarget);				//�������Ŀ��
	void finishMissionTarget(int finishNum);							//�������Ŀ���ĳ����Ŀ
	void registerCurrentTrigger();										//ע�ᵱǰ����Ŀ��Ĵ���
	void unregisterCurrentTrigger();									//ע����ǰ����Ŀ��Ĵ���
	MissionTarget& getCurrentTarget();
public:
	void run();	
	void finish();
};

#endif // Mission_h__