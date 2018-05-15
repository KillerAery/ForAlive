#ifndef _ITEMPAGE_H_
#define _ITEMPAGE_H_

#include "ItemFactory.h"
#include <list>

#include "cocos2d.h"
//cocos studio  UIø‚
#include "ui\CocosGUI.h"  
#include "cocostudio\CocoStudio.h" 

using cocos2d::Node;
using cocos2d::ui::Layout;
using cocos2d::Sprite;
using cocos2d::Label;
using cocos2d::Vec2;


class ItemPage;

class ItemPage : public Node {
/*------≥ı ºªØ-------*/
protected:
	CC_SYNTHESIZE(Item*, m_item, Item);
	CC_SYNTHESIZE(int, m_uniqueID,UniqueID);
	CC_SYNTHESIZE_PASS_BY_REF(Vec2, m_forwardposition,ForwardPosition);
	CC_SYNTHESIZE(bool, m_ifmove,IfMove);
public:
	ItemPage();
	virtual ~ItemPage();
	virtual bool init(Item* item);
	virtual void refresh()=0;
public:
	CC_SYNTHESIZE(bool, m_ifclick, IfClick);
	bool isDoubleClick();
};
#endif
