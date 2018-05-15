#include "MoveController.h"
#include "GameManager.h"

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

移动控制器

********************************/

MoveController::MoveController() :m_frontpng(nullptr), m_backpng(nullptr), m_backradii(65), m_frontradii(20), m_player(nullptr),m_backpackview(nullptr){}

MoveController::~MoveController() {}

bool MoveController::init() {
	if (!Node::init())return false;
	//初始化图片
	initPNG();
	initListener();
	this->scheduleUpdate();

	return true;
}

//初始化图片
void MoveController::initPNG() {
	m_backpng = Sprite::create("/Controller/Controller_back.png");
	m_backpng->setPosition(Vec2(0, 0));
	this->addChild(m_backpng);
	m_frontpng = Sprite::create("/Controller/Controller_front.png");
	m_frontpng->setPosition(Vec2(0, 0));
	this->addChild(m_frontpng);
}

//初始化触摸监听器
void MoveController::initListener() {
	auto listener = EventListenerTouchOneByOne::create();
	//是否吞没下级触摸事件
	listener->setSwallowTouches(true);
	//第一次触摸时 
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		//获取触摸点
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());

		//判断触摸点是否在 摇杆圆形范围内
		if (locationInNode.lengthSquared()> m_backradii*m_backradii) { return false; }

		judgePoint(locationInNode);

		m_frontpng->setPosition(locationInNode);
		return true;
	};
	//触摸移动时
	listener->onTouchMoved = [this](Touch* touch, Event* event) {
		//获取触摸点
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		//判断触摸点是否在 摇杆圆形范围内

		if ((locationInNode.lengthSquared()) > m_backradii*m_backradii) {
			//单位向量*长度
			//m_frontpng->setPosition(locationInNode.getNormalized()*m_backradii);
			locationInNode = locationInNode.getNormalized()*m_backradii;
		}
		judgePoint(locationInNode);
		m_frontpng->setPosition(locationInNode);

	};
	//触摸结束时 归位
	listener->onTouchEnded = [this](Touch* touch, Event* event) {
		m_frontpng->setPosition(0, 0);
		m_player->setVeclocity(Vec2(0,0));
	};
	//绑定触摸到这个NODE上
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


}

//判断方向*玩家速度，给玩家一个速度矢量
void MoveController::judgePoint(Vec2 p) {
	m_player->setVeclocity(p / m_backradii * m_player->getSpeed());
}


//绑定玩家
bool MoveController::bindPlayer(Player* p) {
	CCASSERT(p, "NO PLAYER WERE BINDED BY MOVECONTROLLER!");
	m_player = p;
	return true;
}

void MoveController::bindBackPackView(BackPackView* b) {
	m_backpackview = b;
}

