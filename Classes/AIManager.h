#ifndef _AI_MANAGER_
#define _AI_MANAGER_

#include "cocos2d.h"
#include "Singleton.h"

#include "AIIncludes.h"
#include "GameManager.h"


using cocos2d::Ref;

class AIManager :public Ref, public Singleton<AIManager> {
private:
	AIManager();
public:
	bool init();
	void bindAIonNPC(AI_RootNode* root, NPC* npc);
	void bindAIonNPC(AI_RootNode* root,	int id);
	AI_RootNode* createZombieAI();
	AI_RootNode* createHummanAI();
	AI_RootNode* createGetOutAI();

	void addDaugtherAIwhenAcceptMission1(AI_RootNode* root);


	friend Singleton<AIManager>;
};


#endif 
