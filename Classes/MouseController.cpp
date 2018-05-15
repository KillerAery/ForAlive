#include "MouseController.h"

using cocos2d::EventListenerMouse;
using cocos2d::NotificationCenter;
using cocos2d::EventMouse;
using cocos2d::Event;
using cocos2d::Rect;

//初始化
void MouseController::initListener(){
	auto listener = EventListenerMouse::create();

	listener->onMouseDown = [this](Event* event) {
		EventMouse* e = (EventMouse*)event;
		//如果没有点到其他UI，
		if(!ifHaveOtherUI(Vec2(e->getCursorX(), e->getCursorY())))
		m_player->attack();
	};
	listener->onMouseMove = [this](Event* event) {
		EventMouse* e = (EventMouse*)event;
		m_player->setDirection((Vec2(e->getCursorX(), e->getCursorY()) - m_mainmap->getPosition() - m_player->getPosition()).getNormalized());
	};
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

MouseController::MouseController() :m_player(nullptr),m_mainmap(nullptr),m_shieldCount(0){}

MouseController::~MouseController() {
	NotificationCenter::getInstance()->removeObserver(this, "MOUSE_SHIELD");
	NotificationCenter::getInstance()->removeObserver(this, "MOUSE_UNSHIELD");
}

bool MouseController::init() {
	if (!Node::init())return false;
	initListener();
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(MouseController::shield), "MOUSE_SHIELD", nullptr);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(MouseController::unshield), "MOUSE_UNSHIELD", nullptr);
	return true;
}


//屏蔽
void MouseController::shield(Ref* r){
	m_shieldCount++;
	if (m_shieldCount >= 1) {
		this->setVisible(false);
		cocos2d::Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
	}

}

//取消屏蔽
void MouseController::unshield(Ref* r) {
	m_shieldCount--;
	if (m_shieldCount <= 0) {
		this->setVisible(true);
		cocos2d::Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this);
	}
}

//判定点位置有没有其它UI需要响应
bool MouseController::ifHaveOtherUI(const Vec2& point){
	for (auto ui : r_otherUIs){
		auto posInNode = ui->convertToNodeSpace(point);
		if(Rect(0,0, ui->getContentSize().width, ui->getContentSize().height).containsPoint(posInNode))return true;
	}
	return false;
}

void MouseController::pushOtherUI(Node* ui) {
	r_otherUIs.push_back(ui);
}