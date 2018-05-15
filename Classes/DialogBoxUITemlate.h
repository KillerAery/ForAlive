#pragma once
#ifndef DialogBoxUITemlate_h__
#define DialogBoxUITemlate_h__

#include "cocos2d.h"
#include "Singleton.h"
//cocos studio  UI��
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
	//��ȡcsb�ļ����ģ��UI
	void loadDialogBoxUI();
	CC_SYNTHESIZE(Layer*,m_dialogboxLayer,DialogBoxLayer);

	/*------otherDialogģ��UI-------*/
	Layout* m_otherDialogTempalte;
	void loadOtherDialogUITempalte(Layer* dialogBoxLayer);
	Layout* getBasicOtherDialogUI();
	/*------myDialogTempalteģ��UI-------*/
	Layout* m_myDialogTempalte;
	void loadMyDialogUITempalte(Layer* dialogBoxLayer);
	Layout* getBasicMyDialogUI();
	/*------ChoiceLayoutTempalteģ��UI-------*/
	Layout* m_choiceLayoutTempalte;
	void loadChoiceLayoutUITempalte(Layer* dialogBoxLayer);
	Layout* getBasicChoiceLayout();

	friend Singleton<DialogBoxUITemlate>;

};

#endif // DialogBoxUITemlate_h__