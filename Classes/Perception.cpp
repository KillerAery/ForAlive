#include "Perception.h"
#include "GameManager.h"

Perception::Perception():m_master(nullptr),m_perceptionRangeSq(40000), m_perceptionMaxRangeSq(160000){}

Perception::~Perception() {
	NotificationCenter::getInstance()->removeObserver(this, "BIOLOGY_REMOVE"); 
}

bool Perception::init(){
	if (!Perceptionable::init())return false;

	//接受生物移除信息
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

//检测感知目标是否丢失
void Perception::CheckIfLosingBiologyTargets(float dt) {
	//检测生物目标丢失
	for (auto itr = m_biologyTargets.begin(); itr != m_biologyTargets.end(); ++itr)
		if (!ifInTheRange(*itr, m_master, m_perceptionMaxRangeSq)) {
			m_biologyTargets.erase(itr);
			return;
		}
}

//感知生物目标死亡，回调删除有关该目标的感知信息
void Perception::DeleteBiologyTargets(Ref* r) {
	if (r == m_master) { return; }
	m_biologyTargets.remove(static_cast<Biology*>(r));
}

//遍历所有容器
void Perception::CheckAllContainers(float dt) {
	auto & containerMap = GameManager::getInstance()->getContainerMap();
	for (auto & pair : containerMap)
		CheckContainer(pair.second);
}

void Perception::CheckContainer(Container* target) {
	//若在感知距离内，才检测
	//只检测生物类型
	if (target!=m_master && target->getEntityTpye() == EntityTpye::biology && ifInTheRange(target, m_master, m_perceptionRangeSq))
		CheckBiology(target);
}


void Perception::CheckBiology(Container* arg_target) {
	auto target = static_cast<Biology*>(arg_target);
	//若不存在该感知目标，则添加其为感知目标
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