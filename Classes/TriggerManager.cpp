#include "TriggerManager.h"
#include "MissionManager.h"

//Erase��� ר����Trigger��Map��
const int EraseMark = -1;

bool TriggerManager::init() {
	return true;
}
//ע���ɱ����
void TriggerManager::registerKillTrigger(BiologyTpye requireTpye,int MissionID) {
	m_killTriggers.insert(std::make_pair((int)requireTpye,MissionID));
}
//ע����Ʒ��ȡ����
void TriggerManager::registerGetTrigger(int requireID, int MissionID) {
	m_getTriggers.insert(std::make_pair(requireID, MissionID));
}
//ע��˵������
void TriggerManager::registerTalkTrigger(int requireID, int MissionID) {
	m_talkTriggers.insert(std::make_pair(requireID, MissionID));
}
//ע����ɱ����
void TriggerManager::unregisterKillTrigger(BiologyTpye requireTpye, int MissionID) {
	auto range = m_killTriggers.equal_range((int)requireTpye);
	for (auto i = range.first; i != range.second; ++i)
		if (i->first == (int)requireTpye && i->second == MissionID ) {
			i->second = EraseMark;
			return;
		}
}

//ע����Ʒ��ȡ����
void TriggerManager::unregisterGetTrigger(int requireID, int MissionID) {
	auto range = m_getTriggers.equal_range(requireID);
	for (auto i = range.first; i != range.second; ++i)
		if (i->first == requireID && i->second == MissionID) {
			i->second = EraseMark;
			return;
		}
}

//ע��˵������
void TriggerManager::unregisterTalkTrigger(int requireID, int MissionID) {
	auto range = m_talkTriggers.equal_range(requireID);
	for (auto i = range.first; i != range.second; ++i)
		if (i->first == requireID && i->second == MissionID) {
			i->second = EraseMark;
			return;
		}
}

//����ɱ����
void TriggerManager::checkKillTrigger(BiologyTpye tpye){
	auto range = m_killTriggers.equal_range((int)tpye);
	for (auto i = range.first; i != range.second; ++i)
		if (i->second != EraseMark)
		MissionManager::getInstance()->finishKillTrigger(i->second,1);

}

//�����Ʒ��ȡ����
void TriggerManager::checkGetTrigger(int id, int num) {
	auto range = m_getTriggers.equal_range(id);
	for (auto i = range.first; i != range.second; ++i)
		if(i->second != EraseMark)
		MissionManager::getInstance()->finishGetTrigger(i->second,num);
}

//���˵������
void TriggerManager::checkTalkTrigger(int id) {
	auto range = m_talkTriggers.equal_range(id);
	for (auto i = range.first; i != range.second; ++i)
		if (i->second != EraseMark)
		MissionManager::getInstance()->finishTalkTrigger(i->second, 1);
}