#pragma once
#ifndef BinaryHeap_h__
#define BinaryHeap_h__

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

/******************************************
*   类的名称：二叉堆
******************************************/

template<typename Comparable>
class BinaryHeap
{
public:
	explicit BinaryHeap(int capacity = 1000) :array(capacity,nullptr), currentSize(0) {}
	explicit BinaryHeap(const vector<Comparable*> & items);

	bool isEmpty() const;//推断二叉堆是否为空
	Comparable* findMin() const;//查找最小元素

	void insert(Comparable* x);//插入元素x
	void deleteMin();//删除最小元素
	void makeEmpty();//清空该二叉堆 

private:
	vector<Comparable*> array;//存储二叉堆的节点 
	int currentSize;//当前二叉堆中的节点数目
private:
	void buildHeap();//将元素移动到合适的位置
	void percolateDown(int hole);//下移动
};

template<typename Comparable>
BinaryHeap<Comparable>::BinaryHeap(const vector<Comparable*> & items) :array(items.size() + 10), currentSize(items.size())
{
	for (unsigned i = 0; i < items.size(); ++i)
		array[i + 1] = items[i];

	buildHeap();
}

/****************************************************************
*   功能描写叙述: 将元素移动到合适的位置，满足堆序
*****************************************************************/
template<typename Comparable>
void BinaryHeap<Comparable>::buildHeap()
{
	for (int i = currentSize / 2; i > 0; --i)
		percolateDown(i);
}

template<typename Comparable>
Comparable* BinaryHeap<Comparable>::findMin()const
{
	return array[1];
}


template<typename Comparable>
void BinaryHeap<Comparable>::insert(Comparable* x)
{
	if (currentSize == array.size() - 1)
		array.resize(2 * array.size());//扩大堆中数组的容量
									   //获得空穴的位置
	int hole = ++currentSize;

	//上滤
	for (; hole > 1 && (*x) < (*array[hole / 2]); hole /= 2)
		array[hole] = array[hole / 2];
	//将x插入到合适的位置
	array[hole] = x;
}

template<typename Comparable>
void BinaryHeap<Comparable>::deleteMin()
{
	if (isEmpty()) {
		cout << "BinaryHeap is empty." << endl;
		return;
	}

	array[1] = array[currentSize];//将最后一个元素移动到最小元素的位置
	currentSize--;//元素总数减去1
				  //将最后一个元素移动到合适的位置
	percolateDown(1);
}

/****************************************************************
*   功能描写叙述: 将array(hole)处的值向下移动
*   參数列表: hole为堆中元素的位置标号
*****************************************************************/
template<typename Comparable>
void BinaryHeap<Comparable>::percolateDown(int hole)
{
	int child;
	//先保存array[hole]的值
	Comparable* temp = array[hole];

	for (; hole * 2 <= currentSize; hole = child) {
		child = hole * 2;

		//child != currentSize,表明此时空穴有右儿子
		//array[child] > array[child+1] 表明此时空穴有右儿子小于左儿子
		if (child != currentSize && (*array[child]) > (*array[child + 1]))
			child++;//此时child表示为空穴的右儿子

					//空穴的右儿子小于array[hole]
		if ((*array[child]) < (*temp))
			array[hole] = array[child];
		else
			break;
	}

	array[hole] = temp;
}


template<typename Comparable>
void BinaryHeap<Comparable>::makeEmpty()
{
	for (int i = 1; i <= currentSize; ++i)
	{
		delete array[i];
		array[i] = nullptr;
	}

	currentSize = 0;
}

template<typename Comparable>
bool BinaryHeap<Comparable>::isEmpty() const
{
	return currentSize == 0;
}

#endif // BinaryHeap_h__