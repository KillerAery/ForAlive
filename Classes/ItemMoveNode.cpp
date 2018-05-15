#include "ItemMoveNode.h"
#include "GameManager.h"
//cocos studio  UI库
#include "ui\CocosGUI.h"  
#include "cocostudio\CocoStudio.h" 


using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

Layout* ItemMoveNode::s_itemmovepage = nullptr;
void ItemMoveNode::initItemMovePage(){
	//若已经初始化
	if (s_itemmovepage)return;
	//读入背包UI.csb文件
	auto UIlayer = static_cast<Layer*>(cocos2d::CSLoader::createNode("UI/OperatorLayer.csb"));
	Director::getInstance()->getRunningScene()->addChild(UIlayer);
	s_itemmovepage = static_cast<Layout*>(UIlayer->getChildByTag(24));
}
ItemMoveNode::ItemMoveNode() :m_item(nullptr), m_callback(nullptr), m_cancelcallback(nullptr) {}
ItemMoveNode::~ItemMoveNode() { 
	closePage(); 
	s_itemmovepage = nullptr;
}

bool ItemMoveNode::init(){
	if (!Node::init())return false;
	initItemMovePage();
	return true;
}

void ItemMoveNode::openPage(Item* i, Func callback,Func_NoArgu cancelcallback){
	CCASSERT(i, "ItemMoveNode::item doesnt exist!");
	m_item = i;
	m_callback = callback;
	m_cancelcallback = cancelcallback;

	//少量直接不用判断
	if (m_item->getSum() == 1) {
		finishMove(1);
		return;
	}

	CCASSERT(s_itemmovepage, "ItemMoveNode doesn't have ItemMoveNodePage");
	s_itemmovepage->setVisible(true);

	//数量文字
	auto text = static_cast<Text*>(s_itemmovepage->getChildByTag(102));
	text->setString(StringUtils::toString(m_item->getSum()));
	//滑动条
	auto slider = static_cast<Slider*>(s_itemmovepage->getChildByTag(103));
	slider->setPercent(100);
	slider->addEventListener([this,text](Ref * pSender, Slider::EventType type) {
		auto slider = static_cast<Slider*>(pSender);
		switch (type)
		{
		case cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED:
			text->setString(StringUtils::toString(int(slider->getPercent() / 100.0f * m_item->getSum())));
			break;
		}
	});
	//确认按键
	auto bt_yes = static_cast<Button*>(s_itemmovepage->getChildByTag(105));
	bt_yes->addClickEventListener([this,slider](Ref*) {
		if (slider->getPercent() / 100.0f*m_item->getSum() > 0) {
			auto sum = slider->getPercent() / 100.0f*m_item->getSum();
			finishMove(sum); 
			return;
		}
	});
	//取消按键
	auto bt_no = static_cast<Button*>(s_itemmovepage->getChildByTag(104));
	bt_no->addClickEventListener([this](Ref*){
		m_cancelcallback();
		this->closePage();
	});

}

void ItemMoveNode::closePage(){
	s_itemmovepage->setVisible(false);
	this->removeFromParent();
}

void ItemMoveNode::finishMove(int resultsum){
	m_callback(m_item, resultsum);
	closePage();
}