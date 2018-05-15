#include "AI_Speak.h"

AI_Speak::AI_Speak():m_words("ERROR::no words"){}
AI_Speak* AI_Speak::create(const string& speakwords) {
	auto aispeak = new (std::nothrow) AI_Speak();
	if (aispeak&&aispeak->init(speakwords)) { aispeak->autorelease(); }
	else CC_SAFE_DELETE(aispeak);
	return aispeak;
}

bool AI_Speak::init(const string& speakwords) {
	if (!AI_BehaviorNode::init())return false;
	
	m_words = speakwords;

	return true;
}

void AI_Speak::run(NPC* master){
	if (m_state != BehaviorState::finish&&m_state != BehaviorState::wait)return;

	//��ʾ˵������label
	this->speak(master);
	

	//һ��ʱ������
	this->schedule([master,this](float dt) {
			this->finish(master);
	}, m_words.size()*0.2f,0,0,string("beh_speak"));//�����ַ����� ���� ��ʾʱ��

	m_state = BehaviorState::running;

	AI_BehaviorNode::run(master);
}

void AI_Speak::speak(NPC* master){
	master->speakWords(m_words);
}

void AI_Speak::finish_addtional(NPC* master){
	m_state = BehaviorState::finish;
}
