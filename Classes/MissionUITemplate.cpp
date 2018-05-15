#include "MissionUITemplate.h"

MissionUITemplate::MissionUITemplate() :r_targetTemplate(nullptr),r_missionItemTemplate(nullptr){
}

bool MissionUITemplate::init() {
	return true;
}

//读取MissionLayerUI获得模板
void MissionUITemplate::loadMissionLayerUI(Layer* missionLayer) {
	loadTargetTemplate(missionLayer);
	loadMissionItemTemplate(missionLayer);
}

void MissionUITemplate::loadTargetTemplate(Layer* missionLayer) {
	r_targetTemplate = static_cast<Layout*>(missionLayer->getChildByName("TargetTemplate"));
	CCASSERT(r_targetTemplate, "MissionUITemplate的UI模板 = nullptr !!!!!!!");
}

Layout* MissionUITemplate::getTargetTemplate() {
	auto layout = static_cast<Layout*>(r_targetTemplate->clone());
	layout->setVisible(true);
	return layout;
}


void MissionUITemplate::loadMissionItemTemplate(Layer* missionLayer) {
	r_missionItemTemplate  = static_cast<Button*>(missionLayer->getChildByName("MissionItem"));
	CCASSERT(r_missionItemTemplate, "MissionItemTemplate的UI模板 = nullptr !!!!!!!");
}

Button* MissionUITemplate::getMissionItemTemplate() {
	auto layout = static_cast<Button*>(r_missionItemTemplate->clone());
	layout->setVisible(true);
	return layout;
}