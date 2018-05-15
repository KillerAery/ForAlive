#pragma once
#ifndef AI_Target_h__
#define AI_Target_h__

#include "NPC.h"
#include "GameManager.h"

class AI_Target {
	CC_SYNTHESIZE(int, m_entityTargetID, EntityTargetID);

	AI_Target() : m_entityTargetID(-1){};	//-1为不存在的实体ID
public:
	using Target = std::shared_ptr<AI_Target>;
public:
	AI_Target(int id) :m_entityTargetID(id){};

	static Target create(int id){
		return Target(new AI_Target(id));}

	void setTargetID(int id) {
		m_entityTargetID = id;
	}
	virtual Entity*getEntityTarget() {
		return GameManager::getInstance()->findContainer(m_entityTargetID);
	}

	virtual Biology* getBiologyTarget(NPC* master){
		return GameManager::getInstance()->findBiology(m_entityTargetID);
	}

};

#endif // AI_Target_h__