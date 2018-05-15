#include "RelationShipManager.h"

bool RelationShipManager::init() {
	return true;
}

void RelationShipManager::bindRelationshipOnNPC(Relationship& rls,Biology* npc) {
	CCASSERT(!npc->getRelationship(), "NPC already have relationship!!");
	npc->setRelationship(rls);
}

//��ʬ̬��
Relationship RelationShipManager::createZombieRelationship(){
	auto & relationship = BiologyRelationship::create();
	relationship->addRaceRelationship(BiologyTpye::zombie,Relation(100,Attitude::ally));
	relationship->addRaceRelationship(BiologyTpye::human, Relation(100, Attitude::against));
	relationship->addRaceRelationship(BiologyTpye::player, Relation(100, Attitude::against));
	return relationship;
}

//����̬��
Relationship RelationShipManager::createHumanRelationship() {
	auto & relationship = BiologyRelationship::create();
	relationship->addRaceRelationship(BiologyTpye::zombie, Relation(100, Attitude::against));
	relationship->addRaceRelationship(BiologyTpye::player, Relation(100, Attitude::neutral));
	relationship->addRaceRelationship(BiologyTpye::human, Relation(100, Attitude::neutral));
	return relationship;
}