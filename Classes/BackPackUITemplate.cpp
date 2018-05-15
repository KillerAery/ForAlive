#include <BackPackUITemplate.h>

BackPackUITemplate::BackPackUITemplate():m_basecontaineritempage(nullptr),m_baseweapongearitempage(nullptr),m_usebutton(nullptr),m_basecontainerpageview(nullptr),m_baseitemdescription(nullptr),r_backpackui(nullptr){}

bool BackPackUITemplate::init() {
	return true;
}

//读取BackpackUI layer获得模板UI
void BackPackUITemplate::loadBackPackUI(Layer* backpackui){
	r_backpackui = static_cast<ImageView*>(backpackui->getChildByName("BackPack_Template")->getChildByName("backpacklview"));
	CCASSERT(r_backpackui, "BackPackUITemplate load backpackui failed!!");
	loadBasicContainerItemPage(backpackui);
	loadBasicWeaponGearItemPage(backpackui);
	loadBasicContainerPageView(backpackui);
	loadUseBuutonTemplate(backpackui);
	loadBaseItemDescription(backpackui);
}


/*------ContainerItemPage模板UI-------*/
void BackPackUITemplate::loadBasicContainerItemPage(Layer* backpackui) {
	m_basecontaineritempage = static_cast<Layout*>(backpackui->getChildByName("ItemPage_Template"));	
	CCASSERT(m_basecontaineritempage, "BasicItemPage的UI模板 = nullptr !!!!!!!");
}
	
Layout* BackPackUITemplate::getBasicContainerItemPage() {
	return static_cast<Layout*>(m_basecontaineritempage->clone());
}

/*------WeaponGearItemPage模板UI-------*/
void BackPackUITemplate::loadBasicWeaponGearItemPage(Layer* backpackui) {
	m_baseweapongearitempage = static_cast<Layout*>(backpackui->getChildByName("WeaponGearItemPage_Template"));	
	CCASSERT(m_baseweapongearitempage, "BasicWeaponGearItemPage的UI模板 = nullptr !!!!!!!");
}

Layout* BackPackUITemplate::getBasicWeaponGearItemPage(){
	return static_cast<Layout*>(m_baseweapongearitempage->clone());
}

/*------ContainerPageView模板UI-------*/
void BackPackUITemplate::loadBasicContainerPageView(Layer* backpackui){
m_basecontainerpageview = static_cast<Layout*>(backpackui->getChildByName("ContainerPageView_Template"));
CCASSERT(m_basecontainerpageview, "ContainerPageView的UI模板 = nullptr !!!!!!!");
}

Layout* BackPackUITemplate::getBasicContainerPageView() {
	return static_cast<Layout*>(m_basecontainerpageview->clone());
}

/*------ItemDescription模板UI-------*/
void BackPackUITemplate::loadBaseItemDescription(Layer* backpackui) {
	m_baseitemdescription = static_cast<Layout*>(backpackui->getChildByName("Description_Template"));
	CCASSERT(m_baseitemdescription, "ItemDescription的UI模板 = nullptr !!!!!!!");
}

Layout* BackPackUITemplate::getBaseItemDescription() {
	return static_cast<Layout*>(m_baseitemdescription->clone());
}

/*------使用按钮 模板UI-------*/
void BackPackUITemplate::loadUseBuutonTemplate(Layer* backpacklayer) {
	m_usebutton = static_cast<Button*>(backpacklayer->getChildByName("ButtonUse_Template"));
	CCASSERT(m_usebutton, "UseButton的UI模板 = nullptr !!!!!!!");
}

Button* BackPackUITemplate::getUseButton() {
	return static_cast<Button*>(m_usebutton->clone());
}