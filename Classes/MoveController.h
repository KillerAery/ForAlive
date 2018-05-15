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
摇杆
移动控制器
（使用前应bind所有参数）
********************************/

class MoveController : public Node {
private:
	//摇杆图片、属性
	Sprite* m_frontpng;
	Sprite* m_backpng;
	int m_frontradii;
	int m_backradii;
	Player* m_player;
	BackPackView* m_backpackview;
private:
	//初始化摇杆图片
	void initPNG();
	//初始化摇杆触摸
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
