#include "EndingManager.h"
#include "SceneManager.h"

using cocos2d::ui::Layout;
using cocos2d::ui::Button;
using cocos2d::Layer;
using cocos2d::Node;
using cocos2d::Sprite;
using cocos2d::Label;

EndingManager::EndingManager():m_endingUI(nullptr){
}

bool EndingManager::init(){
	return true;
}


void EndingManager::loadUI() {
	//���뱳��UI.csb�ļ�
	m_endingUI = static_cast<Node*>(cocos2d::CSLoader::createNode("UI/EndingScene.csb"));
	//���ؿ�ʼ������ť
	auto button = static_cast<Button*>(m_endingUI->getChildByName("StartSceneButton"));
	button->addClickEventListener([](Ref*) {
		SceneManager::getInstance()->loadStartScene();
	});

	Scene* scene = Scene::create();
	scene->addChild(m_endingUI);

	SceneManager::getInstance()->loadScene(scene);
}

void EndingManager::intoDeadEnding() {
	loadUI();
	auto layout = static_cast<Layout*>(m_endingUI->getChildByName("AliveJounary"));
	layout->setVisible(false);
}

void EndingManager::intoAliveEnding() {
	loadUI();
}