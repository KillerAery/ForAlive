#pragma once
#ifndef EndingManager_h__
#define EndingManager_h__

#include "Singleton.h"
#include "cocos2d.h"
//cocos studio  UI库
#include "ui\CocosGUI.h"  
#include "cocostudio\CocoStudio.h" 

using cocos2d::Ref;
using cocos2d::Scene;
using cocos2d::Node;


//因为endingui过于简单，不做mvc分离
class EndingManager:public Ref,public Singleton<EndingManager>{
	EndingManager();
	friend Singleton<EndingManager>;
	CC_SYNTHESIZE(Node*,m_endingUI,EndingUI);
public:
	bool init();
	void loadUI();
	void intoDeadEnding();
	void intoAliveEnding();
};

#endif // EndingManager_h__