#include "AI_TalkTo.h"
#include "DialogBoxManager.h"
#include "TriggerManager.h"


AI_Talk* AI_Talk::create(bool ifAskToTalk) {
	auto talk = new(std::nothrow)AI_Talk(ifAskToTalk);
	if (talk&&talk->init()) { talk->autorelease(); }
	else CC_SAFE_DELETE(talk);
	return talk;
}

AI_Talk::AI_Talk(bool ifAskToTalk):m_ifAskToTalk(ifAskToTalk){
	m_condition = [this](NPC* master) {
		auto target = m_target->getBiologyTarget(master);
		if (target&&master->getPosition().getDistanceSq(target->getPosition()) < 3600
			&&(!m_ifAskToTalk||target->getIfRequireToTalk())
			)return true;
		return false; 
	};
}

void AI_Talk::run(NPC* master){
	if (m_state == BehaviorState::wait || m_state == BehaviorState::finish) {
		m_state = BehaviorState::running;
		talk(master, m_dialog);
		AI_BehaviorNode::run(master);
	}
}

void AI_Talk::talk(NPC* master, Dialog& dialog) {
	//触发检测
	TriggerManager::getInstance()->checkTalkTrigger(master->getID());
	DialogBoxManager::getInstance()->requestTalk(dialog);
	//如果是主动说话，才完成（主动说话只执行一次，被动说话可无数次）
	if(!m_ifAskToTalk)finish_addtional(master);
	else m_state = BehaviorState::finish;
}

void AI_Talk::finish_addtional(NPC* master){
	this->setState(BehaviorState::unable);
}