#ifndef _STARTSCENE_H_
#define _STARTSCENE_H_

#include "cocos2d.h"
#include "ui\CocosGUI.h"  //cocos studio  UI��
#include "cocostudio\CocoStudio.h" //cocos studio  UI��

using cocos2d::Scene;
using cocos2d::Layer;
using cocos2d::ui::Layout;



class StartScene :public Layer{
//��ʼ������
public:
	StartScene();
	virtual bool init();
	CREATE_FUNC(StartScene);
	static Scene* createScene();
private:
	Layout * m_onDealingLayer;
private:
	void initAbout(Node* UI);
	void initSetting(Node* UI);
	void initStartContinueExit(Node* UI);
};

#endif
