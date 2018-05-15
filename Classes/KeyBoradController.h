#pragma once
#ifndef _KEYBORAD_CONTROLLER_H_
#define _KEYBORAD_CONTROLLER_H_

#include "cocos2d.h"
#include "Player.h"
#include "BackPackView.h"
#include "MissionView.h"

using cocos2d::Node;
using cocos2d::Sprite;
using cocos2d::Vec2;

using CallbackEvent = std::function<void(Player*)>;

/********************************
WIN32
���̿�����
��ʹ��ǰӦbind���в�����
********************************/

class KeyBoradController : public Node {
private:
	//����
	Player* m_player;
	int m_up;
	int m_down;
	int m_right;
	int m_left;
	int m_EKeyDown;
	BackPackView* r_backpackview;
	MissionView* r_missionView;
private:
	//��ʼ��Win32ƽ̨���̼���
	void initKeyBoardListener();
public:
	KeyBoradController();
	virtual ~KeyBoradController();
	virtual bool init();
	virtual void update(float dt)override;
	CREATE_FUNC(KeyBoradController);
	bool bindPlayer(Player* p);
	void bindBackPackView(BackPackView* b);
	void bindMissionView(MissionView* m);
};



#endif