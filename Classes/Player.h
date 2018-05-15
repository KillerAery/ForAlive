#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Biology.h"

class Player :public Biology {
	CC_SYNTHESIZE(Biology*, m_target,Target);
public:	
	//初始化部分
	Player();
	~Player();
	virtual bool init(ValueMap& obj_valuemap);
	static Player* create(ValueMap& obj_valuemap);
	//从场景中移除
	virtual void removeFromScene()override;
	//触发器检测
	virtual void checkTrigger(int id,int num)override;

	////检测掉落物
	//virtual void CheckDrop(Container* arg_target)override;
};

#endif // !_PLAYER_H_
