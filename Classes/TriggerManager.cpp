#include "TriggerManager.h"
#include "MissionManager.h"

//Erase标记 专用于Trigger的Map；
const int EraseMark = -1;

bool TriggerManager::init() {
	return true;
}
//注册击杀触发
void TriggerManager::registerKillTrigger(BiologyTpye requireTpye,int MissionID) {
	m_killTriggers.insert(std::make_pair((int)requireTpye,MissionID));
}
//注册物品获取触发
void TriggerManager::registerGetTrigger(int requireID, int MissionID) {
	m_getTriggers.insert(std::make_pair(requireID, MissionID));
}
//注册说话触发
void TriggerManager::registerTalkTrigger(int requireID, int MissionID) {
	m_talkTriggers.insert(std::make_pair(requireID, MissionID));
}
//注销击杀触发
void TriggerManager::unregisterKillTrigger(BiologyTpye requireTpye, int MissionID) {
	auto range = m_killTriggers.equal_range((int)requireTpye);
	for (auto i = range.first; i != range.second; ++i)
		if (i->first == (int)requireTpye && i->second == MissionID ) {
			i->second = EraseMark;
			return;
		}
}

//注销物品获取触发
void TriggerManager::unregisterGetTrigger(int requireID, int MissionID) {
	auto range = m_getTriggers.equal_range(requireID);
	for (auto i = range.first; i != range.second; ++i)
		if (i->first == requireID && i->second == MissionID) {
			i->second = EraseMark;
			return;
		}
}

//注销说话触发
void TriggerManager::unregisterTalkTrigger(int requireID, int MissionID) {
	auto range = m_talkTriggers.equal_range(requireID);
	for (auto i = range.first; i != range.second; ++i)
		if (i->first == requireID && i->second == MissionID) {
			i->second = EraseMark;
			return;
		}
}

//检测击杀触发
void TriggerManager::checkKillTrigger(BiologyTpye tpye){
	auto range = m_killTriggers.equal_range((int)tpye);
	for (auto i = range.first; i != range.second; ++i)
		if (i->second != EraseMark)
		MissionManager::getInstance()->finishKillTrigger(i->second,1);

}

//检测物品获取触发
void TriggerManager::checkGetTrigger(int id, int num) {
	auto range = m_getTriggers.equal_range(id);
	for (auto i = range.first; i != range.second; ++i)
		if(i->second != EraseMark)
		MissionManager::getInstance()->finishGetTrigger(i->second,num);
}

//检测说话触发
void TriggerManager::checkTalkTrigger(int id) {
	auto range = m_talkTriggers.equal_range(id);
	for (auto i = range.first; i != range.second; ++i)
		if (i->second != EraseMark)
		MissionManager::getInstance()->finishTalkTrigger(i->second, 1);
}