#pragma once
#ifndef BattleTimer_h__
#define BattleTimer_h__

#include "cocos2d.h"
#include "Singleton.h"
#include "GameTool.h"
#include "GameManager.h"

using cocos2d::Node;

class BattleTimer : public Node,public Singleton<BattleTimer>{
	bool m_inBattle;
	float m_time;
public:
	BattleTimer():m_time(0.0f),m_inBattle(false){}

	virtual bool init() {
		if (!Node::init())return false;
		Node::onEnter();
		Node::onEnterTransitionDidFinish();
		return true;
	}

	void intoBattle(){
		m_time = 0.0f;
		if (!m_inBattle)
		{
			GameTool::getInstance()->fadePlayBGMandCloseOtherBGM("Music/Inon Zur - Unwelcome Guest.mp3",0.5f);
			m_inBattle = true;
			this->schedule(
				[this](float dt) {
				m_time += 1.0f / 60;
				if (m_time >= 5.0f) {
					m_time = 0.0f;
					m_inBattle = false;
					GameTool::getInstance()->fadePlayBGMandCloseOtherBGM("Music/Jeremy Soule - Tundra.mp3");
					this->unschedule("battletime");
				}
			}, "battletime");
		}
	}
};

#endif // BattleTimer_h__