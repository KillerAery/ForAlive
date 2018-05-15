#include "StartScene.h"
#include "GameScene.h"
#include "GameTool.h"
#include "SceneManager.h"

using cocos2d::Point;
using cocos2d::Vec2;


using namespace cocos2d;//CSLoaderλ��cocos2d�����ռ䡣
using namespace cocos2d::ui;
using namespace cocostudio::timeline;


StartScene::StartScene():m_onDealingLayer(nullptr){}

//��������
Scene* StartScene::createScene() {
	auto scene = Scene::create();
	auto layer = StartScene::create();
	scene->addChild(layer);
	return scene;
}
//������ʼ��
bool StartScene::init() {
	if (!Layer::init())return false;

	//���볡��UI.csb�ļ�
	auto UI = CSLoader::createNode("UI/MainScene.csb");
	this->addChild(UI);

	//���ض���
	ActionTimeline *action = CSLoader::createTimeline("UI/MainScene.csb");
	//���Ŷ���
	action->gotoFrameAndPlay(0, 3200, true);//�ӵ�0֡��3200֡ѭ������
	UI->runAction(action);
	//��������
	GameTool::getInstance()->setIfBGM(true);
	//GameTool::getInstance()->playBGM("Music/rain.mp3");
	//GameTool::getInstance()->playBGM("Music/shot.mp3");
	GameTool::getInstance()->fadePlayBGMandCloseOtherBGM("Music/Astral Requiem.mp3");

	//UI�ؼ�����
	//��ʼ��Ϸ ������Ϸ �˳�
	initStartContinueExit(UI);
	//��������
	initSetting(UI);
	//����
	initAbout(UI);

	return true;
}
//��������
void StartScene::initAbout(Node* UI) {
	//�������� ҳ��
	PageView* layout_about = dynamic_cast<PageView*>(UI->getChildByTag(31));

	//�������� ҳ�� �˳���ť
	Button* btn_about_1 = dynamic_cast<Button*>(layout_about->getChildByTag(32)->getChildByTag(35));
	btn_about_1->addClickEventListener(([layout_about](Ref* Pesender) {layout_about->setVisible(false); }));
	
	//�������� ��ť
	Button* btn_about = dynamic_cast<Button*>(UI->getChildByTag(19));
	btn_about->addClickEventListener([layout_about, this](Ref* Pesender) {
		if (m_onDealingLayer)m_onDealingLayer->setVisible(false); layout_about->setVisible(true); m_onDealingLayer = layout_about; });}//������ڴ��� ĳ����ҳ�� ���ر�֮���� �������� ��Ϊ ���ڴ����ҳ��

//����
void StartScene::initSetting(Node* UI) {
	//���� ҳ��
	Layout * layout_setting = dynamic_cast<Layout*>(UI->getChildByTag(41));
	//���� ҳ�� �˳���ť
	Button* btn_setting_exit = dynamic_cast<Button*>(UI->getChildByTag(41)->getChildByTag(42));
	btn_setting_exit->addClickEventListener(([layout_setting](Ref* Pesender) {layout_setting->setVisible(false); }));
	//���� ��ť
	Button* btn_setting = dynamic_cast<Button*>(UI->getChildByTag(20));
	btn_setting->addClickEventListener([layout_setting,this](Ref* Pesender)
	{if (m_onDealingLayer)m_onDealingLayer->setVisible(false); layout_setting->setVisible(true); m_onDealingLayer = layout_setting; });//������ڴ��� ĳ����ҳ�� ���ر�֮���� ���� ��Ϊ ���ڴ����ҳ��

	//���� ҳ�� �������� ��ѡ��
	CheckBox* ckb_setting_BGM = dynamic_cast<CheckBox*>(UI->getChildByTag(41)->getChildByTag(51));
	ckb_setting_BGM->addEventListener([](Ref* pSender, CheckBox::EventType type) {
		if (type == CheckBox::EventType::SELECTED)GameTool::getInstance()->setIfBGM(true);
		else if (type == CheckBox::EventType::UNSELECTED)GameTool::getInstance()->setIfBGM(false);
	}
	);
	//���� ҳ�� ��Ч ��ѡ��
	CheckBox* ckb_setting_Effect = dynamic_cast<CheckBox*>(UI->getChildByTag(41)->getChildByTag(52));
	ckb_setting_Effect->addEventListener([](Ref* pSender, CheckBox::EventType type) {
		if (type == CheckBox::EventType::SELECTED)GameTool::getInstance()->setIfEffect(true);
		else if (type == CheckBox::EventType::UNSELECTED)GameTool::getInstance()->setIfEffect(false);
	});



}

//��ʼ��Ϸ ������Ϸ �˳�
void StartScene::initStartContinueExit(Node* UI) {

	//��ʼ��ť
	do {
		Button* btn_strat = dynamic_cast<Button*>(UI->getChildByTag(15));
		btn_strat->addClickEventListener([](Ref* Pesender) {SceneManager::getInstance()->loadGameScene(); });
	} while (0);


	//������Ϸ��ť
	do {
		Button* btn_strat = dynamic_cast<Button*>(UI->getChildByTag(16));
		btn_strat->setEnabled(false);
		btn_strat->addClickEventListener([](Ref* Pesender) {
			//Director::getInstance()->replaceScene(GameScene::createScene()); 
		});
	} while (0);

	//�رհ�ť
	do {
		/*
		�˳���ť
		�˴�û�ṩios�رշ���

		#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
		#endif

		*/
		Button* btn_exit = dynamic_cast<Button*>(UI->getChildByTag(14));
		btn_exit->addClickEventListener([](Ref* Pesender) {Director::getInstance()->end(); });
	} while (0);
}

