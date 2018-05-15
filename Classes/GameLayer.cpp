#pragma once
#include <vector>
#include "GameLayer.h"
#include "CacheManager.h"
#include "GamePauseUtils.h"
#include "GameManager.h"

#include "RelationShipManager.h"
#include "PlayerPerception.h"
#include "AIManager.h"
#include "Logger.h"
#include "TriggerManager.h"
#include "BattleTimer.h"
#include "EndingManager.h"

//TEST
#include "KaguyaHelper.h"

using cocos2d::Size;
using cocos2d::ValueMap;
using cocos2d::Director; 
using cocos2d::NotificationCenter;

GameLayer::GameLayer() :m_tmxmap(nullptr), m_physcisworld(nullptr),m_wallcheckLayer(nullptr),m_groundLayer(nullptr){}

GameLayer::~GameLayer() {
	NotificationCenter::getInstance()->removeObserver(this, "NPC_CREATE");
	NotificationCenter::getInstance()->removeObserver(this, "ENTITY_CREATE");
	NotificationCenter::getInstance()->removeObserver(this, "PLAYER_CREATE");
	NotificationCenter::getInstance()->removeObserver(this, "CONTAINER_CREATE");
	NotificationCenter::getInstance()->removeObserver(this, "DROP_CREATE");
	NotificationCenter::getInstance()->removeObserver(this, "RESUMEGAME");
	NotificationCenter::getInstance()->removeObserver(this, "PAUSEGAME");
	//TODO
	//待优化
	AIManager::deleteInstance();
	GameManager::deleteInstance();
	RelationShipManager::deleteInstance();
	KaguyaHelper::deleteInstance();
	DialogBoxManager::deleteInstance();
	RelationShipManager::deleteInstance();
	MissionManager::deleteInstance();
	TriggerManager::deleteInstance();
	ItemDataBase::deleteInstance();
	DialogBoxUITemlate::deleteInstance();
	BattleTimer::deleteInstance();
	Logger::clean();
}

bool GameLayer::init(const std::string& tmxfilename) {
	if (!Layer::init())return false;
	initMap(tmxfilename);
	initPhysicsWorld();
	initEntities();
	initContainers();
	initNPCs();
	initPlayer();

	//待扩展，先加载一定缓存
	CacheManager::getInstance();

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameLayer::addNPC), "NPC_CREATE", nullptr);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameLayer::addEntity), "ENTITY_CREATE", nullptr);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameLayer::addPlayer), "PLAYER_CREATE", nullptr);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameLayer::addContainer), "CONTAINER_CREATE", nullptr);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameLayer::addDrop), "DROP_CREATE", nullptr);


	//锁定视角
	this->schedule(schedule_selector(GameLayer::LockView));

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameLayer::resumeGame), "RESUMEGAME", nullptr);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameLayer::pauseGame), "PAUSEGAME", nullptr);

	//TEST
	//AI脚本在INIT函数里读取
	auto i = KaguyaHelper::getInstance();

	return true;
}

//初始化TMX地图 
void GameLayer::initMap(const std::string& tmxfilename) {
	m_tmxmap = TMXTiledMap::create(tmxfilename);
	//断言存在地图
	CCASSERT(m_tmxmap, "M_TMXMAP = NULLPTR!!");
	this->addChild(m_tmxmap);
	//获取检测墙的层
	m_wallcheckLayer =  m_tmxmap->getLayer("wallcheck");
	m_wallcheckLayer->setVisible(false);
	//获取地面层
	m_groundLayer = m_tmxmap->getLayer("ground");
	//获取墙的层
	for (int i = 1; i <= 4; ++i) {
		auto layer = m_tmxmap->getLayer("wall"+cocos2d::StringUtils::toString(i));
		//layer->setOpacity(10);
		m_wallLayers.push_back(layer);
	}
	//记录障碍组
	this->recordBarrierVec();
	//记录地图总大小
	this->recordMapSize();
}
//初始化物理世界
void GameLayer::initPhysicsWorld() {
	Size size = m_tmxmap->getContentSize();
	//物理管理器
	m_physcisworld = PhysicsWorld::create(size);

	this->addChild(m_physcisworld);
}
//初始化实体
void GameLayer::initEntities() {
	//从地图获得obj_wall层
	TMXObjectGroup *obj_wall = m_tmxmap->getObjectGroup("obj_wall");
	//断言存在obj_wall层 
	CCASSERT(obj_wall, "OBJ_WALL = NULLPTR!");
	auto objects = obj_wall->getObjects();
	//创造墙体不需要返还对象
	Entity::createWall(objects);
}
//初始化容器
void GameLayer::initContainers() {
	//从地图获得obj_container层
	TMXObjectGroup *obj_contaier = m_tmxmap->getObjectGroup("obj_container");
	//断言存在obj_container层
	CCASSERT(obj_contaier, "OBJ_CONTAINER = NULLPTR!");
	//从container层获得各对象
	for (auto obj : obj_contaier->getObjects()) {
		//获得属性
		auto valuemap = obj.asValueMap();
		//创建container
		auto c = Container::create(valuemap);
		this->addContainer(c);
	}
}
//初始化NPC
void GameLayer::initNPCs() {
	//从地图获得obj_NPC层
	TMXObjectGroup *obj_NPC = m_tmxmap->getObjectGroup("obj_NPC");
	//断言存在obj_NPC层 
	CCASSERT(obj_NPC, "OBJ_NPC = NULLPTR!");
	//从obj_NPC层获得各对象
	for (auto obj : obj_NPC->getObjects())
	{	//获得对象属性
		auto valuemap = obj.asValueMap();
		//创建NPC
		auto npc = NPC::create(valuemap);
		//主层 添加 NPC
		this->addNPC(npc);
		//暂时在此处处理AI
		switch (npc->getBiologyTpye())
		{
		case BiologyTpye::zombie:
			do {
				auto root = AIManager::getInstance()->createZombieAI();
				AIManager::getInstance()->bindAIonNPC(root, npc);
				RelationShipManager::getInstance()->bindRelationshipOnNPC(RelationShipManager::getInstance()->createZombieRelationship(),npc);
				npc->setPerception(Perception::create(npc));
			} while (0);
			break;
		case BiologyTpye::human:
			do {
				RelationShipManager::getInstance()->bindRelationshipOnNPC(RelationShipManager::getInstance()->createHumanRelationship(), npc);
				npc->setPerception(HumanPerception::create(npc));
			} while (0);
			break;
		}
	}
}

//初始化玩家
void GameLayer::initPlayer() {
	//从地图获得玩家层
	TMXObjectGroup *obj_player = m_tmxmap->getObjectGroup("obj_player");
	CCASSERT(obj_player, "OBJ_PLAYER = NULLPTR!");
	//从玩家层获得属性
	ValueMap valuemap = obj_player->getObject("Player");
	//创建玩家
	auto player = Player::create(valuemap);

	player->setPerception(PlayerPerception::create(player));
	RelationShipManager::getInstance()->bindRelationshipOnNPC(RelationShipManager::getInstance()->createHumanRelationship(), player);

	//主层 添加 玩家
	this->addPlayer(player);
}

//记录障碍组
void GameLayer::recordBarrierVec(){
	//获取障碍层 并记录所有障碍点
	auto barrierLayer = m_tmxmap->getLayer("barrier");
	for (int x = 0; x < m_tmxmap->getTileSize().width; ++x)
		for (int y = 0; y < m_tmxmap->getTileSize().height; ++y)
		{
			auto GID = barrierLayer->getTileGIDAt(Vec2(x, y));
			auto tileProperties = m_tmxmap->getPropertiesForGID(GID);
			//如果是墙检测层
			if (!tileProperties.isNull()) {
				auto groundcheck = tileProperties.asValueMap();
				if (groundcheck.at("wallcheck").asString() == "true")
					//GameManager来记录
					GameManager::getInstance()->pushBarrierPoint(x,99-y);
			}
		}
	barrierLayer->setVisible(false);
}
//记录地图大小
void GameLayer::recordMapSize() {
	auto mapsize = Size(m_tmxmap->getMapSize().width*m_tmxmap->getTileSize().width, m_tmxmap->getMapSize().height*m_tmxmap->getTileSize().height);
	GameManager::getInstance()->setMapSize(mapsize);
	GameManager::getInstance()->setTiles(m_tmxmap->getMapSize());
	GameManager::getInstance()->setTileSize(m_tmxmap->getTileSize());
}

GameLayer* GameLayer::create(const std::string& tmxname) {
	auto layer = new (std::nothrow) GameLayer();
	if (layer &&layer->init(tmxname)) { layer->autorelease();}
	else { delete layer; layer = nullptr;}
	return layer;
}
//暂停游戏
void GameLayer::pauseGame(Ref* r) {
	GamePauseUtils::getInstance()->operateAllSchedulerAndActions(this, PauseTpye::PAUSE);
}
//恢复游戏
void GameLayer::resumeGame(Ref* r) {
	GamePauseUtils::getInstance()->operateAllSchedulerAndActions(this, PauseTpye::RESUME);
}

//获得玩家在瓦片的位置
Vec2 GameLayer::getTilepos(const Vec2 & playerPos) {
	auto tilePos = Vec2(playerPos.x / m_tmxmap->getTileSize().width,
		(GameManager::getInstance()->getMapSize().height - playerPos.y) / m_tmxmap->getTileSize().height);
	if (tilePos.y <= 0)tilePos.y = 0;
	else if (tilePos.y >= m_tmxmap->getMapSize().height)tilePos.y = m_tmxmap->getMapSize().height - 1;
	if (tilePos.x <= 0)tilePos.x = 0;
	else if (tilePos.x >= m_tmxmap->getMapSize().width)tilePos.x = m_tmxmap->getMapSize().width - 1;
	return tilePos;
}

//锁定实体视角
//处理房屋遮掩
void GameLayer::LockView(float dt) {
	auto player = GameManager::getInstance()->getPlayer();
	if (!player)return;
	//判断玩家是否走出小镇
	if (player->getPositionY() <= 0)
	{
		EndingManager::getInstance()->intoAliveEnding();
	}
		

	auto screensize = cocos2d::Director::getInstance()->getVisibleSize();
	auto mapsizeX = GameManager::getInstance()->getMapSize().width;
	auto mapsizeY = GameManager::getInstance()->getMapSize().height;
	//让地图动起来
	//判断Y轴移动方向
	if (player->getPositionY() + screensize.height / 2 >= mapsizeY)setPositionY(screensize.height - mapsizeY);
	else if (player->getPositionY() - screensize.height / 2 <= 0)setPositionY(0);
	else setPositionY(-player->getPositionY() + screensize.height / 2);
	//判断X轴移动方向
	if (player->getPositionX() + screensize.width / 2 >= mapsizeX)setPositionX(screensize.width - mapsizeX);
	else if (player->getPositionX() - screensize.width / 2 <= 0)setPositionX(0);
	else setPositionX(-player->getPositionX() + screensize.width / 2);
	//获得玩家在tile的点
	auto tilePos = getTilepos(player->getPosition());
	//判断房子是否需要遮掩
	auto tileGID = m_wallcheckLayer->getTileGIDAt(tilePos);
	auto tileProperties = m_tmxmap->getPropertiesForGID(tileGID);
	//如果是墙检测层
	if (!tileProperties.isNull()) {
		auto groundcheck = tileProperties.asValueMap();
		if (groundcheck.at("wallcheck").asString()=="true")
		hideWallLayer();
	}
	else showWallLayer();
}

//隐藏墙体层
void GameLayer::hideWallLayer() {
	for (auto layer : m_wallLayers)
		layer->setVisible(false);
}
//显示墙体层
void GameLayer::showWallLayer() {
	for (auto layer : m_wallLayers)
		layer->setVisible(true);
}

//添加容器
void GameLayer::addContainer(Ref* r) {
	addContainer(static_cast<Container*>(r));
}
//添加容器
void GameLayer::addContainer(Container* c) {
	//注册容器
	GameManager::getInstance()->registerContainer(c);
	//主层 添加 Container
	this->addChild(c);
}

//添加实体
void GameLayer::addEntity(Ref* r) {
	addContainer(static_cast<Entity*>(r));
}
//添加实体
void GameLayer::addEntity(Entity* e) {
	//主层 添加 Entity
	this->addChild(e);
}
//添加玩家
void GameLayer::addPlayer(Ref* r) {
	addContainer(static_cast<Player*>(r));
}
//添加玩家
void GameLayer::addPlayer(Player* p) {
	//注册生物
	addBiology(p);
	//设置全局变量——玩家
	GameManager::getInstance()->setPlayer(p);
	//观察 各实体 移动，锁定玩家视角
	this->schedule(schedule_selector(GameLayer::LockView));
}
//添加NPC
void GameLayer::addNPC(Ref* r) {
	addContainer(static_cast<NPC*>(r));
}
//添加NPC
void GameLayer::addNPC(NPC* n) {
	addBiology(n);
}
//添加生物
void GameLayer::addBiology(Biology* b){
	//注册容器
	GameManager::getInstance()->registerContainer(b);
	//注册生物
	GameManager::getInstance()->registerBiology(b);
	//主层 添加 Container
	this->addChild(b);
}

void GameLayer::addDrop(Ref* r) {
	addDrop(static_cast<Drop*>(r));
}

void GameLayer::addDrop(Drop* d) {
	//注册掉落物
	GameManager::getInstance()->registerDrop(d);
	//主层 添加 drop
	this->addChild(d);
}

