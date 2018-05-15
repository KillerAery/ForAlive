#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Biology.h"

class Player :public Biology {
	CC_SYNTHESIZE(Biology*, m_target,Target);
public:	
	//��ʼ������
	Player();
	~Player();
	virtual bool init(ValueMap& obj_valuemap);
	static Player* create(ValueMap& obj_valuemap);
	//�ӳ������Ƴ�
	virtual void removeFromScene()override;
	//���������
	virtual void checkTrigger(int id,int num)override;

	////��������
	//virtual void CheckDrop(Container* arg_target)override;
};

#endif // !_PLAYER_H_
