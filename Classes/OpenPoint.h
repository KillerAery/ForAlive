#ifndef OpenPoint_h__
#define OpenPoint_h__

#include <iostream>
#include <algorithm>
#include "MyPoint.h"

/* openpoint */
struct OpenPoint :public MyPoint{
	int cost;                 // 耗费值
	int pred;                 // 预测值
	OpenPoint* father;        // 父节点
	OpenPoint(const MyPoint & p,const MyPoint& end, int c, OpenPoint *fatherp):MyPoint(p), cost(c), father(fatherp){
		//相对位移x,y取绝对值
		int relativex = std::abs(end.x - p.x);
		int relativey = std::abs(end.y - p.y);
		//x,y偏移值n
		int n = relativex - relativey;
		pred = std::max(relativex, relativey) * 14 - std::abs(n) * 4 + c;
		// (max–n)*14+n*10+c
	}

	//openpoint 比较函数
	bool operator < (const OpenPoint &op)const { return pred < op.pred; }
	bool operator > (const OpenPoint &op)const { return pred > op.pred; }

};


#endif // OpenPoint_h__