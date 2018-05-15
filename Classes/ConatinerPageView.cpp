#pragma once
#include <algorithm>
#include "Biology.h"
#include "ContainerPageView.h"
#include "BackPackUITemplate.h"


using namespace cocos2d;

ContainerPageView::ContainerPageView():m_container(nullptr),m_layout(nullptr),m_weightbar(nullptr){}

bool ContainerPageView::init(Container* c) {
	if (!ItemPageView::init())return false;
	setContainer(c);	
	setBackGroundColorType(Layout::BackGroundColorType::SOLID);
	setBackGroundColor(Color3B(255, 255, 255));
	setAnchorPoint(Vec2(0, 1));
	initContainerPageViewUI();
	initItemPages();
	this->schedule(schedule_selector(ContainerPageView::updateRefresh), 0.1f);
	return true;
}

//初始化UI模板
void ContainerPageView::initContainerPageViewUI(){
	//容器如果没有名字，则无需初始化该 模块UI
	if (m_container->getName().empty())return;
	//容器名字、负重模块
	m_layout = BackPackUITemplate::getInstance()->getBasicContainerPageView();
	m_layout->setAnchorPoint(Vec2(-0.5,0.5));
	m_layout->setVisible(true);
	this->setContentSize(m_layout->getContentSize());
	this->addChild(m_layout);
	//容器名字
	auto nametext = static_cast<cocos2d::ui::Text*>(m_layout->getChildByName("ContainerName"));
	nametext->setString(m_container->getName());
	//容器负重
	m_weightbar = static_cast<LoadingBar*>(m_layout->getChildByName("WeightBar"));
	m_weightbar->setPercent(m_container->getWeight()/m_container->getMaxweight()*100);
}

//初始化ItemPage 
void ContainerPageView::initItemPages() {
	for (auto i : m_container->getItemList())
		addItemPage(ContainerItemPage::create(i));
}

ContainerPageView* ContainerPageView::create(Container* c){
	auto itempageview = new (std::nothrow)ContainerPageView();
	if (itempageview &&itempageview->init(c)) { itempageview->autorelease();s_itempageview_list.push_back(itempageview); }
	else CC_SAFE_DELETE(itempageview);
	return itempageview;
}

Container* ContainerPageView::getContainer() {
	return m_container;
}


void ContainerPageView::reload() {
	//先清除
	for (auto i : m_itempagelist)i->removeFromParent();
	m_itempagelist.clear();
	//再重新读取多个itempages
	initItemPages();
}

//不断更新检查物品项目是否存在
/*TODO-----------待优化修改 -------*/
void ContainerPageView::updateRefresh(float dt) {
	CCASSERT(m_container, "ContainerPageView::m_container doesnt exist");

	//此处应用STL的交集算法，不应二重循环
	//先检查物品项目是否存在
	for (auto itr = m_itempagelist.begin();itr!=m_itempagelist.end();) 
		if (!m_container->findItem((*itr)->getItem())) { this->removeItemPage(itr++);}
		else { (*itr)->refresh(); ++itr; }
	
	//再检查是否有新物品
	for (auto item : m_container->getItemList())
	{
		auto find_result = std::find_if(m_itempagelist.begin(), m_itempagelist.end(), [item](ItemPage* itempage) {return itempage->getItem() == item; });
		//如果没有找到，也就是该物品为新物品,则添加它
		if(find_result == m_itempagelist.end())
			addItemPage(ContainerItemPage::create(item));
	}

	//更新重量检测
	if(m_weightbar)m_weightbar->setPercent(m_container->getWeight() / m_container->getMaxweight() * 100);
}

void ContainerPageView::addItemPage(ContainerItemPage* itempage) {
	auto sizeWidth = BackPackUITemplate::getInstance()->m_basecontaineritempage->getContentSize().width;
	auto sizeHeight = BackPackUITemplate::getInstance()->m_basecontaineritempage->getContentSize().height + m_itempagelist.size()*(BackPackUITemplate::getInstance()->m_basecontaineritempage->getContentSize().height + 5);
	//如果有名字模块，则高度 加 一项的高度
	if (m_layout)sizeHeight = sizeHeight + (BackPackUITemplate::getInstance()->m_basecontaineritempage->getContentSize().height + 5);

	this->setContentSize(Size(sizeWidth, sizeHeight));

	auto page = static_cast<ContainerItemPage*>(itempage);
	page->setForwardPosition(Vec2(sizeWidth, sizeHeight));
	page->setPosition(page->getForwardPosition());
	this->bindItemPageListener(page);
	this->addChild(page);
	m_itempagelist.push_back(page);
}

void ContainerPageView::removeItemPage(ContainerItemPage * itempage) {
	for (auto itr = m_itempagelist.begin(); itr != m_itempagelist.end(); ++itr)
		if ((*itr) == itempage) {
			removeItemPage(itr);
			return;
		}
	CC_ASSERT("ContainerPageView:No Such a Item");
}

void ContainerPageView::removeItemPage(typename ContainerItemPageList::iterator itr){
	(*itr)->removeFromParent();
	itr = m_itempagelist.erase(itr);
	goUpItemPages(itr);
}


void ContainerPageView::goUpItemPages(typename ContainerItemPageList::iterator itr) {
	for (; itr != m_itempagelist.end(); ++itr)
	{
		(*itr)->setForwardPosition(Vec2((*itr)->getForwardPosition().x, (*itr)->getForwardPosition().y + BackPackUITemplate::getInstance()->m_basecontaineritempage->getContentSize().height));
		if (!(*itr)->getIfMove())(*itr)->setPosition((*itr)->getForwardPosition());
	}

}



//查询是否满足添加物品条件
bool ContainerPageView::ifaddItem(int id, int sum) {
	//item数量少于等于0,容器不能容纳更多容量 失败
	if (sum <= 0 || !m_container->ifaddItem(id,sum))return false;

	return true;
}
bool ContainerPageView::ifaddItem(Item* item) {
	//item数量少于等于0,容器不能容纳更多容量 失败
	if (item->getSum() <= 0 || !m_container->ifaddItem(item))return false;

	return true;
}

bool ContainerPageView::preaddItem(Item* i) {
	return m_container->addItem(i);
}

bool ContainerPageView::preaddItem(int id, int sum) {
	return m_container->addItem(id, sum);
}

bool ContainerPageView::prethrowItem(ItemPage* itempage, int sum){
	m_container->throwContainerDrop(itempage->getItem(), sum);

	return true;
}

bool ContainerPageView::premoveItem(Item* i, int id, int sum, ItemPageView* otherView) {
	CCASSERT(i->getSum() >= sum, "premoveItem out of item's sum!");
	bool ret = false;

	if (i->getMaxSuperPosition() == i->getSum())ret = otherView->preaddItem(m_container->moveItem(i).getValueAndClearProtectedTansfer());
	else ret = m_container->removeItem(i,sum) && otherView->preaddItem(id, sum);

	return ret;
}

bool ContainerPageView::preuseItem(ItemPage* i) {
	return false;
}
