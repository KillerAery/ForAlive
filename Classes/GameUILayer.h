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

//游戏UI层
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
	void initController(GameLayer* mainlayer);//初始化控制器
	void initBackPackView();//初始化背包界面
	void initMissionView();//初始化任务界面
	void initButton(GameLayer* mainlayer);//初始化按钮
	void initLogButton();//初始化日志按钮
	void closeUIWithPlayer(Ref* r);//关闭控制玩家的UI
	static GameUILayer* create(GameLayer* mainlayer);
};


#endif