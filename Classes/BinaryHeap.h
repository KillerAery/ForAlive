#pragma once
#ifndef BinaryHeap_h__
#define BinaryHeap_h__

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

/******************************************
*   ������ƣ������
******************************************/

template<typename Comparable>
class BinaryHeap
{
public:
	explicit BinaryHeap(int capacity = 1000) :array(capacity,nullptr), currentSize(0) {}
	explicit BinaryHeap(const vector<Comparable*> & items);

	bool isEmpty() const;//�ƶ϶�����Ƿ�Ϊ��
	Comparable* findMin() const;//������СԪ��

	void insert(Comparable* x);//����Ԫ��x
	void deleteMin();//ɾ����СԪ��
	void makeEmpty();//��ոö���� 

private:
	vector<Comparable*> array;//�洢����ѵĽڵ� 
	int currentSize;//��ǰ������еĽڵ���Ŀ
private:
	void buildHeap();//��Ԫ���ƶ������ʵ�λ��
	void percolateDown(int hole);//���ƶ�
};

template<typename Comparable>
BinaryHeap<Comparable>::BinaryHeap(const vector<Comparable*> & items) :array(items.size() + 10), currentSize(items.size())
{
	for (unsigned i = 0; i < items.size(); ++i)
		array[i + 1] = items[i];

	buildHeap();
}

/****************************************************************
*   ������д����: ��Ԫ���ƶ������ʵ�λ�ã��������
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
		array.resize(2 * array.size());//����������������
									   //��ÿ�Ѩ��λ��
	int hole = ++currentSize;

	//����
	for (; hole > 1 && (*x) < (*array[hole / 2]); hole /= 2)
		array[hole] = array[hole / 2];
	//��x���뵽���ʵ�λ��
	array[hole] = x;
}

template<typename Comparable>
void BinaryHeap<Comparable>::deleteMin()
{
	if (isEmpty()) {
		cout << "BinaryHeap is empty." << endl;
		return;
	}

	array[1] = array[currentSize];//�����һ��Ԫ���ƶ�����СԪ�ص�λ��
	currentSize--;//Ԫ��������ȥ1
				  //�����һ��Ԫ���ƶ������ʵ�λ��
	percolateDown(1);
}

/****************************************************************
*   ������д����: ��array(hole)����ֵ�����ƶ�
*   �����б�: holeΪ����Ԫ�ص�λ�ñ��
*****************************************************************/
template<typename Comparable>
void BinaryHeap<Comparable>::percolateDown(int hole)
{
	int child;
	//�ȱ���array[hole]��ֵ
	Comparable* temp = array[hole];

	for (; hole * 2 <= currentSize; hole = child) {
		child = hole * 2;

		//child != currentSize,������ʱ��Ѩ���Ҷ���
		//array[child] > array[child+1] ������ʱ��Ѩ���Ҷ���С�������
		if (child != currentSize && (*array[child]) > (*array[child + 1]))
			child++;//��ʱchild��ʾΪ��Ѩ���Ҷ���

					//��Ѩ���Ҷ���С��array[hole]
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