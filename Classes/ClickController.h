#pragma once
#ifndef _CLICK_CONTROLLER_H_
#define _CLICK_CONTROLLER_H_

#include "cocos2d.h"
#include "Player.h"

using cocos2d::Node;
using cocos2d::Sprite;
using cocos2d::Vec2;

using CallbackEvent = std::function<void(Player*)>;

/********************************

����������
��ʹ��ǰӦbind���в�����
********************************/

class ClickController : public Node {
private:
	//ҡ��ͼƬ������
	Sprite* m_png;
	Player* m_player;
	CallbackEvent m_callfunc;
private:
	//��ʼ��ҡ��ͼƬ
	void initPNG();
	//��ʼ��ҡ�˴���
	void initListener();
public:
	ClickController();
	virtual ~ClickController();
	virtual bool init();
	CREATE_FUNC(ClickController);
	//�����
	void bindPlayer(Player* p){ m_player = p; }
	//�󶨴����¼�
	void bindCallBackEvent(CallbackEvent func){ m_callfunc = func; }
};

#endif