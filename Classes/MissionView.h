#pragma once
#ifndef MissionView_h__
#define MissionView_h__

#include "cocos2d.h"
#include "Mission.h"
#include "MissionUITemplate.h"

class MissionView :public Widget {
	CC_SYNTHESIZE(Layer*,m_missionLayer,MissionLayer);
	CC_SYNTHESIZE(Text*,m_nameText,NameText);
	CC_SYNTHESIZE(Text*, m_descriptionText, DescriptionText);
	CC_SYNTHESIZE(ListView*, m_listView,ListView);
	CC_SYNTHESIZE(std::vector<Layout*>,m_targetLayouts,TargetLayouts);
public:
	MissionView();
	~MissionView();
	virtual bool init()override;
	void initUI();
	CREATE_FUNC(MissionView);
public:
	void openOrCloseMissionView();
	void closeMissionView();
	
	void addMission(Mission& mission);
	void updateMission(Mission& mission);
	void selectMission(Mission& mission);

	void cleanupMissionTargetLayout();

};

#endif // MissionView_h__