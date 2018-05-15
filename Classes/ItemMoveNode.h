#pragma once
#ifndef _ITEM_MOVE_NODE_H_
#define _ITEM_MOVE_NODE_H_

#include "cocos2d.h"
#include "Item.h"
//cocos studio  UI¿â
#include "ui\CocosGUI.h"  
#include "cocostudio\CocoStudio.h" 

using cocos2d::Sprite;
using cocos2d::Node;
using cocos2d::ui::Layout;

using Func = std::function<void(Item*,int)>;
using Func_NoArgu = std::function<void()>;

class ItemMoveNode:public Node{
public:
	static Layout* s_itemmovepage;
	static void initItemMovePage();
protected:
	CC_SYNTHESIZE(Item*, m_item, Item);
	CC_SYNTHESIZE(Func, m_callback,CallBackFunc);
	CC_SYNTHESIZE(Func_NoArgu, m_cancelcallback, CancelCallBackFunc);
private:
	void finishMove(int resultsum);
public:
	ItemMoveNode();
	~ItemMoveNode();
	bool init();
	CREATE_FUNC(ItemMoveNode);
	void openPage(Item* i, Func callback, Func_NoArgu cancelcallback);
	void closePage();
};

#endif