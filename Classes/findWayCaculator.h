#pragma once
#ifndef findWayCaculator_h__
#define findWayCaculator_h__

#include "cocos2d.h"
#include "AstarCaculator.h"

using cocos2d::Point;

class FindWayCaculator : protected AstarCaculator{
	OpenPoint* m_way;
public:
	FindWayCaculator();
	void findWay(const Point& start, const Point& end);
	bool ifHaveNextTargetPos();
	Point getNextTargetPos();
	void reachNextTargetPos();
};


#endif // findWayCaculator_h__