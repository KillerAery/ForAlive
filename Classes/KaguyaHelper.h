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
	//ע��cocos2dx��Ĳ�����Ĳ��ֽӿ�
	void registerCocos2dxLib(kaguya::State & state);
	//ע��AI�Ļ����ڵ���Ĳ��ֽӿ�
	void registerAIBaseLib(kaguya::State & state);
	//ע��AI����Ϊ�ڵ���Ĳ��ֽӿ�
	void registerAIBehavioerLib(kaguya::State & state);
	//ע��Ի���Ĳ��ֽӿ�
	void registerDialogBoxLib(kaguya::State & state);
	//ע������Ĳ��ֽӿ�
	void registerMissionLib(kaguya::State & state);
};

#endif // KaguyaHelper_h__