#include "ItemPageView.h"
#include "ItemMoveNode.h"
#include "BackPackUITemplate.h"
#include "GameManager.h"

using namespace cocos2d;
using cocos2d::ui::Text;

ItemPageViewList ItemPageView::s_itempageview_list{};

ItemPageView::ItemPageView(){}

ItemPageView::~ItemPageView(){
}

//请求使用物品页面
bool ItemPageView::requestUseItem(ItemPage* i,const Vec2& point) {
	//物品描述
	auto description = BackPackUITemplate::getInstance()->getBaseItemDescription();
	/*给description	设置渲染优先,避免被覆盖*/
	description->setPositionZ(10);
	description->setVisible(true);
	description->setPosition(Vec2(point.x, point.y-description->getContentSize().height/1.7));
	auto destext = static_cast<Text*>(description->getChildByName("description"));
	destext->setText(i->getItem()->getDescription());
	i->addChild(description);

	Item* item = i->getItem();
	Player* player = GameManager::getInstance()->getPlayer();
	Button* button = nullptr;

	//如果可用，则提供使用按钮
	if (player->itemUseable(item, 1)) {
		//使用按钮 
		button = BackPackUITemplate::getInstance()->getUseButton();
		//button->setSwallowTouches(true);
		button->setVisible(true);
		button->setPositionX(description->getContentSize().width / 2);
		//附属在desciprtion上
		description->addChild(button);
		//使用按钮 按下后效果：使用1个该物品
		button->addClickEventListener([player, item](Ref*) {player->useItem(item, 1);});
	}

	//监听
	auto listener = EventListenerTouchOneByOne::create();
	//是否吞没下级触摸事件
	listener->setSwallowTouches(true);
	//触摸开始
	listener->onTouchBegan = [description](Touch* touch, Event* event) {
		//算出矩阵范围
		auto des_rect = Rect(0,0, description->getContentSize().width,description->getContentSize().height);
		//获取触摸点
		auto touchpoint = description->convertToNodeSpace(touch->getLocation());
		//若不在目标矩阵范围内
		if (!des_rect.containsPoint(touchpoint)) { description->removeFromParent(); return false; }
		return true;
	};
	//绑定触摸到description
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,description);

	return true;
}

//请求转移物品页面
bool ItemPageView::requestMoveItem(ItemPage* itempage, ItemPageView* otherView){
	auto item = itempage->getItem();

	auto itemmove =ItemMoveNode::create();
	
	//因为玩家的物品页面不可能消失
	//如果判断请求转移物品页面的是玩家自己的页面，则将请求作为其他页面的child
	if (otherView->getContainer() == GameManager::getInstance()->getPlayer())this->addChild(itemmove);
	else otherView->addChild(itemmove);

	itemmove->openPage(itempage->getItem(),
		//执行成功函数
		[this, otherView](Item* i,int result){
		if (!otherView->ifaddItem(i))return;
		this->premoveItem(i, i->getID(), result, otherView);
		this->reload();otherView->reload();
	},
		//执行取消函数
		[itempage](){itempage->setPosition(itempage->getForwardPosition());});

	return true;
}

//请求扔物品页面
bool ItemPageView::requestThrowItem(ItemPage* itempage) {

	auto item = itempage->getItem();

	auto itemmove = ItemMoveNode::create();
	this->addChild(itemmove);

	itemmove->openPage(itempage->getItem(),
		//执行成功函数
		[this,itempage](Item* i, int result) {
		this->prethrowItem(itempage,result);
		this->reload();
	},
		//执行取消函数
		[itempage]() {itempage->setPosition(itempage->getForwardPosition());});

	return false;
}


void ItemPageView::bindItemPageListener(ItemPage* itemPage){
	auto listener = EventListenerTouchOneByOne::create();
	//是否吞没下级触摸事件
	listener->setSwallowTouches(true);
	//ItemPage触摸开始事件
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto itempage = static_cast<ItemPage*>(event->getCurrentTarget());
		/*若不在目标矩阵范围内，则不响应*/
		
		//算出目标矩阵范围
		auto rect = Rect(-itempage->getContentSize().width / 2, -itempage->getContentSize().height / 2, itempage->getContentSize().width, itempage->getContentSize().height);
		//获取触摸点
		auto touchpoint = itempage->convertToNodeSpace(touch->getLocation());
		//若不在目标矩阵范围内，则不响应
		if (!rect.containsPoint(touchpoint))return false;

		/*给Itempage设置渲染优先,避免拖动的ItemPage出现被覆盖*/
		itempage->setLocalZOrder(100);
		itempage->setPositionZ(10);

		//如果物品项被双击，则请求使用
		if (itempage->isDoubleClick())requestUseItem(itempage, touchpoint);

		return true;
	};
	//ItemPage触摸移动事件
	listener->onTouchMoved = [](Touch* touch, Event* event) {
		//鼠标偏移，拖动物品项目
		auto itempage = static_cast<ItemPage*>(event->getCurrentTarget());
		//目标坐标 =  目标原坐标+触摸偏移值
		itempage->setPosition(itempage->getPosition() + touch->getDelta());
	};
	//ItemPage触摸松开事件
	listener->onTouchEnded = [this](Touch* touch, Event* event) {
		//获取目标
		auto itempage = static_cast<ItemPage*>(event->getCurrentTarget());

		/*给Itempage还原渲染优先，避免*/
		itempage->setLocalZOrder(0);
		itempage->setPositionZ(0);

		for (auto ipv : s_itempageview_list)
		{
			if (ipv == this) continue;
			//获取触摸点
			Point touchpoint = ipv->convertToNodeSpace(touch->getLocation());
			//若在该ItemPageView内
			if (!Rect(0, 0, ipv->getContentSize().width, ipv->getContentSize().height).containsPoint(touchpoint))continue;

			if (ipv->ifaddItem(itempage->getItem()))this->requestMoveItem(itempage, ipv);
			else itempage->setPosition(itempage->getForwardPosition());
			return;
		}

		//获取触摸点
		auto backlayer = BackPackUITemplate::getInstance()->r_backpackui;
		Point touchpoint = backlayer->convertToNodeSpace(touch->getLocation());
		//若在该ItemPageView内
		if (!Rect(0, 0, backlayer->getContentSize().width, backlayer->getContentSize().height).containsPoint(touchpoint)){
			this->requestThrowItem(itempage);
			return;
		}

		//如果没有事件则 归位
		itempage->setPosition(itempage->getForwardPosition());

	};
	//绑定触摸到这个NODE上
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, itemPage);
}