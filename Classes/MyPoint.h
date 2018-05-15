#pragma once
#ifndef MyPoint_h__
#define MyPoint_h__

struct MyPoint {
		int x;
		int y;
		MyPoint(int ix, int iy) :x(ix), y(iy) {}
		MyPoint(const MyPoint& point) :x(point.x), y(point.y) {}
		bool operator == (const MyPoint& p)const { return x == p.x&&y == p.y; }
		bool operator !=(const MyPoint& p)const { return !(*this == p); }
};



#endif // MyPoint_h__