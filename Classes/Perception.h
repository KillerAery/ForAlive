#pragma once
#ifndef Perception_h__
#define Perception_h__

#include "Perceptionable.h"
#include "Biology.h"

class Perception : public Perceptionable{
protected:
	bool ifInTheRange(Entity* e1, Entity* e2, double rangeSq) {return e1->getPosition().getDistanceSq(e2->getPosition()) < rangeSq;}
protected:
	CC_SYNTHESIZE(Biology*, m_master, Master);
	CC_SYNTHESIZE_PASS_BY_REF(std::list<Biology*>, m_biologyTargets, BiologyTargets);	//感知生物目标列表
	CC_SYNTHESIZE(double, m_perceptionRangeSq, PerceptionRangeSq);						//感知距离
	CC_SYNTHESIZE(double, m_perceptionMaxRangeSq, PerceptionMaxRangeSq);				//最远感知距离
public:
	Perception();
	virtual ~Perception();
	virtual bool init();
	static Perception* create(Biology* biology);
public:
	//每time秒检测感知生物目标是否消失
	void scheduleCheckIfLosingBiologyTargets(float time) { this->schedule(schedule_selector(Perception::CheckIfLosingBiologyTargets), time); }
	//感知生物目标死亡，回调删除
	void DeleteBiologyTargets(Ref * r);
	//检测感知目标是否消失
	void CheckIfLosingBiologyTargets(float dt);
	/*-----遍历所有容器，例如（掉落检测，生物检测）用------*/
	//每time秒遍历所有容器
	void scheduleCheckContainer(float time){this->schedule(schedule_selector(Perception::CheckAllContainers), time); }
	//遍历所有容器
	void CheckAllContainers(float dt);
	//检测容器
	virtual void CheckContainer(Container* target);
	//检测生物
	virtual void CheckBiology(Container* arg_target);
public:
	virtual Biology* getNearest(Attitude attitude);
	virtual Biology* getPlayer();
	virtual Biology* getNearestBiology();
	virtual bool ifHaveBiologyTarget();
};

#endif // Perception_h__