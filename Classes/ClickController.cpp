#include "ClickController.h"


using cocos2d::EventListenerTouchOneByOne;
using cocos2d::EventListenerMouse;
using cocos2d::EventListenerKeyboard;
using cocos2d::NotificationCenter;
using cocos2d::EventMouse;
using cocos2d::Event;
using cocos2d::Touch;
using cocos2d::Rect;
using cocos2d::EventKeyboard;


/********************************

单击控制器

********************************/

ClickController::ClickController() :m_player(nullptr), m_png(nullptr), m_callfunc(nullptr) {}

ClickController::~ClickController(){}

bool ClickController::init() {
	if (!Node::init())return false;
	//初始化图片
	initPNG();
	initListener();
	return true;
}

//初始化摇杆图片
void ClickController::initPNG() {
	m_png = Sprite::create("/Controller/Controller_front.png");
	m_png->setPosition(Vec2(0, 0));
	this->addChild(m_png);
}

//初始化摇杆触摸
void ClickController::initListener() {
	auto listener = EventListenerTouchOneByOne::create();
	//是否吞没下级触摸事件
	listener->setSwallowTouches(true);
	//第一次触摸时 
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		//若没有绑定callfunc事件，则失败
		if (!m_callfunc)return false;
		//获取触摸点
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());

		//判断触摸点是否在 摇杆圆形范围内
		//若在内 则调用 callfunc事件
		if (locationInNode.lengthSquared() < m_png->getContentSize().width* m_png->getContentSize().height)
		{
			m_callfunc(m_player);
			m_png->setScale(1.2f);
			return true;
		}
		return false;
	};
	//触摸移动时
	listener->onTouchMoved = [this](Touch* touch, Event* event) {
	};
	//触摸结束时 归位
	listener->onTouchEnded = [this](Touch* touch, Event* event) {
		m_png->setScale(1.0f);
	};
	//绑定触摸到这个NODE上
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
