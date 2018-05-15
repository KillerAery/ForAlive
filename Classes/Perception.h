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
	CC_SYNTHESIZE_PASS_BY_REF(std::list<Biology*>, m_biologyTargets, BiologyTargets);	//��֪����Ŀ���б�
	CC_SYNTHESIZE(double, m_perceptionRangeSq, PerceptionRangeSq);						//��֪����
	CC_SYNTHESIZE(double, m_perceptionMaxRangeSq, PerceptionMaxRangeSq);				//��Զ��֪����
public:
	Perception();
	virtual ~Perception();
	virtual bool init();
	static Perception* create(Biology* biology);
public:
	//ÿtime�����֪����Ŀ���Ƿ���ʧ
	void scheduleCheckIfLosingBiologyTargets(float time) { this->schedule(schedule_selector(Perception::CheckIfLosingBiologyTargets), time); }
	//��֪����Ŀ���������ص�ɾ��
	void DeleteBiologyTargets(Ref * r);
	//����֪Ŀ���Ƿ���ʧ
	void CheckIfLosingBiologyTargets(float dt);
	/*-----�����������������磨�����⣬�����⣩��------*/
	//ÿtime�������������
	void scheduleCheckContainer(float time){this->schedule(schedule_selector(Perception::CheckAllContainers), time); }
	//������������
	void CheckAllContainers(float dt);
	//�������
	virtual void CheckContainer(Container* target);
	//�������
	virtual void CheckBiology(Container* arg_target);
public:
	virtual Biology* getNearest(Attitude attitude);
	virtual Biology* getPlayer();
	virtual Biology* getNearestBiology();
	virtual bool ifHaveBiologyTarget();
};

#endif // Perception_h__