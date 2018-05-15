#pragma once
#ifndef _BLOOD_BAR_H_
#define _BLOOD_BAR_H_

#include "cocos2d.h"

using cocos2d::Node;
using cocos2d::Sprite;

class Biology;

//¶¨ÒåÑªÌõ
class BloodBar :public Node {
	CC_SYNTHESIZE(Sprite*, m_maxbar, MaxBar);
	CC_SYNTHESIZE(Sprite*, m_bar, Bar);
public:
	BloodBar();
	virtual bool init();
	CREATE_FUNC(BloodBar);
	void showBloodBar(Biology * b);
};

#endif