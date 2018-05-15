#pragma once
#ifndef _GAME_UILAYER_H_
#define _GAME_UILAYER_H_

#include "cocos2d.h"
#include "GameManager.h"
#include "GameLayer.h"

#include "MoveController.h"
#include "ClickController.h"
#include "MouseController.h"
#include "KeyBoradController.h"

#include "BackPackView.h"
#include "MissionView.h"
#include "MissionManager.h"

using cocos2d::Layer;

//��ϷUI��
class GameUILayer : public Layer {
protected:
	CC_SYNTHESIZE(cocos2d::Menu*, m_physicsTestButton,PhysicsTestButton);
	CC_SYNTHESIZE(BackPackView*, m_backpackview, BackPackView);
	CC_SYNTHESIZE(MissionView*, m_missionView, MissionView);
	CC_SYNTHESIZE(MoveController*, m_movecontroller, MoveController);
	CC_SYNTHESIZE(ClickController*,m_clickcontroller, ClickController);
	CC_SYNTHESIZE(MouseController*, m_mousecontroller, MouseController);
	CC_SYNTHESIZE(KeyBoradController*, m_keyboradcontroller, KeyBoradController);
public:
	GameUILayer();
	~GameUILayer();
	bool init(GameLayer* mainlayer);
	void initController(GameLayer* mainlayer);//��ʼ��������
	void initBackPackView();//��ʼ����������
	void initMissionView();//��ʼ���������
	void initButton(GameLayer* mainlayer);//��ʼ����ť
	void initLogButton();//��ʼ����־��ť
	void closeUIWithPlayer(Ref* r);//�رտ�����ҵ�UI
	static GameUILayer* create(GameLayer* mainlayer);
};


#endif