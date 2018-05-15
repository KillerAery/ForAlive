#pragma once
#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
#include "GameLayer.h"
#include "GameUILayer.h"

using cocos2d::Scene;
using cocos2d::Layer;
using cocos2d::TMXTiledMap;


class GameScene:public Layer {
protected:
	CC_SYNTHESIZE(GameLayer*, m_mainlayer, MainLayer);
	CC_SYNTHESIZE(GameUILayer*, m_UIlayer, UILayer);
public:
	static Scene* createScene();
	//初始化部分
	GameScene();
	~GameScene();
	virtual bool init()override;
	virtual void onExit()override;
	CREATE_FUNC(GameScene);
	void initMainLayer();//初始化主层
	void initUILayer(GameLayer* mainlayer);//初始化UI层
};



#endif // !_GAMESCENE_H_
