#include "GameManager.h"
#include "GameLayer.h"

using cocos2d::Director;
using cocos2d::NotificationCenter;
using std::make_pair;

GameManager::GameManager() :m_player(nullptr), m_b2world(nullptr), m_mapSize(Size(0, 0)), m_playerPos(Vec2(0, 0)), r_gameLayer(nullptr){
	for (int i = 0; i < 50; i++)
		for (int j = 0; j < 100; j++)
			barrierMark[i][j] = true;
}

GameManager::~GameManager() {
	NotificationCenter::getInstance()->removeObserver(this, "CONTAINER_REMOVE");
	NotificationCenter::getInstance()->removeObserver(this, "BIOLOGY_REMOVE");
	NotificationCenter::getInstance()->removeObserver(this,"PLAYER_DIE");
	NotificationCenter::getInstance()->removeObserver(this, "DROP_REMOVE");
}

bool GameManager::init(){ 
	if (!Node::init())return false;
	initEventListener();
	return true; 
}

void GameManager::initEventListener(){
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameManager::removeContainer),"CONTAINER_REMOVE", nullptr);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameManager::removeBiology), "BIOLOGY_REMOVE", nullptr);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameManager::removePlayer),"PLAYER_DIE", nullptr);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameManager::removeDrop), "DROP_REMOVE", nullptr);
}

//注册容器
void GameManager::registerContainer(Container* c){
	//断言存在容器
	CCASSERT(c, "GameManager doesn't allow add nullptr!!!");
	m_containerMap.insert(make_pair(c->getID(),c));
}

//注册生物 
void GameManager::registerBiology(Biology* b) {
	//断言存在生物
	CCASSERT(b, "GameManager doesn't allow add nullptr!!!");
	m_biologyMap.insert(make_pair(b->getID(), b));
}
//注册掉落物
void GameManager::registerDrop(Drop* d) {
	//断言存在掉落物
	CCASSERT(d, "GameManager doesn't allow add nullptr!!!");
	m_dropList.push_back(d);
}

//移除掉落物
void GameManager::removeDrop(Ref* r) {
	auto d = static_cast<Drop*>(r);
	m_dropList.remove(d);
}

//移除容器
void GameManager::removeContainer(Ref* r){
	auto c = static_cast<Container*>(r);
	m_containerMap.erase(c->getID());
}

//移除生物 
void GameManager::removeBiology(Ref* r){
	auto b = static_cast<Biology*>(r);
	m_biologyMap.erase(b->getID());
}

void GameManager::removePlayer(Ref* r){
	CCASSERT(r == m_player, "GameManager::Player error!!");
	m_player = nullptr;
}

Biology* GameManager::findBiology(int id) {
	auto find_result = m_biologyMap.find(id);
	if (find_result == m_biologyMap.end())return nullptr;
	return find_result->second;
}

Container* GameManager::findContainer(int id) {
	auto find_result = m_containerMap.find(id);
	if (find_result == m_containerMap.end())return nullptr;
	return find_result->second;
}

//脚步音效
void GameManager::playFootEffect(const Vec2& pos) {
	//在tile的点
	auto tilePos = r_gameLayer->getTilepos(pos);
	//判断是否地面层
	auto tileGID = r_gameLayer->getGroundLayer()->getTileGIDAt(tilePos);
	auto tileProperties = r_gameLayer->getTMXMap()->getPropertiesForGID(tileGID);
	//如果是地面层
	if (!tileProperties.isNull()) {
		auto groundcheck = tileProperties.asValueMap();
		int num = groundcheck.at("Effect").asString().front() - '0';
		//a和b互相切换 生成类似Effect2a.mp3 Effect3b.mp3的字符串
		static char aOrb = 'a';
		aOrb = (aOrb == 'a' ? 'b' : 'a');

		string str = cocos2d::StringUtils::format("Music/Effect%d%c.mp3", num, aOrb);
		playEffect(str, pos);
	}
}

void GameManager::playEffect(const string& str, const Vec2& pos) {
	//如果存在玩家，则更新玩家位置
	if (m_player)m_playerPos = m_player->getPosition();

	auto distanceSq = m_playerPos.getDistanceSq(pos);
	//权重
	auto value = 100.0f / distanceSq;
	value = value >= 1.0f ? 1.0f : value;

	GameTool::getInstance()->playEffect(str, value);
}

//获得在瓦片的位置
Vec2 GameManager::getTilepos(const Vec2& pos)
{
	return r_gameLayer->getTilepos(pos);
}

