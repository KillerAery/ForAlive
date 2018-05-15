#pragma once
#ifndef DialogBoxUITemlate_h__
#define DialogBoxUITemlate_h__

#include "cocos2d.h"
#include "Singleton.h"
//cocos studio  UI库
#include "ui\CocosGUI.h"  
#include "cocostudio\CocoStudio.h" 

using cocos2d::Ref;
using cocos2d::ui::Layout;
using cocos2d::ui::Button;
using cocos2d::Layer;
using cocos2d::Node;
using cocos2d::Label;


class DialogBoxUITemlate : public Ref, public Singleton<DialogBoxUITemlate> {
private:
	DialogBoxUITemlate();
	~DialogBoxUITemlate();
public:
	bool init();
	//读取csb文件获得模板UI
	void loadDialogBoxUI();
	CC_SYNTHESIZE(Layer*,m_dialogboxLayer,DialogBoxLayer);

	/*------otherDialog模板UI-------*/
	Layout* m_otherDialogTempalte;
	void loadOtherDialogUITempalte(Layer* dialogBoxLayer);
	Layout* getBasicOtherDialogUI();
	/*------myDialogTempalte模板UI-------*/
	Layout* m_myDialogTempalte;
	void loadMyDialogUITempalte(Layer* dialogBoxLayer);
	Layout* getBasicMyDialogUI();
	/*------ChoiceLayoutTempalte模板UI-------*/
	Layout* m_choiceLayoutTempalte;
	void loadChoiceLayoutUITempalte(Layer* dialogBoxLayer);
	Layout* getBasicChoiceLayout();

	friend Singleton<DialogBoxUITemlate>;

};

#endif // DialogBoxUITemlate_h__