#pragma once
#ifndef Perceptionable_h__
#define Perceptionable_h__

#include "cocos2d.h"
#include "Relation.h"

using cocos2d::Node;

class Biology;
class Container;
class Drop;

//感知物体
class Perceptionable : public Node{
public:
	CREATE_FUNC(Perceptionable);
	virtual Biology* getNearest(Attitude attitude) { return nullptr; }
	virtual Biology* getPlayer() { return nullptr; }
	virtual Container* getNearestContainer() { return nullptr; }
	virtual Biology* getNearestBiology() { return nullptr; }
	virtual Drop* getNearestDrop() { return nullptr; }
	virtual bool ifHaveBiologyTarget() { return false; }
	virtual bool ifHaveDropTarget() { return false; }
};

#endif // Perceptionable_h__