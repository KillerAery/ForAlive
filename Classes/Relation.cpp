#include "Relation.h"

void Relation::judgeAttitude() {
	if (m_dispositionValue <= 50)m_disposition = Disposition::hate;
	else if (m_dispositionValue <= 95)m_disposition = Disposition::dislike;
	else if (m_dispositionValue <= 110)m_disposition = Disposition::normal;
	else if (m_dispositionValue <= 130)m_disposition = Disposition::like;
	else m_disposition = Disposition::admire;
}

Relation::Relation(int disposition , Attitude attitude) :m_dispositionValue(disposition), m_attitude(attitude) { judgeAttitude(); }

void Relation::addDisposition(int n) {
m_dispositionValue += n; 
judgeAttitude(); 
}

void Relation::reduceDisposition(int n) {
	m_dispositionValue -= n; 
	judgeAttitude(); 
}

void Relation::setDisposition(int n) {
	m_dispositionValue = n; 
	judgeAttitude(); 
}

void Relation::setAttitue(Attitude attitude) { m_attitude = attitude; }

Disposition Relation::getDisposition() { return m_disposition; }

Attitude Relation::getAttitude() { return  m_attitude; }