#pragma once
#ifndef _CONTAINER_ITEM_PAGE_H_
#define _CONTAINER_ITEM_PAGE_H_

#include "ItemPage.h"

class ContainerItemPage :public ItemPage {
protected:
	CC_SYNTHESIZE(Label*, m_sumlabel, SumLabel);
public:
	ContainerItemPage();
	static ContainerItemPage* create(Item* item);
	bool init(Item* item);
	virtual void refresh()override;
};


#endif