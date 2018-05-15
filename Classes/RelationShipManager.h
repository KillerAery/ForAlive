#pragma once
#ifndef RelationShipManager_h__
#define RelationShipManager_h__

#include "Singleton.h"
#include "BiologyRelationship.h"
#include "NPC.h"

using cocos2d::Ref;

class RelationShipManager : public Ref, public Singleton<RelationShipManager> {
public:
	bool init();
	void bindRelationshipOnNPC(Relationship & rls,Biology* npc);
	Relationship createZombieRelationship();
	Relationship createHumanRelationship();
};

#endif // RelationShipManager_h__