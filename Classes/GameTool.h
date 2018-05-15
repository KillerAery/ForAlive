#pragma once
#ifndef _GAMETOOL_H_
#define _GAMETOOL_H_

#include "cocos2d.h"
#include "Singleton.h"
#include "Box2D/Box2D.h"

//物理引擎与cocos2dx 长度单位转换
#define PTM_RATIO 32

using cocos2d::Node;
using std::string;
using cocos2d::Vec2;

class GameTool:public Node ,public Singleton<GameTool>{
	GameTool();
private:
	std::vector<int> m_BGMlist;
	int m_EnviromentBGMID;
	void fadePlayBGM(const std::string& str,float fadeTime);
public:
	virtual bool init();
	void setIfBGM(bool ret);
	bool getIfBGM();
	void setIfEffect(bool ret);
	bool getIfEffect();
	void playBGM(const std::string& str);
	//渐入播放BGM，并且关闭其他BGM
	void fadePlayBGMandCloseOtherBGM(const string& str,float fadeTime = 2.0f);
	void playEffect(const string& str,float voice = 1.0f);
	void playEnviromentBGM(const string& str);
	void stopEnviromentBGM();
	void clearBGM();
	friend Singleton<GameTool>;
};




#endif // ! _GAMETOOL_H_
