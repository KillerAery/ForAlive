#pragma once
#ifndef _MOUSE_CONTROLLER_H_
#define _MOUSE_CONTROLLER_H_

#include "cocos2d.h"
#include "Player.h"

using cocos2d::Node;
using cocos2d::Vec2;
using std::vector;

/********************************
WIN32
��꣨���򣩿�����
��ʹ��ǰӦbind���в�����
********************************/

class MouseController : public Node {
private:
	Player* m_player;
	Node* m_mainmap;
	int m_shieldCount;
	CC_SYNTHESIZE_PASS_BY_REF(vector<Node*>, r_otherUIs, OtherUIs);
private:
	//��ʼ��ҡ�˴���
	void initListener();
	void shield(Ref* r);	//����
	void unshield(Ref* r);	//ȡ������
	bool ifHaveOtherUI(const Vec2& point);//�ж���λ����û������UI��Ҫ��Ӧ

public:
	MouseController();
	virtual ~MouseController();
	virtual bool init();
	CREATE_FUNC(MouseController);

	void bindPlayer(Player* p){ m_player = p; }
	void bindMap(Node* n) { m_mainmap = n;  }
	void pushOtherUI(Node* ui);
};


#endif