#pragma once
#ifndef AstarCaculator_h__
#define AstarCaculator_h__

#include "OpenPoint.h"
#include "BinaryHeap.h"

class AstarCaculator {
	BinaryHeap<OpenPoint> openlist;
	bool mark[50][100];
	int m_count;
public:
	AstarCaculator();
	//获取障碍标记，清除关闭点
	void copyBarrierMark();
	// 清理容器 
	void cleanlist();
	//检查函数 返还成功与否值
	bool checkInBarrierAndCloseList(const MyPoint & p1);
	// 开启检查，检查父节点 
	void open(OpenPoint* openp,const MyPoint & end);
	OpenPoint* findway(const MyPoint& _start, const MyPoint& end);
};


#endif // AstarCaculator_h__