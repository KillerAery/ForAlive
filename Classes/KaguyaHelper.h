#pragma once
#ifndef KaguyaHelper_h__
#define KaguyaHelper_h__

#include "cocos2d.h"
#include "kaguya.hpp"
#include "Singleton.h"

#include "AIManager.h"
#include "DialogBoxManager.h"
#include "MissionManager.h"

class KaguyaHelper : public cocos2d::Ref , public Singleton<KaguyaHelper>{
	KaguyaHelper() {}
	friend Singleton<KaguyaHelper>;
	kaguya::State m_state;
public:
	kaguya::State& getState() { return m_state; }
	bool init();
	void loadLuaScrip(const std::string& luafile);
	//注册cocos2dx库的部分类的部分接口
	void registerCocos2dxLib(kaguya::State & state);
	//注册AI的基础节点类的部分接口
	void registerAIBaseLib(kaguya::State & state);
	//注册AI的行为节点类的部分接口
	void registerAIBehavioerLib(kaguya::State & state);
	//注册对话框的部分接口
	void registerDialogBoxLib(kaguya::State & state);
	//注册任务的部分接口
	void registerMissionLib(kaguya::State & state);
};

#endif // KaguyaHelper_h__