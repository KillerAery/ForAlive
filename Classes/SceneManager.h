#pragma once
#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "cocos2d.h"
#include "Singleton.h"

using cocos2d::Node;
using cocos2d::Scene;

class SceneManager:public Node, public Singleton<SceneManager> {
	SceneManager();
	friend Singleton<SceneManager>;
public:
	bool init();
	void loadStartScene();
	void loadGameScene();
	void loadScene(Scene* scene);
	void firstLoadStartScene();
};


#endif // !_SCENE_MANAGER_H_