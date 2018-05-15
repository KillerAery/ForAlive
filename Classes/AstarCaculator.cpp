#include "AstarCaculator.h"

#include "GameManager.h"

AstarCaculator::AstarCaculator():m_count(0){}

//获取障碍标记，清除关闭点
void AstarCaculator::copyBarrierMark() {
	for (int i = 0; i < 50; ++i)
		for (int j = 0; j < 100; ++j)
			mark[i][j] = GameManager::getInstance()->barrierMark[i][j];
	return;
}

// 清理容器 
void AstarCaculator::cleanlist() {
	if (!openlist.isEmpty()) {
		openlist.makeEmpty();
	}
	copyBarrierMark();
}

//检查函数 返还成功与否值
bool AstarCaculator::checkInBarrierAndCloseList(const MyPoint & pos) {
	if (pos.x < 0 || pos.y < 0 || pos.x >= GameManager::getInstance()->getTiles().width || pos.y >= GameManager::getInstance()->getTiles().height)
		return false;
	return mark[pos.x][pos.y];
}

// 开启检查，检查父节点 
void AstarCaculator::open(OpenPoint* openp,const MyPoint & end) {
	m_count++;
	//将父节点从openlist移除
	openlist.deleteMin();

	//检查p点四方的点
	MyPoint points1[4] = { MyPoint(openp->x + 1 , openp->y),MyPoint(openp->x, openp->y + 1),MyPoint(openp->x - 1, openp->y), MyPoint(openp->x,openp->y -1) };
	bool have[4];

	for (int i = 0; i < 4; ++i)
	{
		if (checkInBarrierAndCloseList(points1[i])) {
			openlist.insert(new OpenPoint(points1[i], end, openp->cost + 10, openp));
			have[i] = true;
		}
		else have[i] = false;
	}

	//检查p点四角的点
	MyPoint points2[4] = { MyPoint(openp->x + 1,openp->y + 1) ,MyPoint(openp->x - 1,openp->y + 1),MyPoint(openp->x - 1,openp->y - 1),MyPoint(openp->x + 1,openp->y-1) };

	for (int i = 0; i < 4; ++i)
		if (have[i] && have[i == 3 ? 0 : (i + 1)] && checkInBarrierAndCloseList(points2[i]))
			openlist.insert(new OpenPoint(points2[i], end, openp->cost + 14, openp));

	//关闭父节点p点
	mark[openp->x][openp->y] = false;
}

OpenPoint* AstarCaculator::findway(const MyPoint& start, const MyPoint& end){
	auto a = start;
	auto b = end;
	// 清理节点容器
	cleanlist();
	m_count = 0;

	// 创建一个父节点
	// 开启该节点
	openlist.insert(new OpenPoint(start, end, 0, nullptr));
	// 重复寻找预测和花费之和最小节点开启检查
	OpenPoint* minOpenp = openlist.findMin();
	for (; (*minOpenp) != end; minOpenp = openlist.findMin())
	{
		open(minOpenp, end);
		if (openlist.isEmpty()||m_count>=300)return openlist.findMin();
	}

	// 找到重点后返还end点
	return openlist.findMin()->father;
}