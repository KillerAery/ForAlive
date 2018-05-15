#ifndef AI_Speak_h__
#define AI_Speak_h__

#include "AI_BehaviorNode.h"

using cocos2d::Label;
using std::string;

class AI_Speak : public AI_BehaviorNode{
	CC_SYNTHESIZE_PASS_BY_REF(string,m_words,Words);
public:
	AI_Speak();
	bool init(const string& speakwords);
	static AI_Speak* create(const string& speakwords);
	virtual void run(NPC* master)override;
	void speak(NPC* master);
	virtual void finish_addtional(NPC* master)override;

};

#endif // AI_Speak_h__
#pragma once
