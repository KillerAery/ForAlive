#pragma once
#ifndef GamePauseUtils_h__
#define GamePauseUtils_h__

#include "cocos2d.h"  
#include "Singleton.h"

using cocos2d::Node;
using cocos2d::Ref;

//操作类型  
enum class PauseTpye {
	PAUSE,
	RESUME
};

class GamePauseUtils : public Ref,public Singleton<GamePauseUtils>{
	GamePauseUtils();
	friend Singleton<GamePauseUtils>;
public:
	bool init();
	void operateAllSchedulerAndActions(Node* node, PauseTpye type, int ignoreTag = 000); //忽略检测的tag
};

#endif // GamePauseUtils_h__