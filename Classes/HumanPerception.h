#pragma once
#ifndef HumanPerception_h__
#define HumanPerception_h__

#include "Perception.h"

class HumanPerception : public Perception{
protected:
	CC_SYNTHESIZE_PASS_BY_REF(std::list<Drop*>, m_dropTargets, DropTargets);	//��֪������Ŀ���б�
	CC_SYNTHESIZE(double, m_dropRangeSq, DropRangeSq);							//���������
public:
	HumanPerception();
	virtual ~HumanPerception();
	virtual bool init();
	static HumanPerception* create(Biology* biology);
public:
	//ÿtime��������е�����
	void scheduleCheckDrop(float time) { this->schedule(schedule_selector(HumanPerception::CheckAllDrops), time); }
	//ÿtime�����֪������Ŀ���Ƿ���ʧ
	void scheduleCheckIfLosingDropTargets(float time) { this->schedule(schedule_selector(HumanPerception::CheckIfLosingDropTargets), time); }
	//��֪������Ŀ���Ƴ�,�ص�ɾ��
	void DeleteDropTargets(Ref * r);
	//����֪�������Ƿ���ʧ
	void CheckIfLosingDropTargets(float dt);
	//ÿtime��������е�����
	void CheckAllDrops(float dt);
	//��������
	virtual void CheckDrop(Container* arg_target);
	//�������
	virtual void CheckContainer(Container* target);
public:
	virtual Drop* getNearestDrop();
	virtual bool ifHaveDropTarget();
};

#endif // HumanPerception_h__