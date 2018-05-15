#include "HumanPerception.h"
#include "GameManager.h"

HumanPerception::HumanPerception():m_dropRangeSq(2500){}

HumanPerception::~HumanPerception() {
	NotificationCenter::getInstance()->removeObserver(this, "DROP_REMOVE");
}

bool HumanPerception::init(){
	if (!Perception::init())return false;

	//���ܵ������Ƴ���Ϣ
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(HumanPerception::DeleteDropTargets), "DROP_REMOVE", nullptr);

	this->scheduleCheckIfLosingDropTargets(0.1f);

	this->scheduleCheckDrop(0.1f);

	return true;
}

HumanPerception* HumanPerception::create(Biology* biology)
{
	HumanPerception * pRet = new(std::nothrow)HumanPerception();
	if (pRet && pRet->init()) { pRet->autorelease(); pRet->setMaster(biology); }
	else CC_SAFE_DELETE(pRet);
	return pRet;
}

//ÿtime��������е�����
void HumanPerception::CheckAllDrops(float dt) {
	auto& droplist = GameManager::getInstance()->getDropList();
	for (auto drop : droplist)
		CheckDrop(drop);
}

//����֪�������Ƿ���ʧ
void HumanPerception::CheckIfLosingDropTargets(float dt) {
	//��������Ŀ�궪ʧ
	for (auto itr = m_dropTargets.begin(); itr != m_dropTargets.end();)
		if (!ifInTheRange(*itr, m_master, m_perceptionRangeSq))
			itr = m_dropTargets.erase(itr);
		else ++itr;
}


//��֪������Ŀ���Ƴ����ص�ɾ���йظ�Ŀ��ĸ�֪��Ϣ
void HumanPerception::DeleteDropTargets(Ref * r) {
	m_dropTargets.remove(static_cast<Drop*>(r));
}

//�������
void HumanPerception::CheckContainer(Container* target) {
	switch (target->getEntityTpye())
	{
	case EntityTpye::biology:
		CheckBiology(target);
		break;
	}
}

void HumanPerception::CheckDrop(Container* arg_target){
	auto drop = static_cast<Drop*>(arg_target);

	if (ifInTheRange(drop, m_master, m_perceptionRangeSq) && (std::find(m_dropTargets.begin(), m_dropTargets.end(), drop) == m_dropTargets.end()))
		m_dropTargets.push_back(drop);
}

Drop* HumanPerception::getNearestDrop(){
	Drop* nearestdrop = nullptr;
	float nearestdistanceSq = m_dropRangeSq;

	for (auto drop : m_dropTargets){
		float distanceSq = drop->getPosition().getDistanceSq(m_master->getPosition());
		if (nearestdistanceSq > distanceSq) { nearestdrop = drop; nearestdistanceSq = distanceSq; }
	}

	return nearestdrop;
}

bool HumanPerception::ifHaveDropTarget() {
	return !m_dropTargets.empty();
}