#include "ChoicesView.h"

using namespace cocos2d;

ChoicesView::ChoicesView() :m_choicesLayout(nullptr), m_button{nullptr}{}

bool ChoicesView::init() {
	if (!Layout::init())return false;

	m_choicesLayout = DialogBoxUITemlate::getInstance()->getBasicChoiceLayout();
	this->addChild(m_choicesLayout);

	for (int i = 0; i < 4; ++i)
	{
		m_button[i] = static_cast<Button*>(m_choicesLayout->getChildByName(StringUtils::format("Button%d", i)));
		m_button[i]->setVisible(false);
	}
	return true;
}

void ChoicesView::putChoices(const Choices& choices) {
	m_choices = choices;

	for (int i = 0; i < m_choices.size; ++i)
	{
		Option& option = m_choices.option[i];
		auto text = static_cast<Text*>(m_button[i]->getChildByName("Text"));
		//设置文字
		text->setText(option.m_words);

		//设置文字颜色
		Color3B color;
		switch (option.m_color)
		{
		case  ChoiceColor::red:
			color = Color3B::RED;
			break;
		case ChoiceColor::green:
			color = Color3B::GREEN;
			break;
		default:
			color = Color3B::WHITE;
			break;
		}
		text->setColor(color);

		m_button[i]->addClickEventListener([this,&option](cocos2d::Ref*){
			//完成选项相应事件
			option.m_choiceFunc();
			//完成选项->关闭选择
			this->finishChoices();
		});
	}
}
void ChoicesView::showChoices() {
	for (int i = 0; i < m_choices.size; ++i) {
		//设置按钮可见
		m_button[i]->setVisible(true);
		//如果不满足条件则 屏蔽按钮
		if (!m_choices.option[i].m_condition())m_button[i]->setEnabled(false);
	}
}
void ChoicesView::finishChoices() {
	//全部设置不可见
	for (int i = 0; i < m_choices.size; ++i)
		m_button[i]->setVisible(false);
	NotificationCenter::getInstance()->postNotification("DialogBox_Done", this);
}