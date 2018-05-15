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
	//���뱳��UI.csb�ļ�
	m_missionLayer = static_cast<Layer*>(cocos2d::CSLoader::createNode("UI/MissionLayer.csb"));
	m_nameText = static_cast<Text*>(m_missionLayer->getChildByName("MissionLayout")->getChildByName("Name"));
	m_descriptionText = static_cast<Text*>(m_missionLayer->getChildByName("MissionLayout")->getChildByName("Description"));
	m_listView = static_cast<ListView*>(m_missionLayer->getChildByName("ListView"));
	//����ģ��
	MissionUITemplate::getInstance()->loadMissionLayerUI(m_missionLayer);

	this->addChild(m_missionLayer);
}

void MissionView::openOrCloseMissionView(){
	static bool ifFirst = true;
	//һ��ʼ��������0
	if (ifFirst) { MissionManager::getInstance()->runMission(0); ifFirst = false; }
	
	if (isVisible()) { closeMissionView(); return; }
	this->setVisible(true);
	//���������ƣ�UI���⣩
	NotificationCenter::getInstance()->postNotification("MOUSE_SHIELD", this);
}

void MissionView::closeMissionView() {
	if (!isVisible())return;
	this->setVisible(false);
	//ȡ�����������ƣ�UI���⣩
	NotificationCenter::getInstance()->postNotification("MOUSE_UNSHIELD", this);
}

void MissionView::addMission(Mission& mission) {
	//����������
	auto MissionItem = MissionUITemplate::getInstance()->getMissionItemTemplate();
	auto name = static_cast<Text*>(MissionItem->getChildByName("Name"));
	name->setString(mission.getName());
	//���������б�
	m_listView->pushBackCustomItem(MissionItem);
	//�������������ʾ���������Ϣ
	MissionItem->addTouchEventListener([this, &mission](Ref*, TouchEventType) {
		this->selectMission(mission);
	});
	//���ֻ��һ��������չ�������������Ϣ
	if (m_listView->getItems().size() == 1)
	selectMission(mission);
}

void MissionView::updateMission(Mission& mission) {
	selectMission(mission);
}

void MissionView::selectMission(Mission& mission) {
	//������֮ǰ��targetLayout
	cleanupMissionTargetLayout();

	//��ʾ������������
	string str = mission.getName();
	if (mission.getStatus() == MissionStatus::finish)
		str += string(u8"(�����)");
	m_nameText->setString(str);

	m_descriptionText->setString(mission.getDescription());
	//��ʾ��������Ŀ��
	for (auto & target : mission.getTargets()) {
		auto targetLayout = MissionUITemplate::getInstance()->getTargetTemplate();
		
		if (!m_targetLayouts.empty())
			targetLayout->setPositionY(m_targetLayouts.back()->getPositionY() - targetLayout->getContentSize().height - 5);

		//Ŀ������
		auto text = static_cast<Text*>(targetLayout->getChildByName("Description"));
		text->setString(target.getDescription()+cocos2d::StringUtils::format(" %d/%d",target.getNum(),target.getRequireNum()));
		//�Ƿ��
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