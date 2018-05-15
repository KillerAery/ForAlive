#include "GameManager.h"
#include "BackPackView.h"
#include "PlayerPerception.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using cocos2d::NotificationCenter;

BackPackView::BackPackView():m_opener(nullptr),m_backpacklayer(nullptr),m_mylistview(nullptr),m_otherlistview(nullptr){}

BackPackView::~BackPackView(){
	NotificationCenter::getInstance()->removeObserver(this, "CONTAINER_REMOVE");
	NotificationCenter::getInstance()->removeObserver(this, "DROP_REMOVE");
	BackPackUITemplate::deleteInstance();
	ItemPageView::s_itempageview_list.clear();
}

bool BackPackView::init() {
	if (!Widget::init())return false;
	initUI();
	initUITemplates();
	//ɾ��������������
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(BackPackView::ContainerDelete), "CONTAINER_REMOVE", nullptr);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(BackPackView::ContainerDelete), "DROP_REMOVE", nullptr);
	return true;
}

void BackPackView::initUI() {
	//���뱳��UI.csb�ļ�
	m_backpacklayer = static_cast<Layer*>(cocos2d::CSLoader::createNode("UI/BackPackLayer.csb"));
	//��������ӱ���UI
	this->addChild(m_backpacklayer);
	m_mylistview = static_cast<ListView*>(m_backpacklayer->getChildByTag(1)->getChildByTag(34));
	m_otherlistview = static_cast<ListView*>(m_backpacklayer->getChildByTag(1)->getChildByTag(23));
	//��ʼ�����ذ�ť 
	auto button = static_cast<Button*>(m_backpacklayer->getChildByTag(1)->getChildByName("Button_back"));
	button->addClickEventListener([this](Ref*) {this->closeBackPack();});

}

//��ʼ������UI�ĸ���ģ��
void BackPackView::initUITemplates() {
	BackPackUITemplate::getInstance()->loadBackPackUI(m_backpacklayer);
}


//��ʼ��װ��ģ��
void BackPackView::initGearPageView() {
	//����װ��
	for (int i = GearTpye::HeadGear; i <= GearTpye::HandGear; ++i)
		this->addChild(GearPageView::create(m_opener, i, m_backpacklayer));
	//����������װ��
	for (int i = GearTpye::LeftHandGear; i <= GearTpye::RightHandGear; ++i)
		this->addChild(WeaponGearPageView::create(m_opener, i, m_backpacklayer));
}

//��ʼ���Լ�����ҳ
void BackPackView::initContainerPageView() {
	m_mylistview->pushBackCustomItem(ContainerPageView::create(m_opener));
}

BackPackView* BackPackView::create() {
	auto backpackview = new (std::nothrow)BackPackView();
	if (backpackview &&backpackview->init()) {backpackview->autorelease();}
	else CC_SAFE_DELETE(backpackview);
	return backpackview;
}

//�Ƴ���ҳ
void BackPackView::removePageView(ItemPageView* i) {
	ItemPageView::s_itempageview_list.remove(i);
}

void BackPackView::openOrCloseBackPack(Biology* biology) {
	//��biology������
	if (!biology)return;
	//���Ѿ��򿪣���ر�
	if (isVisible()){closeBackPack();return;}

	this->setOpener(biology);
	this->setVisible(true);
	
	initContainerPageView();
	//initOtherContainerPageView();
	initGearPageView();

	//ÿ0.1������Χ����
	this->schedule(schedule_selector(BackPackView::checkContainer),0.1f);
	//���������ƣ�UI���⣩
	NotificationCenter::getInstance()->postNotification("MOUSE_SHIELD",this);
}
void BackPackView::closeBackPack() {
	if (!isVisible())return;

	this->setVisible(false);
	this->setOpener(nullptr);
	//ֹͣ�����Χ���� 
	this->unschedule(schedule_selector(BackPackView::checkContainer));

	//�Ƴ�������Ʒҵ
	for (auto i : ItemPageView::s_itempageview_list)
		i->removeFromParent();
	ItemPageView::s_itempageview_list.clear();

	//�Ƴ������б����������ҵ
	m_otherlistview->removeAllChildren();
	//�Ƴ��Լ��б������ҵ
	m_mylistview->removeAllChildren();


	//ȡ�����������ƣ�UI���⣩
	NotificationCenter::getInstance()->postNotification("MOUSE_UNSHIELD",this);
}

//Ϊ�·��ֵ�Ŀ��������� һ��viewҳ
void BackPackView::addTargetAsView(Container* target) {
	//�������Ǳ����Լ���������Ҿ����Զ�����˳�
	if (!ifInTheRange(target, m_opener, 70 * 70))return;
	//����������ҳ
	auto children = m_otherlistview->getItems();
	//��û��������View������� �·��ֵ�����ҳ
	if (std::find_if(children.begin(), children.end(),[=](Node* one) {return target == static_cast<ContainerPageView*>(one)->getContainer(); })
		== children.end())
		m_otherlistview->pushBackCustomItem(ContainerPageView::create(target));
	
}
//�����Χ����
void BackPackView::checkContainer(float dt){
	//����Ƿ���Ӹ�Ӧ����
	auto player = GameManager::getInstance()->getPlayer();
	auto percetion = static_cast<PlayerPerception*>(player->getPerception());
	//��������
	for (auto i : percetion->getDropTargets())
		addTargetAsView(i);
	//�������
	for (auto i : percetion->getContainerTargets())
		addTargetAsView(i);
	

	//����������ҳ
	auto children = m_otherlistview->getItems();
 	//����Ƿ�ʧȥ��Ӧ����
	for (auto i = 0; i < children.size(); ++i) {
		auto ipv = static_cast<ContainerPageView*>(children.at(i));
		//������Ҿ����Զ�����ܶ�ʧ�����ĸ�Ӧ
		if (!ifInTheRange(ipv->getContainer(), m_opener, 70 * 70))
		{
			ItemPageView::s_itempageview_list.remove(ipv);
			m_otherlistview->removeItem(i);
			return;
		}
	}
}

void BackPackView::ContainerDelete(Ref* r){
	auto children = m_otherlistview->getItems();
	for (auto i = 0; i < m_otherlistview->getItems().size(); ++i) {
		auto ipv = static_cast<ContainerPageView*>(children.at(i));
		//����ҵ�����ɾ��
		if (ipv->getContainer() == r) {
			m_otherlistview->removeItem(i); 
			ItemPageView::s_itempageview_list.remove(ipv);
			return; 
		}
	}
	//û�ҵ���ASSERT
	CC_ASSERT("BackPackView dosen't have such a Container to be deleted!");
}