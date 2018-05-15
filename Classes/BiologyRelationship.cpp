#include "BiologyRelationship.h"
#include "Biology.h"

BiologyRelationship::BiologyRelationship()
{
}

Attitude BiologyRelationship::getAttitude(Biology* somebody) {
	//在个人关系网查找
	auto itr = m_individualRelationship.find(somebody->getID());
	if (itr != m_individualRelationship.end())return itr->second.getAttitude();
	//若个人关系网里找不了
	//在种群关系网查找
	auto itr2 = m_raceRelationship.find(somebody->getBiologyTpye());
	if (itr2 != m_raceRelationship.end())return itr2->second.getAttitude();
	//若种群关系网里找不了,返还中立态度
	return Attitude::neutral;
}

Disposition BiologyRelationship::getDispositon(Biology* somebody) {
	//在个人关系网查找
	auto itr = m_individualRelationship.find(somebody->getID());
	if (itr != m_individualRelationship.end())return itr->second.getDisposition();
	//若个人关系网里找不了
	//在种群关系网查找
	auto itr2 = m_raceRelationship.find(somebody->getBiologyTpye());
	if (itr2 != m_raceRelationship.end())return itr2->second.getDisposition();
	//若种群关系网里找不了,返还普通好感度
	return Disposition::normal;
}

void BiologyRelationship::addRaceRelationship(BiologyTpye tpye, Relation& relation) {
	m_raceRelationship.insert(std::make_pair(tpye, relation));
}
void BiologyRelationship::addIndividualRelationship(Biology* individual, Relation& relation) {
	addIndividualRelationship(individual->getID(), relation);
}
void BiologyRelationship::addIndividualRelationship(int id, Relation& relation) {
	m_individualRelationship.insert(std::make_pair(id, relation));
}

Relation& BiologyRelationship::getRelationship(BiologyTpye tpye) { return m_raceRelationship[tpye]; }
Relation& BiologyRelationship::getRelationship(Biology* individual) { return getRelationship(individual->getID()); }
Relation& BiologyRelationship::getRelationship(int id) { return m_individualRelationship[id]; }