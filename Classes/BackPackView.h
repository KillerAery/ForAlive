#pragma once
#ifndef _BACKPACKVIEW_H_
#define _BACKPACKVIEW_H_

#include "GearPageView.h"
#include "ContainerPageView.h"
#include "WeaponGearPageView.h"
#include "BackPackUITemplate.h"

using cocos2d::Layer;
using cocos2d::Sprite;
using cocos2d::ui::ListView;
using cocos2d::ui::Widget;

//����UI
class BackPackView :public Widget{
protected:
	CC_SYNTHESIZE(Layer*, m_backpacklayer, BackPackLayer);
	CC_SYNTHESIZE(Biology*, m_opener,Opener);
	CC_SYNTHESIZE(ListView*, m_mylistview, MyListView);
	CC_SYNTHESIZE(ListView*, m_otherlistview, OtherListView);
public:
	BackPackView();
	~BackPackView();
	virtual bool init()override;
	static BackPackView* create();
protected:
	bool ifInTheRange(Node* a, Node* b, double RangeSq){ return (a->getPosition().getDistanceSq(b->getPosition()) < RangeSq); }
	void addTargetAsView(Container* target);	//Ϊ�·��ֵ�Ŀ��������� һ��viewҳ
public:
	void initUI();
	void initUITemplates();

	void initGearPageView();
	void initContainerPageView();

	void removePageView(ItemPageView* i);//�Ƴ�ItemPageView

	void openOrCloseBackPack(Biology* biology);
	void closeBackPack();

	void checkContainer(float dt);
	void ContainerDelete(Ref* r);
};

#endif