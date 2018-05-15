#pragma once
#ifndef _MOVECONTROLLER_H_
#define _MOVECONTROLLER_H_

#include "cocos2d.h"
#include "Player.h"
#include "BackPackView.h"

using cocos2d::Node;
using cocos2d::Sprite;
using cocos2d::Vec2;

using CallbackEvent = std::function<void(Player*)>;


/********************************
ҡ��
�ƶ�������
��ʹ��ǰӦbind���в�����
********************************/

class MoveController : public Node {
private:
	//ҡ��ͼƬ������
	Sprite* m_frontpng;
	Sprite* m_backpng;
	int m_frontradii;
	int m_backradii;
	Player* m_player;
	BackPackView* m_backpackview;
private:
	//��ʼ��ҡ��ͼƬ
	void initPNG();
	//��ʼ��ҡ�˴���
	void initListener();
private:
	inline void judgePoint(Vec2 p);
public:	
	MoveController();
	virtual ~MoveController();
	virtual bool init();
	CREATE_FUNC(MoveController);
	bool bindPlayer(Player* p);
	void bindBackPackView(BackPackView* b);
};




#endif // !_MOVECONTROLLER_H_
