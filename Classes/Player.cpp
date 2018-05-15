#include "Player.h"
#include "TriggerManager.h"
#include "EndingManager.h"

using cocos2d::Vec2; 
using cocos2d::NotificationCenter;
using cocos2d::Director;

Player::Player():m_target(nullptr){}
Player::~Player(){}
void Player::removeFromScene() {
	//玩家死亡，关闭所有控制玩家的组件
	NotificationCenter::getInstance()->postNotification("PLAYER_DIE", this);
	Biology::removeFromScene();
	EndingManager::getInstance()->intoDeadEnding();
}

bool Player::init(ValueMap& obj_valuemap) {
	if (!Biology::init(obj_valuemap))return false;
	return true;
}

Player* Player::create(ValueMap& obj_valuemap) {
	obj_valuemap.insert(ValueMap::value_type("entitytpye", Value(int(EntityTpye::biology))));
	auto player = new (std::nothrow)Player();
	if (player&&player->init(obj_valuemap)) { player->autorelease(); }
	else CC_SAFE_DELETE(player);

	return player;
}

//触发器检测
void Player::checkTrigger(int id, int num) {
	TriggerManager::getInstance()->checkGetTrigger(id,num);
}
