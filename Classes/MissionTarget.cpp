#include "MissionTarget.h"

MissionTarget::MissionTarget(const string& description, int requireNum,Require require, MissionTargetTpye tpye):
	m_description(description), m_requireNum(requireNum), m_num(0),m_require(require),m_missionTargetTpye(tpye){}

//�Ƿ���
bool MissionTarget::ifAchieve() const{
	return m_num >= m_requireNum;
}

//��ȡΪĿ�ĵ�Ŀ��
MissionTarget_Get::MissionTarget_Get(const string& description, int requireNum, int requireID) :
	MissionTarget(description, requireNum, Require(requireID), MissionTargetTpye::Get){
}
//��ɱΪĿ�ĵ�Ŀ��
MissionTarget_Kill::MissionTarget_Kill(const string& description, int requireNum, BiologyTpye requireBiologyTpye) :
	MissionTarget(description, requireNum, Require(requireBiologyTpye),MissionTargetTpye::Kill){

}
//˵��ΪĿ�ĵ�Ŀ��
MissionTarget_Talk::MissionTarget_Talk(const string& description, int requireNum, int requireID) :
	MissionTarget(description, requireNum, Require(requireID), MissionTargetTpye::Talk){
}