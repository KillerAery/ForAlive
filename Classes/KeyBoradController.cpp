#include "KeyBoradController.h"
#include "MissionManager.h"

using cocos2d::EventListenerTouchOneByOne;
using cocos2d::EventListenerMouse;
using cocos2d::EventListenerKeyboard;
using cocos2d::NotificationCenter;
using cocos2d::EventMouse;
using cocos2d::Event;
using cocos2d::Touch;
using cocos2d::Rect;
using cocos2d::EventKeyboard;

KeyBoradController::KeyBoradController() :m_player(nullptr), m_up(0), m_down(0), m_right(0), m_left(0), r_backpackview(nullptr),r_missionView(nullptr),m_EKeyDown(0){}

KeyBoradController::~KeyBoradController() {}
bool KeyBoradController::init() {
	if (!Node::init())return false;

	initKeyBoardListener();

	this->scheduleUpdate();

	return true;
}

//绑定玩家
bool KeyBoradController::bindPlayer(Player* p) {
	CCASSERT(p, "NO PLAYER WERE BINDED BY MOVECONTROLLER!");
	m_player = p;
	return true;
}

void KeyBoradController::bindBackPackView(BackPackView* b) {
	r_backpackview = b;
}

void KeyBoradController::bindMissionView(MissionView* m) {
	r_missionView = m;
}

//初始化Win32平台键盘监听
void KeyBoradController::initKeyBoardListener() {
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [this](EventKeyboard::KeyCode keycode, Event* event) {
		switch (keycode)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_W:
			m_up = 1;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_A:
			m_left = 1;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_S:
			m_down = 1;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_D:
			m_right = 1;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_E:
			if (m_EKeyDown == 0){
			m_EKeyDown = 1;
			m_player->pickupNearestDrop();
			m_player->setIfRequireToTalk(true);
			}
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_SHIFT:
			break;
		default:
			break;
		}
	};
	listener->onKeyReleased = [this](EventKeyboard::KeyCode keycode, Event* event) {
		switch (keycode)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_W:
			m_up = 0;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_A:
			m_left = 0;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_S:
			m_down = 0;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_D:
			m_right = 0;
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_E:
			m_EKeyDown = 0;
			m_player->setIfRequireToTalk(false);
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_SHIFT:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_1:
			m_player->setInHandIndex(LeftHandGear);
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_2:
			m_player->setInHandIndex(RightHandGear);
			break;

		case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE:
			r_backpackview->closeBackPack();
			r_missionView->closeMissionView();
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_TAB:
		case cocos2d::EventKeyboard::KeyCode::KEY_I:
			r_backpackview->openOrCloseBackPack(m_player);
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_J:
			r_missionView->openOrCloseMissionView();
			break;
		default:
			break;
		}
	};

	//绑定触摸到这个NODE上
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void KeyBoradController::update(float dt) {
	m_player->setVeclocity(Vec2(m_right - m_left, m_up - m_down).getNormalized()*m_player->getSpeed());
}


