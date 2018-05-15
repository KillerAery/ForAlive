#include "SceneManager.h"
#include "StartScene.h"
#include "GameScene.h"

using namespace cocos2d;

SceneManager::SceneManager() {
}

bool SceneManager::init(){
	if (!Node::init())return false;

	Node::onEnter();
	Node::onEnterTransitionDidFinish();

	return true;
}

void SceneManager::loadStartScene() {
	Director::getInstance()->replaceScene(TransitionFade::create(3.0f,StartScene::createScene()));
}

void SceneManager::loadGameScene(){
	Director::getInstance()->replaceScene(TransitionFade::create(3.0f,GameScene::createScene()));
}

void SceneManager::loadScene(Scene* scene) {
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f,scene));
}

void SceneManager::firstLoadStartScene(){
	this->scheduleOnce([this](float dt) {this->loadStartScene(); }, 5.0f, "firstLoadStartScene");
}