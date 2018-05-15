#pragma once
#ifndef MissionTarget_h__
#define MissionTarget_h__

#include "cocos2d.h"
#include "Biology.h"

using std::string;

union Require
{
	int ID;
	BiologyTpye Tpye;
	Require(int i):ID(i){}
	Require(BiologyTpye biologyTpye):Tpye(biologyTpye){}
};

enum class MissionTargetTpye{
	Get,Kill,Talk
};

class MissionTarget{
	CC_SYNTHESIZE_PASS_BY_REF(string, m_description, Description);//Ŀ������
	CC_SYNTHESIZE(Require, m_require, Require);		//���轻̸�������ID
	CC_SYNTHESIZE(int,m_requireNum,RequireNum);				//����Ŀ����
	CC_SYNTHESIZE(int,m_num,Num);							//���Ŀ����
	CC_SYNTHESIZE(MissionTargetTpye,m_missionTargetTpye, MissionTargetTpye);//����Ŀ������
public:
	MissionTarget(const string& description = "Error", int requireNum = 0, Require require = Require(0), MissionTargetTpye tpye = MissionTargetTpye::Get);
	bool ifAchieve()const;//�Ƿ���
};

//��ȡΪĿ�ĵ�Ŀ��
class MissionTarget_Get : public MissionTarget {public:
	MissionTarget_Get(const string& description, int requireNum, int requireID);
};
//��ɱΪĿ�ĵ�Ŀ��
class MissionTarget_Kill : public MissionTarget {public:
	MissionTarget_Kill(const string& description, int requireNum, BiologyTpye requireBiologyTpye);
};
//˵��ΪĿ�ĵ�Ŀ��
class MissionTarget_Talk : public MissionTarget {public:
	MissionTarget_Talk(const string& description, int requireNum, int requireID);
};


#endif // MissionTarget_h__