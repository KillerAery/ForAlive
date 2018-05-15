#include "GameScene.h"
#include "GameTool.h"

using namespace cocos2d;

GameScene::GameScene():m_mainlayer(nullptr),m_UIlayer(nullptr){}
GameScene::~GameScene(){}

//场景创建
Scene* GameScene::createScene() {
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init() {
	if (!Layer::init())return false;
	//设置 2D正交投影
	cocos2d::Director::getInstance()->setProjection(cocos2d::Director::Projection::_2D);
	//设置 深度测试
	cocos2d::Director::getInstance()->setDepthTest(true);
	//主层
	this->initMainLayer();
	//UI层
	this->initUILayer(m_mainlayer);

	GameTool::getInstance()->fadePlayBGMandCloseOtherBGM("Music/Jeremy Soule - Tundra.mp3");
	GameTool::getInstance()->playEnviromentBGM("Music/Gordon Hempton - Juniperwind.mp3");

	return true;
}

//初始化主层
void GameScene::initMainLayer() {
	//创建主层
	m_mainlayer = GameLayer::create(cocos2d::FileUtils::getInstance()->fullPathForFilename("GameScene/test.tmx"));
	GameManager::getInstance()->setGameLayer(m_mainlayer);
	//游戏场景 添加 主层
	this->addChild(m_mainlayer);
}

//初始化UI层
void GameScene::initUILayer(GameLayer* mainlayer){
	//创建UI层
	m_UIlayer = GameUILayer::create(mainlayer);
	//游戏场景 添加 UI层
	this->addChild(m_UIlayer);
}

void  GameScene::onExit(){
	Layer::onExit();
	//还原 投影
	cocos2d::Director::getInstance()->setProjection(cocos2d::Director::Projection::DEFAULT);
	//还原 深度测试
	cocos2d::Director::getInstance()->setDepthTest(false);
}