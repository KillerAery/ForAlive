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
		//��������
		text->setText(option.m_words);

		//����������ɫ
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
			//���ѡ����Ӧ�¼�
			option.m_choiceFunc();
			//���ѡ��->�ر�ѡ��
			this->finishChoices();
		});
	}
}
void ChoicesView::showChoices() {
	for (int i = 0; i < m_choices.size; ++i) {
		//���ð�ť�ɼ�
		m_button[i]->setVisible(true);
		//��������������� ���ΰ�ť
		if (!m_choices.option[i].m_condition())m_button[i]->setEnabled(false);
	}
}
void ChoicesView::finishChoices() {
	//ȫ�����ò��ɼ�
	for (int i = 0; i < m_choices.size; ++i)
		m_button[i]->setVisible(false);
	NotificationCenter::getInstance()->postNotification("DialogBox_Done", this);
}