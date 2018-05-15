#pragma once
#ifndef PlayerPerception_h__
#define PlayerPerception_h__

#include "HumanPerception.h"

class PlayerPerception : public HumanPerception{
	CC_SYNTHESIZE_PASS_BY_REF(std::list<Container*>, m_containerTargets,ContainerTargets);	//��֪����Ŀ���б�
public:
	PlayerPerception();
	~PlayerPerception();
	virtual bool init();
	static PlayerPerception* create(Biology* biology);
public:
	//�������
	void CheckContainer(Container* target)override;
	//ÿtime�����֪����Ŀ���Ƿ���ʧ
	void scheduleCheckIfLosingContainerTargets(float time) { this->schedule(schedule_selector(PlayerPerception::CheckIfLosingContainerTargets), time); }
	//��֪����Ŀ���������ص�ɾ��
	void DeleteContainerTargets(Ref * r);
	//����֪����Ŀ���Ƿ���ʧ
	void CheckIfLosingContainerTargets(float dt);
	//��������
	virtual void CheckDrop(Container* arg_target)override;

};

#endif // PlayerPerception_h__