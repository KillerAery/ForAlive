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
	//��ȡ�ϰ���ǣ�����رյ�
	void copyBarrierMark();
	// �������� 
	void cleanlist();
	//��麯�� �����ɹ����ֵ
	bool checkInBarrierAndCloseList(const MyPoint & p1);
	// ������飬��鸸�ڵ� 
	void open(OpenPoint* openp,const MyPoint & end);
	OpenPoint* findway(const MyPoint& _start, const MyPoint& end);
};


#endif // AstarCaculator_h__