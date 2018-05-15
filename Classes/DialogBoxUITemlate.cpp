#include "DialogBoxUITemlate.h"

DialogBoxUITemlate::DialogBoxUITemlate():m_myDialogTempalte(nullptr),m_otherDialogTempalte(nullptr),m_choiceLayoutTempalte(nullptr),m_dialogboxLayer(nullptr){}

DialogBoxUITemlate::~DialogBoxUITemlate(){
	m_dialogboxLayer->autorelease();
}

bool DialogBoxUITemlate::init() {
	loadDialogBoxUI();
	return true;
}

//��ȡcsb�ļ����ģ��UI
void DialogBoxUITemlate::loadDialogBoxUI(){
	//����UI.csb�ļ�
	m_dialogboxLayer = static_cast<Layer*>(cocos2d::CSLoader::createNode("UI/DialogBoxLayer.csb"));
	m_dialogboxLayer->retain();
	CCASSERT(m_dialogboxLayer, "DialogBoxUITemplate load UIlayer failed!");

	loadOtherDialogUITempalte(m_dialogboxLayer);
	loadMyDialogUITempalte(m_dialogboxLayer);
	loadChoiceLayoutUITempalte(m_dialogboxLayer);
}

/*------otherDialogģ��UI-------*/
void DialogBoxUITemlate::loadOtherDialogUITempalte(Layer* dialogBoxLayer) {
	m_otherDialogTempalte = static_cast<Layout*>(dialogBoxLayer->getChildByName("OtherDialog"));

	CCASSERT(m_otherDialogTempalte, "DialogBoxUITemplate load UIlayer failed!");
}
Layout* DialogBoxUITemlate::getBasicOtherDialogUI() {
	return static_cast<Layout*>(m_otherDialogTempalte->clone());
}

/*------myDialogTempalteģ��UI-------*/
void DialogBoxUITemlate::loadMyDialogUITempalte(Layer* dialogBoxLayer) {
	m_myDialogTempalte = static_cast<Layout*>(dialogBoxLayer->getChildByName("MyDialog"));
	CCASSERT(m_myDialogTempalte ,"DialogBoxUITemplate load UIlayer failed!");
}
Layout* DialogBoxUITemlate::getBasicMyDialogUI() {
	return static_cast<Layout*>(m_myDialogTempalte->clone());
}	

/*------ChoiceLayoutTempalteģ��UI-------*/
void DialogBoxUITemlate::loadChoiceLayoutUITempalte(Layer* dialogBoxLayer) {
	m_choiceLayoutTempalte = static_cast<Layout*>(dialogBoxLayer->getChildByName("ChoiceLayout"));
	CCASSERT(m_choiceLayoutTempalte, "DialogBoxUITemplate load UIlayer failed!");
}
Layout* DialogBoxUITemlate::getBasicChoiceLayout(){
return static_cast<Layout*>(m_choiceLayoutTempalte->clone());
}