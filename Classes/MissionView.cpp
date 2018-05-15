#include "MissionView.h"
#include "MissionManager.h"

MissionView::MissionView() :m_missionLayer(nullptr),m_nameText(nullptr),m_descriptionText(nullptr),m_listView(nullptr){
}
MissionView::~MissionView() {
	MissionUITemplate::deleteInstance();
}
bool MissionView::init(){
	if (!Widget::init())return false;
	initUI();

	return true;
}
void MissionView::initUI(){
	//读入背包UI.csb文件
	m_missionLayer = static_cast<Layer*>(cocos2d::CSLoader::createNode("UI/MissionLayer.csb"));
	m_nameText = static_cast<Text*>(m_missionLayer->getChildByName("MissionLayout")->getChildByName("Name"));
	m_descriptionText = static_cast<Text*>(m_missionLayer->getChildByName("MissionLayout")->getChildByName("Description"));
	m_listView = static_cast<ListView*>(m_missionLayer->getChildByName("ListView"));
	//载入模板
	MissionUITemplate::getInstance()->loadMissionLayerUI(m_missionLayer);

	this->addChild(m_missionLayer);
}

void MissionView::openOrCloseMissionView(){
	static bool ifFirst = true;
	//一开始就有任务0
	if (ifFirst) { MissionManager::getInstance()->runMission(0); ifFirst = false; }
	
	if (isVisible()) { closeMissionView(); return; }
	this->setVisible(true);
	//屏蔽鼠标控制（UI界外）
	NotificationCenter::getInstance()->postNotification("MOUSE_SHIELD", this);
}

void MissionView::closeMissionView() {
	if (!isVisible())return;
	this->setVisible(false);
	//取消屏蔽鼠标控制（UI界外）
	NotificationCenter::getInstance()->postNotification("MOUSE_UNSHIELD", this);
}

void MissionView::addMission(Mission& mission) {
	//任务名字项
	auto MissionItem = MissionUITemplate::getInstance()->getMissionItemTemplate();
	auto name = static_cast<Text*>(MissionItem->getChildByName("Name"));
	name->setString(mission.getName());
	//放入任务列表
	m_listView->pushBackCustomItem(MissionItem);
	//监听：点击则显示任务具体信息
	MissionItem->addTouchEventListener([this, &mission](Ref*, TouchEventType) {
		this->selectMission(mission);
	});
	//如果只有一个任务，则展开该任务具体信息
	if (m_listView->getItems().size() == 1)
	selectMission(mission);
}

void MissionView::updateMission(Mission& mission) {
	selectMission(mission);
}

void MissionView::selectMission(Mission& mission) {
	//先清理之前的targetLayout
	cleanupMissionTargetLayout();

	//显示任务名字描述
	string str = mission.getName();
	if (mission.getStatus() == MissionStatus::finish)
		str += string(u8"(已完成)");
	m_nameText->setString(str);

	m_descriptionText->setString(mission.getDescription());
	//显示任务所有目标
	for (auto & target : mission.getTargets()) {
		auto targetLayout = MissionUITemplate::getInstance()->getTargetTemplate();
		
		if (!m_targetLayouts.empty())
			targetLayout->setPositionY(m_targetLayouts.back()->getPositionY() - targetLayout->getContentSize().height - 5);

		//目标文字
		auto text = static_cast<Text*>(targetLayout->getChildByName("Description"));
		text->setString(target.getDescription()+cocos2d::StringUtils::format(" %d/%d",target.getNum(),target.getRequireNum()));
		//是否打勾
		auto checkBox = static_cast<CheckBox*>(targetLayout->getChildByName("CheckBox"));
		checkBox->setSelectedState(target.ifAchieve());

		m_missionLayer->addChild(targetLayout);
		m_targetLayouts.push_back(targetLayout);
	}
}

void MissionView::cleanupMissionTargetLayout() {
	for (auto i : m_targetLayouts)
		i->removeFromParent();

	m_targetLayouts.clear();
}