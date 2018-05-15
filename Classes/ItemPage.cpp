#include "ItemPage.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;



ItemPage::ItemPage():m_item(nullptr),m_ifclick(false),m_uniqueID(0),m_ifmove(false),m_forwardposition(0,0){}

ItemPage::~ItemPage(){}

bool ItemPage::init(Item* item) {
	if(!Node::init())return false;
	m_item = item;
	return true;
}

bool ItemPage::isDoubleClick(){
	bool result = m_ifclick;
	this->unschedule("ResumeClick");
	this->scheduleOnce([this](float dt){m_ifclick = false;},0.3f,"ResumeClick");
	m_ifclick = true;
	return result;
}
