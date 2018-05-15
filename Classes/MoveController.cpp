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

�ƶ�������

********************************/

MoveController::MoveController() :m_frontpng(nullptr), m_backpng(nullptr), m_backradii(65), m_frontradii(20), m_player(nullptr),m_backpackview(nullptr){}

MoveController::~MoveController() {}

bool MoveController::init() {
	if (!Node::init())return false;
	//��ʼ��ͼƬ
	initPNG();
	initListener();
	this->scheduleUpdate();

	return true;
}

//��ʼ��ͼƬ
void MoveController::initPNG() {
	m_backpng = Sprite::create("/Controller/Controller_back.png");
	m_backpng->setPosition(Vec2(0, 0));
	this->addChild(m_backpng);
	m_frontpng = Sprite::create("/Controller/Controller_front.png");
	m_frontpng->setPosition(Vec2(0, 0));
	this->addChild(m_frontpng);
}

//��ʼ������������
void MoveController::initListener() {
	auto listener = EventListenerTouchOneByOne::create();
	//�Ƿ���û�¼������¼�
	listener->setSwallowTouches(true);
	//��һ�δ���ʱ 
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		//��ȡ������
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());

		//�жϴ������Ƿ��� ҡ��Բ�η�Χ��
		if (locationInNode.lengthSquared()> m_backradii*m_backradii) { return false; }

		judgePoint(locationInNode);

		m_frontpng->setPosition(locationInNode);
		return true;
	};
	//�����ƶ�ʱ
	listener->onTouchMoved = [this](Touch* touch, Event* event) {
		//��ȡ������
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		//�жϴ������Ƿ��� ҡ��Բ�η�Χ��

		if ((locationInNode.lengthSquared()) > m_backradii*m_backradii) {
			//��λ����*����
			//m_frontpng->setPosition(locationInNode.getNormalized()*m_backradii);
			locationInNode = locationInNode.getNormalized()*m_backradii;
		}
		judgePoint(locationInNode);
		m_frontpng->setPosition(locationInNode);

	};
	//��������ʱ ��λ
	listener->onTouchEnded = [this](Touch* touch, Event* event) {
		m_frontpng->setPosition(0, 0);
		m_player->setVeclocity(Vec2(0,0));
	};
	//�󶨴��������NODE��
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


}

//�жϷ���*����ٶȣ������һ���ٶ�ʸ��
void MoveController::judgePoint(Vec2 p) {
	m_player->setVeclocity(p / m_backradii * m_player->getSpeed());
}


//�����
bool MoveController::bindPlayer(Player* p) {
	CCASSERT(p, "NO PLAYER WERE BINDED BY MOVECONTROLLER!");
	m_player = p;
	return true;
}

void MoveController::bindBackPackView(BackPackView* b) {
	m_backpackview = b;
}

