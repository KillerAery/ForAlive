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
	//删除背包其他容器
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(BackPackView::ContainerDelete), "CONTAINER_REMOVE", nullptr);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(BackPackView::ContainerDelete), "DROP_REMOVE", nullptr);
	return true;
}

void BackPackView::initUI() {
	//读入背包UI.csb文件
	m_backpacklayer = static_cast<Layer*>(cocos2d::CSLoader::createNode("UI/BackPackLayer.csb"));
	//给场景添加背包UI
	this->addChild(m_backpacklayer);
	m_mylistview = static_cast<ListView*>(m_backpacklayer->getChildByTag(1)->getChildByTag(34));
	m_otherlistview = static_cast<ListView*>(m_backpacklayer->getChildByTag(1)->getChildByTag(23));
	//初始化返回按钮 
	auto button = static_cast<Button*>(m_backpacklayer->getChildByTag(1)->getChildByName("Button_back"));
	button->addClickEventListener([this](Ref*) {this->closeBackPack();});

}

//初始化背包UI的各种模板
void BackPackView::initUITemplates() {
	BackPackUITemplate::getInstance()->loadBackPackUI(m_backpacklayer);
}


//初始化装备模块
void BackPackView::initGearPageView() {
	//身体装备
	for (int i = GearTpye::HeadGear; i <= GearTpye::HandGear; ++i)
		this->addChild(GearPageView::create(m_opener, i, m_backpacklayer));
	//左右手武器装备
	for (int i = GearTpye::LeftHandGear; i <= GearTpye::RightHandGear; ++i)
		this->addChild(WeaponGearPageView::create(m_opener, i, m_backpacklayer));
}

//初始化自己容器页
void BackPackView::initContainerPageView() {
	m_mylistview->pushBackCustomItem(ContainerPageView::create(m_opener));
}

BackPackView* BackPackView::create() {
	auto backpackview = new (std::nothrow)BackPackView();
	if (backpackview &&backpackview->init()) {backpackview->autorelease();}
	else CC_SAFE_DELETE(backpackview);
	return backpackview;
}

//移除子页
void BackPackView::removePageView(ItemPageView* i) {
	ItemPageView::s_itempageview_list.remove(i);
}

void BackPackView::openOrCloseBackPack(Biology* biology) {
	//若biology不存在
	if (!biology)return;
	//若已经打开，则关闭
	if (isVisible()){closeBackPack();return;}

	this->setOpener(biology);
	this->setVisible(true);
	
	initContainerPageView();
	//initOtherContainerPageView();
	initGearPageView();

	//每0.1秒检测周围容器
	this->schedule(schedule_selector(BackPackView::checkContainer),0.1f);
	//屏蔽鼠标控制（UI界外）
	NotificationCenter::getInstance()->postNotification("MOUSE_SHIELD",this);
}
void BackPackView::closeBackPack() {
	if (!isVisible())return;

	this->setVisible(false);
	this->setOpener(nullptr);
	//停止检测周围容器 
	this->unschedule(schedule_selector(BackPackView::checkContainer));

	//移除所有物品业
	for (auto i : ItemPageView::s_itempageview_list)
		i->removeFromParent();
	ItemPageView::s_itempageview_list.clear();

	//移除他人列表的所有容器业
	m_otherlistview->removeAllChildren();
	//移除自己列表的容器业
	m_mylistview->removeAllChildren();


	//取消屏蔽鼠标控制（UI界外）
	NotificationCenter::getInstance()->postNotification("MOUSE_UNSHIELD",this);
}

//为新发现的目标容器添加 一个view页
void BackPackView::addTargetAsView(Container* target) {
	//若容器是本身自己或者离玩家距离很远，则退出
	if (!ifInTheRange(target, m_opener, 70 * 70))return;
	//在其它容器页
	auto children = m_otherlistview->getItems();
	//若没存在所属View，则添加 新发现的容器页
	if (std::find_if(children.begin(), children.end(),[=](Node* one) {return target == static_cast<ContainerPageView*>(one)->getContainer(); })
		== children.end())
		m_otherlistview->pushBackCustomItem(ContainerPageView::create(target));
	
}
//检测周围容器
void BackPackView::checkContainer(float dt){
	//检测是否添加感应容器
	auto player = GameManager::getInstance()->getPlayer();
	auto percetion = static_cast<PlayerPerception*>(player->getPerception());
	//检测掉落物
	for (auto i : percetion->getDropTargets())
		addTargetAsView(i);
	//检测容器
	for (auto i : percetion->getContainerTargets())
		addTargetAsView(i);
	

	//在其它容器页
	auto children = m_otherlistview->getItems();
 	//检测是否失去感应容器
	for (auto i = 0; i < children.size(); ++i) {
		auto ipv = static_cast<ContainerPageView*>(children.at(i));
		//若离玩家距离很远，则能丢失容器的感应
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
		//如果找到了则删除
		if (ipv->getContainer() == r) {
			m_otherlistview->removeItem(i); 
			ItemPageView::s_itempageview_list.remove(ipv);
			return; 
		}
	}
	//没找到则ASSERT
	CC_ASSERT("BackPackView dosen't have such a Container to be deleted!");
}