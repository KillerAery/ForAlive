#pragma once
#ifndef MissionUITemplate_h__
#define MissionUITemplate_h__

#include "cocos2d.h"
#include "Singleton.h"
//cocos studio  UI库
#include "ui\CocosGUI.h"  
#include "cocostudio\CocoStudio.h" 

using cocos2d::Layer;
using cocos2d::Sprite;
using cocos2d::ui::Layout;
using cocos2d::ui::ListView;
using cocos2d::ui::CheckBox;
using cocos2d::ui::Widget;
using cocos2d::ui::Text;
using cocos2d::ui::Button;

class MissionUITemplate : public cocos2d::Ref, public Singleton<MissionUITemplate> {
private:
	MissionUITemplate();
	friend Singleton<MissionUITemplate>;
public:
	bool init();
	//读取MissionLayerUI获得模板
	void loadMissionLayerUI(Layer* missionLayer);

	Layout* r_targetTemplate;
	void loadTargetTemplate(Layer* missionLayer);
	Layout* getTargetTemplate();
	
	Button* r_missionItemTemplate;
	void loadMissionItemTemplate(Layer* missionLayer);
	Button* getMissionItemTemplate();
};

#endif // MissionUITemplate_h__