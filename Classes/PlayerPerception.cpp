#include "PlayerPerception.h"

PlayerPerception::PlayerPerception(){}

PlayerPerception::~PlayerPerception(){
	NotificationCenter::getInstance()->removeObserver(this,"CONTAINER_REMOVE");
}

bool PlayerPerception::init() {
	if (!HumanPerception::init())return false;
	//接受掉落物移除信息
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(PlayerPerception::DeleteContainerTargets), "CONTAINER_REMOVE", nullptr);

	this->scheduleCheckIfLosingContainerTargets(0.1f);

	return true;
}

PlayerPerception* PlayerPerception::create(Biology* biology) {
	PlayerPerception * pRet = new(std::nothrow)PlayerPerception();
	if (pRet && pRet->init()) { pRet->autorelease(); pRet->setMaster(biology); }
	else CC_SAFE_DELETE(pRet);
	return pRet;
}

//检测容器
void PlayerPerception::CheckContainer(Container* target) {
	if (target == m_master||!ifInTheRange(target, m_master, m_perceptionRangeSq))return;
	//检测生物类型
	if (target->getEntityTpye() == EntityTpye::biology)CheckBiology(target);
	else if (target->getEntityTpye() == EntityTpye::container){
		//在极小范围内显示tab键提示键
		if (ifInTheRange(target, m_master,2500))target->showTabKey();
		else target->hideTabKey();
	}
	//检测容器类型
	//若不存在该感知目标，则添加其为感知目标
	if (std::find(m_containerTargets.begin(), m_containerTargets.end(), target) == m_containerTargets.end())
		m_containerTargets.push_back(target);

}

//感知容器目标死亡，回调删除
void PlayerPerception::DeleteContainerTargets(Ref * r) {
	if (r == m_master) return; 
	m_containerTargets.remove(static_cast<Container*>(r));
}
//检测感知容器目标是否消失
void PlayerPerception::CheckIfLosingContainerTargets(float dt) {
	//检测容器目标丢失
	for (auto itr = m_containerTargets.begin(); itr != m_containerTargets.end(); ++itr)
		if (!ifInTheRange(*itr, m_master, m_perceptionMaxRangeSq)) {
			m_containerTargets.erase(itr);
			return;
		}
}

//检测掉落物
void PlayerPerception::CheckDrop(Container* arg_target) {
	auto drop = static_cast<Drop*>(arg_target);

	if (!ifInTheRange(drop, m_master, m_perceptionRangeSq)){ 
		drop->undisplayerItemName();	//顺便关闭掉落物的名字
		return; }
	//若不存在该感知目标，则添加其为感知目标
	if (std::find(m_dropTargets.begin(), m_dropTargets.end(), drop) == m_dropTargets.end())
	{
		m_dropTargets.push_back(drop); 
		drop->displayItemName();		//顺便显示掉落物的名字
	}

}