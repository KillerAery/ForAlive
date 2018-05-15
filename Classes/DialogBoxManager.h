#pragma once
#ifndef DialogBoxManager_h__
#define DialogBoxManager_h__

#include "cocos2d.h"
#include "Singleton.h"
#include "Dialog.h"
#include "DialogBoxView.h"
#include "ChoicesView.h"

using cocos2d::Ref;

class DialogBoxManager :public Ref, public Singleton<DialogBoxManager>{
	DialogBoxView* m_dialogBoxView[2];
	ChoicesView* m_choicesView;
	CC_SYNTHESIZE_PASS_BY_REF(Dialog, m_dialog, Dialog);
private:
	DialogBoxManager();
	~DialogBoxManager();
	friend Singleton<DialogBoxManager>;
public:
	bool init();
	bool requestTalk(Dialog& dialog);
	void requestChoices(const Choices& choices);
	void doneTalk(Ref* r);

	void finishTalk();
	void pauseGame();
	void resumeGame();
};
#endif // DialogBoxManager_h__
