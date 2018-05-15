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
鼠标（方向）控制器
（使用前应bind所有参数）
********************************/

class MouseController : public Node {
private:
	Player* m_player;
	Node* m_mainmap;
	int m_shieldCount;
	CC_SYNTHESIZE_PASS_BY_REF(vector<Node*>, r_otherUIs, OtherUIs);
private:
	//初始化摇杆触摸
	void initListener();
	void shield(Ref* r);	//屏蔽
	void unshield(Ref* r);	//取消屏蔽
	bool ifHaveOtherUI(const Vec2& point);//判定点位置有没有其它UI需要响应

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