#pragma once
#ifndef PlayerPerception_h__
#define PlayerPerception_h__

#include "HumanPerception.h"

class PlayerPerception : public HumanPerception{
	CC_SYNTHESIZE_PASS_BY_REF(std::list<Container*>, m_containerTargets,ContainerTargets);	//感知容器目标列表
public:
	PlayerPerception();
	~PlayerPerception();
	virtual bool init();
	static PlayerPerception* create(Biology* biology);
public:
	//检测容器
	void CheckContainer(Container* target)override;
	//每time秒检测感知容器目标是否消失
	void scheduleCheckIfLosingContainerTargets(float time) { this->schedule(schedule_selector(PlayerPerception::CheckIfLosingContainerTargets), time); }
	//感知容器目标死亡，回调删除
	void DeleteContainerTargets(Ref * r);
	//检测感知容器目标是否消失
	void CheckIfLosingContainerTargets(float dt);
	//检测掉落物
	virtual void CheckDrop(Container* arg_target)override;

};

#endif // PlayerPerception_h__