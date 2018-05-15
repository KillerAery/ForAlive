#include "findWayCaculator.h"
#include "GameManager.h"

FindWayCaculator::FindWayCaculator() :m_way(nullptr) {}

void FindWayCaculator::findWay(const Point& start,const Point& end) {
	//起点和终点要倒置
	//因为返还的是一条终点为起点的链
	auto startTilepos = MyPoint((start.x-10) / GameManager::getInstance()->getTileSize().width , (start.y) / GameManager::getInstance()->getTileSize().height);
	auto endTilepos = MyPoint((end.x-10) / GameManager::getInstance()->getTileSize().width, (end.y) / GameManager::getInstance()->getTileSize().height );
	if (startTilepos == endTilepos)return;
	m_way= findway(endTilepos,startTilepos);
}

bool FindWayCaculator::ifHaveNextTargetPos() {
	return m_way?true:false;
}

Point FindWayCaculator::getNextTargetPos() {
	Point pos = Point(m_way->x*GameManager::getInstance()->getTileSize().width+25, m_way->y*GameManager::getInstance()->getTileSize().height+20);
	return pos;
}

void FindWayCaculator::reachNextTargetPos(){
	if (m_way)
		m_way = m_way->father;
}	