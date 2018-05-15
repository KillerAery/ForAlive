#ifndef OpenPoint_h__
#define OpenPoint_h__

#include <iostream>
#include <algorithm>
#include "MyPoint.h"

/* openpoint */
struct OpenPoint :public MyPoint{
	int cost;                 // �ķ�ֵ
	int pred;                 // Ԥ��ֵ
	OpenPoint* father;        // ���ڵ�
	OpenPoint(const MyPoint & p,const MyPoint& end, int c, OpenPoint *fatherp):MyPoint(p), cost(c), father(fatherp){
		//���λ��x,yȡ����ֵ
		int relativex = std::abs(end.x - p.x);
		int relativey = std::abs(end.y - p.y);
		//x,yƫ��ֵn
		int n = relativex - relativey;
		pred = std::max(relativex, relativey) * 14 - std::abs(n) * 4 + c;
		// (max�Cn)*14+n*10+c
	}

	//openpoint �ȽϺ���
	bool operator < (const OpenPoint &op)const { return pred < op.pred; }
	bool operator > (const OpenPoint &op)const { return pred > op.pred; }

};


#endif // OpenPoint_h__