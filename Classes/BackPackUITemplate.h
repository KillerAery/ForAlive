#pragma once
#ifndef _BACKPACK_UI_TEMPLATE_H_
#define _BACKPACK_UI_TEMPLATE_H_

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
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::ui::ImageView;



class BackPackUITemplate : public Ref, public Singleton<BackPackUITemplate> {
private:
	BackPackUITemplate();
public:
	bool init();
	//读取BackpackUI layer获得模板UI
	void loadBackPackUI(Layer* backpackui);
	//背包的引用
	ImageView* r_backpackui;
	/*------ContainerItemPage模板UI-------*/
	Layout* m_basecontaineritempage;
	void loadBasicContainerItemPage(Layer* backpackui);
	Layout* getBasicContainerItemPage();
	/*------WeaponGearItemPage模板UI-------*/
	Layout* m_baseweapongearitempage;
	void loadBasicWeaponGearItemPage(Layer* backpackui);
	Layout* getBasicWeaponGearItemPage();
	/*------ContainerPageView模板UI-------*/
	Layout* m_basecontainerpageview;
	void loadBasicContainerPageView(Layer* backpackui);
	Layout* getBasicContainerPageView();
	/*------ItemDescription模板UI-------*/
	Layout* m_baseitemdescription;
	void loadBaseItemDescription(Layer* backpackui);
	Layout* getBaseItemDescription();
	/*------使用模板UI-------*/
	Button* m_usebutton;	
	void loadUseBuutonTemplate(Layer* backpacklayer);
	Button* getUseButton();

	friend Singleton<BackPackUITemplate>;
};

#endif // !_BACKPACK_UI_TEMPLATE_H_
