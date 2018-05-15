#include "Perception.h"
#include "GameManager.h"

Perception::Perception():m_master(nullptr),m_perceptionRangeSq(40000), m_perceptionMaxRangeSq(160000){}

Perception::~Perception() {
	NotificationCenter::getInstance()->removeObserver(this, "BIOLOGY_REMOVE"); 
}

bool Perception::init(){
	if (!Perceptionable::init())return false;

	//���������Ƴ���Ϣ
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Perception::DeleteBiologyTargets), "BIOLOGY_REMOVE", nullptr);

	this->scheduleCheckContainer(0.1f);

	this->scheduleCheckIfLosingBiologyTargets(0.1f);

	return true;
}

Perception* Perception::create(Biology* biology)
{
	Perception * pRet = new(std::nothrow)Perception();
	if (pRet && pRet->init()) { pRet->autorelease(); pRet->setMaster(biology); }
	else CC_SAFE_DELETE(pRet);
	return pRet;
}

//����֪Ŀ���Ƿ�ʧ
void Perception::CheckIfLosingBiologyTargets(float dt) {
	//�������Ŀ�궪ʧ
	for (auto itr = m_biologyTargets.begin(); itr != m_biologyTargets.end(); ++itr)
		if (!ifInTheRange(*itr, m_master, m_perceptionMaxRangeSq)) {
			m_biologyTargets.erase(itr);
			return;
		}
}

//��֪����Ŀ���������ص�ɾ���йظ�Ŀ��ĸ�֪��Ϣ
void Perception::DeleteBiologyTargets(Ref* r) {
	if (r == m_master) { return; }
	m_biologyTargets.remove(static_cast<Biology*>(r));
}

//������������
void Perception::CheckAllContainers(float dt) {
	auto & containerMap = GameManager::getInstance()->getContainerMap();
	for (auto & pair : containerMap)
		CheckContainer(pair.second);
}

void Perception::CheckContainer(Container* target) {
	//���ڸ�֪�����ڣ��ż��
	//ֻ�����������
	if (target!=m_master && target->getEntityTpye() == EntityTpye::biology && ifInTheRange(target, m_master, m_perceptionRangeSq))
		CheckBiology(target);
}


void Perception::CheckBiology(Container* arg_target) {
	auto target = static_cast<Biology*>(arg_target);
	//�������ڸø�֪Ŀ�꣬�������Ϊ��֪Ŀ��
	if (std::find(m_biologyTargets.begin(), m_biologyTargets.end(), target) == m_biologyTargets.end())
			m_biologyTargets.push_back(target);
}


Biology* Perception::getNearest(Attitude attitude) {
	Biology* nearestTarget = nullptr;
	double nearestDistanceSq = m_perceptionMaxRangeSq;
	for (auto target : m_biologyTargets) {
		if(m_master->getRelationship()->getAttitude(target)!= attitude)continue;
		
		double distanceSq = m_master->getPosition().getDistanceSq(target->getPosition());
		if (distanceSq < nearestDistanceSq) { nearestTarget = target; nearestDistanceSq = distanceSq; }

	}
	return nearestTarget;
}

Biology* Perception::getPlayer() {
	auto player = GameManager::getInstance()->getPlayer();
	if (player&&ifInTheRange(player, m_master, m_perceptionRangeSq))return player;
	return nullptr;
}

Biology* Perception::getNearestBiology() {
	auto nearest = std::min_element(m_biologyTargets.begin(), m_biologyTargets.end(), [this](Biology* b1, Biology* b2){
		return (b1->getPosition().getDistanceSq(m_master->getPosition()) < b2->getPosition().getDistanceSq(m_master->getPosition()));
	});

	if (nearest != m_biologyTargets.end())return *nearest;
	return nullptr;
}

bool Perception::ifHaveBiologyTarget() {
	return !m_biologyTargets.empty();
}