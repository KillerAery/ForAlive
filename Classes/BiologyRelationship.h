#pragma once
#ifndef BiologyRelation_h__
#define BiologyRelation_h__

#include "cocos2d.h"
#include "Relation.h"

class Biology;
enum class BiologyTpye;

class BiologyRelationship;

using Relationship = std::shared_ptr<BiologyRelationship>;

class BiologyRelationship
{
protected:
	using RaceRelationship = std::map<BiologyTpye, Relation>;
	using IndividualRelationship = std::map<int, Relation>;
	CC_SYNTHESIZE_PASS_BY_REF(RaceRelationship,m_raceRelationship,RaceRelationship);
	CC_SYNTHESIZE_PASS_BY_REF(IndividualRelationship, m_individualRelationship, IndividualRelationship);
public:
	BiologyRelationship();
	static Relationship create() {return Relationship(new BiologyRelationship());}
	Attitude getAttitude(Biology* somebody);
	Disposition getDispositon(Biology* somebody);

	void addRaceRelationship(BiologyTpye tpye,Relation& relation);
	void addIndividualRelationship(Biology* individual, Relation& relation);
	void addIndividualRelationship(int id, Relation& relation);

	Relation& getRelationship(BiologyTpye tpye);
	Relation& getRelationship(Biology* individual);
	Relation& getRelationship(int id);
};

#endif // BiologyRelation_h__