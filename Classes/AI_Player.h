#pragma once
#ifndef AI_Player_h__
#define AI_Player_h__

#include "AI_Target.h"
#include "GameManager.h"

class AI_Player :public AI_Target {
public:

	static Target create() { return Target(new AI_Player); }

	virtual Biology* getBiologyTarget(NPC* master)override {
		Biology* player = GameManager::getInstance()->getPlayer();
		return player;
	}
};

#endif // AI_Player_h__