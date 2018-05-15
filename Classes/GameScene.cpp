#include "GameScene.h"
#include "GameTool.h"

using namespace cocos2d;

GameScene::GameScene():m_mainlayer(nullptr),m_UIlayer(nullptr){}
GameScene::~GameScene(){}

//��������
Scene* GameScene::createScene() {
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init() {
	if (!Layer::init())return false;
	//���� 2D����ͶӰ
	cocos2d::Director::getInstance()->setProjection(cocos2d::Director::Projection::_2D);
	//���� ��Ȳ���
	cocos2d::Director::getInstance()->setDepthTest(true);
	//����
	this->initMainLayer();
	//UI��
	this->initUILayer(m_mainlayer);

	GameTool::getInstance()->fadePlayBGMandCloseOtherBGM("Music/Jeremy Soule - Tundra.mp3");
	GameTool::getInstance()->playEnviromentBGM("Music/Gordon Hempton - Juniperwind.mp3");

	return true;
}

//��ʼ������
void GameScene::initMainLayer() {
	//��������
	m_mainlayer = GameLayer::create(cocos2d::FileUtils::getInstance()->fullPathForFilename("GameScene/test.tmx"));
	GameManager::getInstance()->setGameLayer(m_mainlayer);
	//��Ϸ���� ��� ����
	this->addChild(m_mainlayer);
}

//��ʼ��UI��
void GameScene::initUILayer(GameLayer* mainlayer){
	//����UI��
	m_UIlayer = GameUILayer::create(mainlayer);
	//��Ϸ���� ��� UI��
	this->addChild(m_UIlayer);
}

void  GameScene::onExit(){
	Layer::onExit();
	//��ԭ ͶӰ
	cocos2d::Director::getInstance()->setProjection(cocos2d::Director::Projection::DEFAULT);
	//��ԭ ��Ȳ���
	cocos2d::Director::getInstance()->setDepthTest(false);
}