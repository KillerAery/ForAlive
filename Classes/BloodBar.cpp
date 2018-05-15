#include "BloodBar.h"
#include "Biology.h"

BloodBar::BloodBar() :m_bar(nullptr), m_maxbar(nullptr){}

bool BloodBar::init() {
	m_maxbar = Sprite::create("/BloodBar/maxbloodbar.png");
	this->addChild(m_maxbar);
	m_bar = Sprite::create("/BloodBar/bloodbar.png");
	this->addChild(m_bar);

	return true;
}

void BloodBar::showBloodBar(Biology * b){
	this->unschedule("bloodbar");
	this->setVisible(true);
	m_bar->setScaleX(float(b->getHealth()) / float(b->getMaxHealth()));
	this->schedule([this](float dt) {this->setVisible(false); }, 3.0f, std::string("bloodbar"));
}