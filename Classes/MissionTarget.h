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
	CC_SYNTHESIZE_PASS_BY_REF(string, m_description, Description);//目标描述
	CC_SYNTHESIZE(Require, m_require, Require);		//所需交谈的人物的ID
	CC_SYNTHESIZE(int,m_requireNum,RequireNum);				//需求目标数
	CC_SYNTHESIZE(int,m_num,Num);							//达成目标数
	CC_SYNTHESIZE(MissionTargetTpye,m_missionTargetTpye, MissionTargetTpye);//任务目标类型
public:
	MissionTarget(const string& description = "Error", int requireNum = 0, Require require = Require(0), MissionTargetTpye tpye = MissionTargetTpye::Get);
	bool ifAchieve()const;//是否达成
};

//获取为目的的目标
class MissionTarget_Get : public MissionTarget {public:
	MissionTarget_Get(const string& description, int requireNum, int requireID);
};
//击杀为目的的目标
class MissionTarget_Kill : public MissionTarget {public:
	MissionTarget_Kill(const string& description, int requireNum, BiologyTpye requireBiologyTpye);
};
//说话为目的的目标
class MissionTarget_Talk : public MissionTarget {public:
	MissionTarget_Talk(const string& description, int requireNum, int requireID);
};


#endif // MissionTarget_h__