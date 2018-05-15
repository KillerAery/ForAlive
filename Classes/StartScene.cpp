#include "StartScene.h"
#include "GameScene.h"
#include "GameTool.h"
#include "SceneManager.h"

using cocos2d::Point;
using cocos2d::Vec2;


using namespace cocos2d;//CSLoader位于cocos2d命名空间。
using namespace cocos2d::ui;
using namespace cocostudio::timeline;


StartScene::StartScene():m_onDealingLayer(nullptr){}

//场景创建
Scene* StartScene::createScene() {
	auto scene = Scene::create();
	auto layer = StartScene::create();
	scene->addChild(layer);
	return scene;
}
//场景初始化
bool StartScene::init() {
	if (!Layer::init())return false;

	//读入场景UI.csb文件
	auto UI = CSLoader::createNode("UI/MainScene.csb");
	this->addChild(UI);

	//加载动画
	ActionTimeline *action = CSLoader::createTimeline("UI/MainScene.csb");
	//播放动画
	action->gotoFrameAndPlay(0, 3200, true);//从第0帧到3200帧循环播放
	UI->runAction(action);
	//播放音乐
	GameTool::getInstance()->setIfBGM(true);
	//GameTool::getInstance()->playBGM("Music/rain.mp3");
	//GameTool::getInstance()->playBGM("Music/shot.mp3");
	GameTool::getInstance()->fadePlayBGMandCloseOtherBGM("Music/Astral Requiem.mp3");

	//UI控件对象
	//开始游戏 继续游戏 退出
	initStartContinueExit(UI);
	//关于作者
	initSetting(UI);
	//设置
	initAbout(UI);

	return true;
}
//关于作者
void StartScene::initAbout(Node* UI) {
	//关于作者 页面
	PageView* layout_about = dynamic_cast<PageView*>(UI->getChildByTag(31));

	//关于作者 页面 退出按钮
	Button* btn_about_1 = dynamic_cast<Button*>(layout_about->getChildByTag(32)->getChildByTag(35));
	btn_about_1->addClickEventListener(([layout_about](Ref* Pesender) {layout_about->setVisible(false); }));
	
	//关于作者 按钮
	Button* btn_about = dynamic_cast<Button*>(UI->getChildByTag(19));
	btn_about->addClickEventListener([layout_about, this](Ref* Pesender) {
		if (m_onDealingLayer)m_onDealingLayer->setVisible(false); layout_about->setVisible(true); m_onDealingLayer = layout_about; });}//如果正在处理 某个层页面 ，关闭之；将 关于作者 作为 正在处理层页面

//设置
void StartScene::initSetting(Node* UI) {
	//设置 页面
	Layout * layout_setting = dynamic_cast<Layout*>(UI->getChildByTag(41));
	//设置 页面 退出按钮
	Button* btn_setting_exit = dynamic_cast<Button*>(UI->getChildByTag(41)->getChildByTag(42));
	btn_setting_exit->addClickEventListener(([layout_setting](Ref* Pesender) {layout_setting->setVisible(false); }));
	//设置 按钮
	Button* btn_setting = dynamic_cast<Button*>(UI->getChildByTag(20));
	btn_setting->addClickEventListener([layout_setting,this](Ref* Pesender)
	{if (m_onDealingLayer)m_onDealingLayer->setVisible(false); layout_setting->setVisible(true); m_onDealingLayer = layout_setting; });//如果正在处理 某个层页面 ，关闭之；将 设置 作为 正在处理层页面

	//设置 页面 背景音乐 复选框
	CheckBox* ckb_setting_BGM = dynamic_cast<CheckBox*>(UI->getChildByTag(41)->getChildByTag(51));
	ckb_setting_BGM->addEventListener([](Ref* pSender, CheckBox::EventType type) {
		if (type == CheckBox::EventType::SELECTED)GameTool::getInstance()->setIfBGM(true);
		else if (type == CheckBox::EventType::UNSELECTED)GameTool::getInstance()->setIfBGM(false);
	}
	);
	//设置 页面 音效 复选框
	CheckBox* ckb_setting_Effect = dynamic_cast<CheckBox*>(UI->getChildByTag(41)->getChildByTag(52));
	ckb_setting_Effect->addEventListener([](Ref* pSender, CheckBox::EventType type) {
		if (type == CheckBox::EventType::SELECTED)GameTool::getInstance()->setIfEffect(true);
		else if (type == CheckBox::EventType::UNSELECTED)GameTool::getInstance()->setIfEffect(false);
	});



}

//开始游戏 继续游戏 退出
void StartScene::initStartContinueExit(Node* UI) {

	//开始按钮
	do {
		Button* btn_strat = dynamic_cast<Button*>(UI->getChildByTag(15));
		btn_strat->addClickEventListener([](Ref* Pesender) {SceneManager::getInstance()->loadGameScene(); });
	} while (0);


	//继续游戏按钮
	do {
		Button* btn_strat = dynamic_cast<Button*>(UI->getChildByTag(16));
		btn_strat->setEnabled(false);
		btn_strat->addClickEventListener([](Ref* Pesender) {
			//Director::getInstance()->replaceScene(GameScene::createScene()); 
		});
	} while (0);

	//关闭按钮
	do {
		/*
		退出按钮
		此处没提供ios关闭方案

		#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
		#endif

		*/
		Button* btn_exit = dynamic_cast<Button*>(UI->getChildByTag(14));
		btn_exit->addClickEventListener([](Ref* Pesender) {Director::getInstance()->end(); });
	} while (0);
}

