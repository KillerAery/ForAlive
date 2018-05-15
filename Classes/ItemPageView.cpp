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

//����ʹ����Ʒҳ��
bool ItemPageView::requestUseItem(ItemPage* i,const Vec2& point) {
	//��Ʒ����
	auto description = BackPackUITemplate::getInstance()->getBaseItemDescription();
	/*��description	������Ⱦ����,���ⱻ����*/
	description->setPositionZ(10);
	description->setVisible(true);
	description->setPosition(Vec2(point.x, point.y-description->getContentSize().height/1.7));
	auto destext = static_cast<Text*>(description->getChildByName("description"));
	destext->setText(i->getItem()->getDescription());
	i->addChild(description);

	Item* item = i->getItem();
	Player* player = GameManager::getInstance()->getPlayer();
	Button* button = nullptr;

	//������ã����ṩʹ�ð�ť
	if (player->itemUseable(item, 1)) {
		//ʹ�ð�ť 
		button = BackPackUITemplate::getInstance()->getUseButton();
		//button->setSwallowTouches(true);
		button->setVisible(true);
		button->setPositionX(description->getContentSize().width / 2);
		//������desciprtion��
		description->addChild(button);
		//ʹ�ð�ť ���º�Ч����ʹ��1������Ʒ
		button->addClickEventListener([player, item](Ref*) {player->useItem(item, 1);});
	}

	//����
	auto listener = EventListenerTouchOneByOne::create();
	//�Ƿ���û�¼������¼�
	listener->setSwallowTouches(true);
	//������ʼ
	listener->onTouchBegan = [description](Touch* touch, Event* event) {
		//�������Χ
		auto des_rect = Rect(0,0, description->getContentSize().width,description->getContentSize().height);
		//��ȡ������
		auto touchpoint = description->convertToNodeSpace(touch->getLocation());
		//������Ŀ�����Χ��
		if (!des_rect.containsPoint(touchpoint)) { description->removeFromParent(); return false; }
		return true;
	};
	//�󶨴�����description
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,description);

	return true;
}

//����ת����Ʒҳ��
bool ItemPageView::requestMoveItem(ItemPage* itempage, ItemPageView* otherView){
	auto item = itempage->getItem();

	auto itemmove =ItemMoveNode::create();
	
	//��Ϊ��ҵ���Ʒҳ�治������ʧ
	//����ж�����ת����Ʒҳ���������Լ���ҳ�棬��������Ϊ����ҳ���child
	if (otherView->getContainer() == GameManager::getInstance()->getPlayer())this->addChild(itemmove);
	else otherView->addChild(itemmove);

	itemmove->openPage(itempage->getItem(),
		//ִ�гɹ�����
		[this, otherView](Item* i,int result){
		if (!otherView->ifaddItem(i))return;
		this->premoveItem(i, i->getID(), result, otherView);
		this->reload();otherView->reload();
	},
		//ִ��ȡ������
		[itempage](){itempage->setPosition(itempage->getForwardPosition());});

	return true;
}

//��������Ʒҳ��
bool ItemPageView::requestThrowItem(ItemPage* itempage) {

	auto item = itempage->getItem();

	auto itemmove = ItemMoveNode::create();
	this->addChild(itemmove);

	itemmove->openPage(itempage->getItem(),
		//ִ�гɹ�����
		[this,itempage](Item* i, int result) {
		this->prethrowItem(itempage,result);
		this->reload();
	},
		//ִ��ȡ������
		[itempage]() {itempage->setPosition(itempage->getForwardPosition());});

	return false;
}


void ItemPageView::bindItemPageListener(ItemPage* itemPage){
	auto listener = EventListenerTouchOneByOne::create();
	//�Ƿ���û�¼������¼�
	listener->setSwallowTouches(true);
	//ItemPage������ʼ�¼�
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		auto itempage = static_cast<ItemPage*>(event->getCurrentTarget());
		/*������Ŀ�����Χ�ڣ�����Ӧ*/
		
		//���Ŀ�����Χ
		auto rect = Rect(-itempage->getContentSize().width / 2, -itempage->getContentSize().height / 2, itempage->getContentSize().width, itempage->getContentSize().height);
		//��ȡ������
		auto touchpoint = itempage->convertToNodeSpace(touch->getLocation());
		//������Ŀ�����Χ�ڣ�����Ӧ
		if (!rect.containsPoint(touchpoint))return false;

		/*��Itempage������Ⱦ����,�����϶���ItemPage���ֱ�����*/
		itempage->setLocalZOrder(100);
		itempage->setPositionZ(10);

		//�����Ʒ�˫����������ʹ��
		if (itempage->isDoubleClick())requestUseItem(itempage, touchpoint);

		return true;
	};
	//ItemPage�����ƶ��¼�
	listener->onTouchMoved = [](Touch* touch, Event* event) {
		//���ƫ�ƣ��϶���Ʒ��Ŀ
		auto itempage = static_cast<ItemPage*>(event->getCurrentTarget());
		//Ŀ������ =  Ŀ��ԭ����+����ƫ��ֵ
		itempage->setPosition(itempage->getPosition() + touch->getDelta());
	};
	//ItemPage�����ɿ��¼�
	listener->onTouchEnded = [this](Touch* touch, Event* event) {
		//��ȡĿ��
		auto itempage = static_cast<ItemPage*>(event->getCurrentTarget());

		/*��Itempage��ԭ��Ⱦ���ȣ�����*/
		itempage->setLocalZOrder(0);
		itempage->setPositionZ(0);

		for (auto ipv : s_itempageview_list)
		{
			if (ipv == this) continue;
			//��ȡ������
			Point touchpoint = ipv->convertToNodeSpace(touch->getLocation());
			//���ڸ�ItemPageView��
			if (!Rect(0, 0, ipv->getContentSize().width, ipv->getContentSize().height).containsPoint(touchpoint))continue;

			if (ipv->ifaddItem(itempage->getItem()))this->requestMoveItem(itempage, ipv);
			else itempage->setPosition(itempage->getForwardPosition());
			return;
		}

		//��ȡ������
		auto backlayer = BackPackUITemplate::getInstance()->r_backpackui;
		Point touchpoint = backlayer->convertToNodeSpace(touch->getLocation());
		//���ڸ�ItemPageView��
		if (!Rect(0, 0, backlayer->getContentSize().width, backlayer->getContentSize().height).containsPoint(touchpoint)){
			this->requestThrowItem(itempage);
			return;
		}

		//���û���¼��� ��λ
		itempage->setPosition(itempage->getForwardPosition());

	};
	//�󶨴��������NODE��
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, itemPage);
}