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

单击控制器
（使用前应bind所有参数）
********************************/

class ClickController : public Node {
private:
	//摇杆图片、属性
	Sprite* m_png;
	Player* m_player;
	CallbackEvent m_callfunc;
private:
	//初始化摇杆图片
	void initPNG();
	//初始化摇杆触摸
	void initListener();
public:
	ClickController();
	virtual ~ClickController();
	virtual bool init();
	CREATE_FUNC(ClickController);
	//绑定玩家
	void bindPlayer(Player* p){ m_player = p; }
	//绑定触发事件
	void bindCallBackEvent(CallbackEvent func){ m_callfunc = func; }
};

#endif