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
	//���Ż�
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

	//����չ���ȼ���һ������
	CacheManager::getInstance();

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameLayer::addNPC), "NPC_CREATE", nullptr);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameLayer::addEntity), "ENTITY_CREATE", nullptr);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameLayer::addPlayer), "PLAYER_CREATE", nullptr);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameLayer::addContainer), "CONTAINER_CREATE", nullptr);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameLayer::addDrop), "DROP_CREATE", nullptr);


	//�����ӽ�
	this->schedule(schedule_selector(GameLayer::LockView));

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameLayer::resumeGame), "RESUMEGAME", nullptr);
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameLayer::pauseGame), "PAUSEGAME", nullptr);

	//TEST
	//AI�ű���INIT�������ȡ
	auto i = KaguyaHelper::getInstance();

	return true;
}

//��ʼ��TMX��ͼ 
void GameLayer::initMap(const std::string& tmxfilename) {
	m_tmxmap = TMXTiledMap::create(tmxfilename);
	//���Դ��ڵ�ͼ
	CCASSERT(m_tmxmap, "M_TMXMAP = NULLPTR!!");
	this->addChild(m_tmxmap);
	//��ȡ���ǽ�Ĳ�
	m_wallcheckLayer =  m_tmxmap->getLayer("wallcheck");
	m_wallcheckLayer->setVisible(false);
	//��ȡ�����
	m_groundLayer = m_tmxmap->getLayer("ground");
	//��ȡǽ�Ĳ�
	for (int i = 1; i <= 4; ++i) {
		auto layer = m_tmxmap->getLayer("wall"+cocos2d::StringUtils::toString(i));
		//layer->setOpacity(10);
		m_wallLayers.push_back(layer);
	}
	//��¼�ϰ���
	this->recordBarrierVec();
	//��¼��ͼ�ܴ�С
	this->recordMapSize();
}
//��ʼ����������
void GameLayer::initPhysicsWorld() {
	Size size = m_tmxmap->getContentSize();
	//���������
	m_physcisworld = PhysicsWorld::create(size);

	this->addChild(m_physcisworld);
}
//��ʼ��ʵ��
void GameLayer::initEntities() {
	//�ӵ�ͼ���obj_wall��
	TMXObjectGroup *obj_wall = m_tmxmap->getObjectGroup("obj_wall");
	//���Դ���obj_wall�� 
	CCASSERT(obj_wall, "OBJ_WALL = NULLPTR!");
	auto objects = obj_wall->getObjects();
	//����ǽ�岻��Ҫ��������
	Entity::createWall(objects);
}
//��ʼ������
void GameLayer::initContainers() {
	//�ӵ�ͼ���obj_container��
	TMXObjectGroup *obj_contaier = m_tmxmap->getObjectGroup("obj_container");
	//���Դ���obj_container��
	CCASSERT(obj_contaier, "OBJ_CONTAINER = NULLPTR!");
	//��container���ø�����
	for (auto obj : obj_contaier->getObjects()) {
		//�������
		auto valuemap = obj.asValueMap();
		//����container
		auto c = Container::create(valuemap);
		this->addContainer(c);
	}
}
//��ʼ��NPC
void GameLayer::initNPCs() {
	//�ӵ�ͼ���obj_NPC��
	TMXObjectGroup *obj_NPC = m_tmxmap->getObjectGroup("obj_NPC");
	//���Դ���obj_NPC�� 
	CCASSERT(obj_NPC, "OBJ_NPC = NULLPTR!");
	//��obj_NPC���ø�����
	for (auto obj : obj_NPC->getObjects())
	{	//��ö�������
		auto valuemap = obj.asValueMap();
		//����NPC
		auto npc = NPC::create(valuemap);
		//���� ��� NPC
		this->addNPC(npc);
		//��ʱ�ڴ˴�����AI
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

//��ʼ�����
void GameLayer::initPlayer() {
	//�ӵ�ͼ�����Ҳ�
	TMXObjectGroup *obj_player = m_tmxmap->getObjectGroup("obj_player");
	CCASSERT(obj_player, "OBJ_PLAYER = NULLPTR!");
	//����Ҳ�������
	ValueMap valuemap = obj_player->getObject("Player");
	//�������
	auto player = Player::create(valuemap);

	player->setPerception(PlayerPerception::create(player));
	RelationShipManager::getInstance()->bindRelationshipOnNPC(RelationShipManager::getInstance()->createHumanRelationship(), player);

	//���� ��� ���
	this->addPlayer(player);
}

//��¼�ϰ���
void GameLayer::recordBarrierVec(){
	//��ȡ�ϰ��� ����¼�����ϰ���
	auto barrierLayer = m_tmxmap->getLayer("barrier");
	for (int x = 0; x < m_tmxmap->getTileSize().width; ++x)
		for (int y = 0; y < m_tmxmap->getTileSize().height; ++y)
		{
			auto GID = barrierLayer->getTileGIDAt(Vec2(x, y));
			auto tileProperties = m_tmxmap->getPropertiesForGID(GID);
			//�����ǽ����
			if (!tileProperties.isNull()) {
				auto groundcheck = tileProperties.asValueMap();
				if (groundcheck.at("wallcheck").asString() == "true")
					//GameManager����¼
					GameManager::getInstance()->pushBarrierPoint(x,99-y);
			}
		}
	barrierLayer->setVisible(false);
}
//��¼��ͼ��С
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
//��ͣ��Ϸ
void GameLayer::pauseGame(Ref* r) {
	GamePauseUtils::getInstance()->operateAllSchedulerAndActions(this, PauseTpye::PAUSE);
}
//�ָ���Ϸ
void GameLayer::resumeGame(Ref* r) {
	GamePauseUtils::getInstance()->operateAllSchedulerAndActions(this, PauseTpye::RESUME);
}

//����������Ƭ��λ��
Vec2 GameLayer::getTilepos(const Vec2 & playerPos) {
	auto tilePos = Vec2(playerPos.x / m_tmxmap->getTileSize().width,
		(GameManager::getInstance()->getMapSize().height - playerPos.y) / m_tmxmap->getTileSize().height);
	if (tilePos.y <= 0)tilePos.y = 0;
	else if (tilePos.y >= m_tmxmap->getMapSize().height)tilePos.y = m_tmxmap->getMapSize().height - 1;
	if (tilePos.x <= 0)tilePos.x = 0;
	else if (tilePos.x >= m_tmxmap->getMapSize().width)tilePos.x = m_tmxmap->getMapSize().width - 1;
	return tilePos;
}

//����ʵ���ӽ�
//����������
void GameLayer::LockView(float dt) {
	auto player = GameManager::getInstance()->getPlayer();
	if (!player)return;
	//�ж�����Ƿ��߳�С��
	if (player->getPositionY() <= 0)
	{
		EndingManager::getInstance()->intoAliveEnding();
	}
		

	auto screensize = cocos2d::Director::getInstance()->getVisibleSize();
	auto mapsizeX = GameManager::getInstance()->getMapSize().width;
	auto mapsizeY = GameManager::getInstance()->getMapSize().height;
	//�õ�ͼ������
	//�ж�Y���ƶ�����
	if (player->getPositionY() + screensize.height / 2 >= mapsizeY)setPositionY(screensize.height - mapsizeY);
	else if (player->getPositionY() - screensize.height / 2 <= 0)setPositionY(0);
	else setPositionY(-player->getPositionY() + screensize.height / 2);
	//�ж�X���ƶ�����
	if (player->getPositionX() + screensize.width / 2 >= mapsizeX)setPositionX(screensize.width - mapsizeX);
	else if (player->getPositionX() - screensize.width / 2 <= 0)setPositionX(0);
	else setPositionX(-player->getPositionX() + screensize.width / 2);
	//��������tile�ĵ�
	auto tilePos = getTilepos(player->getPosition());
	//�жϷ����Ƿ���Ҫ����
	auto tileGID = m_wallcheckLayer->getTileGIDAt(tilePos);
	auto tileProperties = m_tmxmap->getPropertiesForGID(tileGID);
	//�����ǽ����
	if (!tileProperties.isNull()) {
		auto groundcheck = tileProperties.asValueMap();
		if (groundcheck.at("wallcheck").asString()=="true")
		hideWallLayer();
	}
	else showWallLayer();
}

//����ǽ���
void GameLayer::hideWallLayer() {
	for (auto layer : m_wallLayers)
		layer->setVisible(false);
}
//��ʾǽ���
void GameLayer::showWallLayer() {
	for (auto layer : m_wallLayers)
		layer->setVisible(true);
}

//�������
void GameLayer::addContainer(Ref* r) {
	addContainer(static_cast<Container*>(r));
}
//�������
void GameLayer::addContainer(Container* c) {
	//ע������
	GameManager::getInstance()->registerContainer(c);
	//���� ��� Container
	this->addChild(c);
}

//���ʵ��
void GameLayer::addEntity(Ref* r) {
	addContainer(static_cast<Entity*>(r));
}
//���ʵ��
void GameLayer::addEntity(Entity* e) {
	//���� ��� Entity
	this->addChild(e);
}
//������
void GameLayer::addPlayer(Ref* r) {
	addContainer(static_cast<Player*>(r));
}
//������
void GameLayer::addPlayer(Player* p) {
	//ע������
	addBiology(p);
	//����ȫ�ֱ����������
	GameManager::getInstance()->setPlayer(p);
	//�۲� ��ʵ�� �ƶ�����������ӽ�
	this->schedule(schedule_selector(GameLayer::LockView));
}
//���NPC
void GameLayer::addNPC(Ref* r) {
	addContainer(static_cast<NPC*>(r));
}
//���NPC
void GameLayer::addNPC(NPC* n) {
	addBiology(n);
}
//�������
void GameLayer::addBiology(Biology* b){
	//ע������
	GameManager::getInstance()->registerContainer(b);
	//ע������
	GameManager::getInstance()->registerBiology(b);
	//���� ��� Container
	this->addChild(b);
}

void GameLayer::addDrop(Ref* r) {
	addDrop(static_cast<Drop*>(r));
}

void GameLayer::addDrop(Drop* d) {
	//ע�������
	GameManager::getInstance()->registerDrop(d);
	//���� ��� drop
	this->addChild(d);
}

