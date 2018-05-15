#include "AstarCaculator.h"

#include "GameManager.h"

AstarCaculator::AstarCaculator():m_count(0){}

//��ȡ�ϰ���ǣ�����رյ�
void AstarCaculator::copyBarrierMark() {
	for (int i = 0; i < 50; ++i)
		for (int j = 0; j < 100; ++j)
			mark[i][j] = GameManager::getInstance()->barrierMark[i][j];
	return;
}

// �������� 
void AstarCaculator::cleanlist() {
	if (!openlist.isEmpty()) {
		openlist.makeEmpty();
	}
	copyBarrierMark();
}

//��麯�� �����ɹ����ֵ
bool AstarCaculator::checkInBarrierAndCloseList(const MyPoint & pos) {
	if (pos.x < 0 || pos.y < 0 || pos.x >= GameManager::getInstance()->getTiles().width || pos.y >= GameManager::getInstance()->getTiles().height)
		return false;
	return mark[pos.x][pos.y];
}

// ������飬��鸸�ڵ� 
void AstarCaculator::open(OpenPoint* openp,const MyPoint & end) {
	m_count++;
	//�����ڵ��openlist�Ƴ�
	openlist.deleteMin();

	//���p���ķ��ĵ�
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

	//���p���Ľǵĵ�
	MyPoint points2[4] = { MyPoint(openp->x + 1,openp->y + 1) ,MyPoint(openp->x - 1,openp->y + 1),MyPoint(openp->x - 1,openp->y - 1),MyPoint(openp->x + 1,openp->y-1) };

	for (int i = 0; i < 4; ++i)
		if (have[i] && have[i == 3 ? 0 : (i + 1)] && checkInBarrierAndCloseList(points2[i]))
			openlist.insert(new OpenPoint(points2[i], end, openp->cost + 14, openp));

	//�رո��ڵ�p��
	mark[openp->x][openp->y] = false;
}

OpenPoint* AstarCaculator::findway(const MyPoint& start, const MyPoint& end){
	auto a = start;
	auto b = end;
	// ����ڵ�����
	cleanlist();
	m_count = 0;

	// ����һ�����ڵ�
	// �����ýڵ�
	openlist.insert(new OpenPoint(start, end, 0, nullptr));
	// �ظ�Ѱ��Ԥ��ͻ���֮����С�ڵ㿪�����
	OpenPoint* minOpenp = openlist.findMin();
	for (; (*minOpenp) != end; minOpenp = openlist.findMin())
	{
		open(minOpenp, end);
		if (openlist.isEmpty()||m_count>=300)return openlist.findMin();
	}

	// �ҵ��ص�󷵻�end��
	return openlist.findMin()->father;
}