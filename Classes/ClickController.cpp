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

����������

********************************/

ClickController::ClickController() :m_player(nullptr), m_png(nullptr), m_callfunc(nullptr) {}

ClickController::~ClickController(){}

bool ClickController::init() {
	if (!Node::init())return false;
	//��ʼ��ͼƬ
	initPNG();
	initListener();
	return true;
}

//��ʼ��ҡ��ͼƬ
void ClickController::initPNG() {
	m_png = Sprite::create("/Controller/Controller_front.png");
	m_png->setPosition(Vec2(0, 0));
	this->addChild(m_png);
}

//��ʼ��ҡ�˴���
void ClickController::initListener() {
	auto listener = EventListenerTouchOneByOne::create();
	//�Ƿ���û�¼������¼�
	listener->setSwallowTouches(true);
	//��һ�δ���ʱ 
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		//��û�а�callfunc�¼�����ʧ��
		if (!m_callfunc)return false;
		//��ȡ������
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());

		//�жϴ������Ƿ��� ҡ��Բ�η�Χ��
		//������ ����� callfunc�¼�
		if (locationInNode.lengthSquared() < m_png->getContentSize().width* m_png->getContentSize().height)
		{
			m_callfunc(m_player);
			m_png->setScale(1.2f);
			return true;
		}
		return false;
	};
	//�����ƶ�ʱ
	listener->onTouchMoved = [this](Touch* touch, Event* event) {
	};
	//��������ʱ ��λ
	listener->onTouchEnded = [this](Touch* touch, Event* event) {
		m_png->setScale(1.0f);
	};
	//�󶨴��������NODE��
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
