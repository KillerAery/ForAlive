#pragma once
#ifndef HumanPerception_h__
#define HumanPerception_h__

#include "Perception.h"

class HumanPerception : public Perception{
protected:
	CC_SYNTHESIZE_PASS_BY_REF(std::list<Drop*>, m_dropTargets, DropTargets);	//感知掉落物目标列表
	CC_SYNTHESIZE(double, m_dropRangeSq, DropRangeSq);							//掉落物距离
public:
	HumanPerception();
	virtual ~HumanPerception();
	virtual bool init();
	static HumanPerception* create(Biology* biology);
public:
	//每time秒遍历所有掉落物
	void scheduleCheckDrop(float time) { this->schedule(schedule_selector(HumanPerception::CheckAllDrops), time); }
	//每time秒检测感知掉落物目标是否消失
	void scheduleCheckIfLosingDropTargets(float time) { this->schedule(schedule_selector(HumanPerception::CheckIfLosingDropTargets), time); }
	//感知掉落物目标移除,回调删除
	void DeleteDropTargets(Ref * r);
	//检测感知掉落物是否消失
	void CheckIfLosingDropTargets(float dt);
	//每time秒遍历所有掉落物
	void CheckAllDrops(float dt);
	//检测掉落物
	virtual void CheckDrop(Container* arg_target);
	//检测容器
	virtual void CheckContainer(Container* target);
public:
	virtual Drop* getNearestDrop();
	virtual bool ifHaveDropTarget();
};

#endif // HumanPerception_h__