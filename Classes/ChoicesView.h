#pragma once
#ifndef ChoicesView_h__
#define ChoicesView_h__

#include "cocos2d.h"
#include "DialogBoxUITemlate.h"
#include "Dialog.h"

using std::string;
using cocos2d::ui::Button;
using cocos2d::ui::Text;

class ChoicesView : public Layout{
protected:
	Button* m_button[4];
	Choices m_choices;
	CC_SYNTHESIZE(Layout*, m_choicesLayout, ChoicesLayout);	//Ñ¡Ôñ²ã
public:
	ChoicesView();
	CREATE_FUNC(ChoicesView);
	bool init();

	void putChoices(const Choices& choices);
	void showChoices();
	void finishChoices();
};

#endif // ChoicesView_h__