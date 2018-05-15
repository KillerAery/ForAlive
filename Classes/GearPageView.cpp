#include "GearPageView.h"
#include "Biology.h"

using namespace cocos2d;


GearPageView::GearPageView():m_itempage(nullptr),m_sprite(nullptr),m_index(0),m_biology(nullptr){}

bool GearPageView::init(Biology* b, int geartpyr, Layer* backpacklayer){
	if (!Node::init())return false;
	CCASSERT(m_index <= RightHandGear, "m_index>RightHandGear!!!!");
	m_biology = b;
	m_index = geartpyr;
	initGearPageViewUI(backpacklayer);
	initItemPages();
	this->schedule(schedule_selector(GearPageView::updateRefresh),0.1f);
	return true;
}


void GearPageView::initGearPageViewUI(Layer* backpacklayer) {
	//暂时增加 不推荐
	if (!backpacklayer)return;
	m_sprite = static_cast<ImageView*>(backpacklayer->getChildByTag(1)->getChildByTag(70 + m_index));
	this->setAnchorPoint(Vec2(0.5, 0.5));
	this->setPosition(m_sprite->getWorldPosition());
	//测试体积用
//	setBackGroundColorType(Layout::BackGroundColorType::SOLID);
//	setBackGroundColor(Color3B(255, 255, 255));
	this->setContentSize(Size(m_sprite->getContentSize().width*m_sprite->getParent()->getScaleX(),m_sprite->getContentSize().height*m_sprite->getParent()->getScaleY()));
}

void GearPageView::initItemPages() {	
	if (m_index<GearTpye::HeadGear || m_index>GearTpye::HandGear || !m_biology->getGearVec()[m_index])return;
	this->addItemPage(GearItemPage::create(m_biology->getGearVec()[m_index]));
}

GearPageView* GearPageView::create(Biology* b, int geartpyr, Layer* backpacklayer) {
	auto gearpage = new (std::nothrow)GearPageView();
	if (gearpage &&gearpage->init(b,geartpyr,backpacklayer)) {
		gearpage->autorelease(); 
		s_itempageview_list.push_back(gearpage);
	}
	else CC_SAFE_DELETE(gearpage);
	return gearpage;
}

Container* GearPageView::getContainer() { return m_biology; }


//不推荐
void GearPageView::reload(){
	if(m_itempage)
	this->removeItemPage(m_itempage);
	init(m_biology,m_index,nullptr);
}
//更新
void GearPageView::updateRefresh(float dt) {
	CCASSERT(m_biology, "GearPageView::m_biology doesnt exist");
	if (!m_itempage)return;
	else if (m_biology->getGearVec()[m_index] == nullptr) {
		this->removeItemPage(m_itempage);
	}
	else m_itempage->refresh();
}

//查询是否满足添加物品条件
bool GearPageView::ifaddItem(int id, int sum){
	//item数量少于等于0，item类型不符 均失败
	if (sum <= 0 || Item::getItemTpye(id) != ItemTpye::Armor )return false;

	return true;
}
//查询是否满足添加物品条件
bool GearPageView::ifaddItem(Item* item) {
	//item不存在,item数量少于等于0，item类型不符 均失败
	if (!item||item->getSum()<= 0 || item->getItemTpye() != ItemTpye::Armor)return false;
	return true;
}
//预添加物品
bool GearPageView::preaddItem(int id, int sum){
	auto ret = m_biology->wearGear(id,sum,(GearTpye)m_index);
	return ret;
}
//预添加物品
bool GearPageView::preaddItem(Item* i) {
	if (i == nullptr)return false;
	return m_biology->wearGear(i,(GearTpye)m_index);
}
//预扔物品
bool GearPageView::prethrowItem(ItemPage* itempage, int sum) {
	m_biology->throwGearDrop((GearTpye)m_index,sum);
	return true;
}
//预使用物品
bool GearPageView::preuseItem(ItemPage* i) {
	return false;
}
//预转移物品
bool GearPageView::premoveItem(Item* i, int id, int sum, ItemPageView* otherView) {
	CCASSERT(i->getSum() >= sum&&m_biology->getGearVec()[m_index] == i, "premoveItem out of item's sum!");
	bool ret = false;

	if (i->getMaxSuperPosition() == i->getSum())ret = otherView->preaddItem(m_biology->moveGear(GearTpye(m_index)).getValueAndClearProtectedTansfer());
	else ret = otherView->preaddItem(id, sum) && m_biology->removeGear((GearTpye)m_index, sum);

	return ret;
}



void GearPageView::addItemPage(GearItemPage * itempage) {
	m_itempage = itempage;
	m_itempage->setForwardPosition(m_itempage->getPosition());
	m_itempage->setAnchorPoint(Vec2(-0.5, -0.5));
	this->bindItemPageListener(m_itempage);
	this->addChild(m_itempage);
}

void GearPageView::removeItemPage(GearItemPage * itempage) {
	CCASSERT(itempage == m_itempage, "GEARPAGEVIEW m_itempage != itempage");
	m_itempage->removeFromParent();
	m_itempage = nullptr;
}