#include "GameUILayer.h"

GameUILayer::GameUILayer():m_movecontroller(nullptr),m_backpackview(nullptr),m_missionView(nullptr),m_clickcontroller(nullptr),m_mousecontroller(nullptr),m_keyboradcontroller(nullptr),m_physicsTestButton(nullptr){}

GameUILayer::~GameUILayer(){
	NotificationCenter::getInstance()->removeObserver(this,"PLAYER_DIE");
}
//初始化UI层
bool GameUILayer::init(GameLayer* mainlayer) {
	if (!Layer::init())return false;
	initBackPackView();
	initMissionView();
	initController(mainlayer);
	initLogButton();
	//initButton(mainlayer);
	//监听玩家是否死亡,死亡则UI层关闭部分控制player的UI
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameUILayer::closeUIWithPlayer), "PLAYER_DIE", nullptr);

	return true;
}

//初始化控制器
void GameUILayer::initController(GameLayer* mainlayer) {
	auto player = GameManager::getInstance()->getPlayer();

	//移动控制器
	//m_movecontroller = MoveController::create();
	//m_movecontroller->setAnchorPoint(Vec2(0, 1));
	//m_movecontroller->setPosition(Vec2(100, 100));
	//m_movecontroller->setVisible(true);
	//m_movecontroller->bindBackPackView(m_backpackview);
	//this->addChild(m_movecontroller);

	//移动控制器
	m_keyboradcontroller = KeyBoradController::create();
	m_keyboradcontroller->bindPlayer(player);
	m_keyboradcontroller->bindBackPackView(m_backpackview);
	m_keyboradcontroller->bindMissionView(m_missionView);
	this->addChild(m_keyboradcontroller);

	//单击控制器
	//m_clickcontroller = ClickController::create(GameManager::getInstance()->getPlayer());
	//m_clickcontroller->setAnchorPoint(Vec2(0, 1));
	//m_clickcontroller->setPosition(Vec2(700, 100));
	//m_clickcontroller->bindCallBackEvent([](Player*p) {if (p->getTarget()){p->attack((p->getTarget()->getPosition() - p->getPosition()).getNormalized());}});
	//this->addChild(m_clickcontroller);

	//鼠标控制器
	m_mousecontroller = MouseController::create();
	m_mousecontroller->bindPlayer(player);
	m_mousecontroller->bindMap(mainlayer);
	
	this->addChild(m_mousecontroller);
}
//初始化日志按钮
void GameUILayer::initLogButton(){
	auto closeItem = cocos2d::MenuItemImage::create("GameScene/Log1.png","GameScene/Log2.png",
		[this](Ref* s) {m_missionView->openOrCloseMissionView(); });
	closeItem->setPosition(Vec2(50, 420));
	auto LogButton = cocos2d::Menu::create(closeItem, NULL);
	LogButton->setSwallowsTouches(true);
	LogButton->setPosition(Vec2::ZERO);
	this->addChild(LogButton);

	//提示按键J 图像
	auto Jsprite = Sprite::create("UI/png/ButtonJ.png");
	Jsprite->setPosition(closeItem->getPositionX() + closeItem->getContentSize().width / 2+ 20,closeItem->getPositionY());
	Jsprite->setScale(0.2f);
	this->addChild(Jsprite);

	m_mousecontroller->pushOtherUI(LogButton->getChildren().front());
}

//初始化背包界面
void GameUILayer::initBackPackView() {
	m_backpackview = BackPackView::create();
	m_backpackview->setVisible(false);
	this->addChild(m_backpackview);
}
//初始化任务界面
void GameUILayer::initMissionView(){
	m_missionView = MissionView::create();
	m_missionView->setVisible(false);
	MissionManager::getInstance()->setMissionView(m_missionView);
	this->addChild(m_missionView);
}
//初始化按钮
void GameUILayer::initButton(GameLayer* mainlayer) {
	//显示 物理引擎debug 按钮
	auto closeItem = cocos2d::MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		[this, mainlayer](Ref* s) {mainlayer->getTMXMap()->setVisible(!mainlayer->getTMXMap()->isVisible()); });
	closeItem->setPosition(Vec2(600, 400));
	m_physicsTestButton = cocos2d::Menu::create(closeItem, NULL);
	m_physicsTestButton->setSwallowsTouches(true);
	m_physicsTestButton->setPosition(Vec2::ZERO);
	this->addChild(m_physicsTestButton);

	m_mousecontroller->pushOtherUI(m_physicsTestButton->getChildren().front());
	////显示 人物背包 按钮
	//auto backpackItem = cocos2d::MenuItemImage::create(
	//	"CloseNormal.png",
	//	"CloseSelected.png",
	//	[this](Ref* s) {
	//	m_backpackview->setVisible(!m_backpackview->isVisible());
	//	m_backpackview->refreshItemPageView(nullptr);
	//});
	//backpackItem->setPosition(Vec2(750, 400));
	//auto backpackmenu = cocos2d::Menu::create(backpackItem, NULL);
	//backpackmenu->setPosition(Vec2::ZERO);
	//backpackmenu->setSwallowsTouches(true);
	//this->addChild(backpackmenu);
}

GameUILayer* GameUILayer::create(GameLayer* mainlayer) {
	auto layer = new (std::nothrow) GameUILayer();
	if (layer &&layer->init(mainlayer)) { layer->autorelease(); }
	else { delete layer; layer = nullptr; }
	return layer;
}

//关闭控制玩家的UI
void GameUILayer::closeUIWithPlayer(Ref* r) {
	if (m_missionView)m_missionView->removeFromParent();
	m_missionView = nullptr;
	//背包UI 
	if(m_backpackview)m_backpackview->removeFromParent();
	m_backpackview = nullptr;
	//各种控制器
	if(m_clickcontroller)m_clickcontroller->removeFromParent();
	m_clickcontroller = nullptr;
	if(m_movecontroller)m_movecontroller->removeFromParent();
	m_movecontroller = nullptr;
	if (m_mousecontroller)m_mousecontroller->removeFromParent();
	m_mousecontroller = nullptr;
	if (m_keyboradcontroller)m_keyboradcontroller->removeFromParent();
	m_keyboradcontroller = nullptr;
}