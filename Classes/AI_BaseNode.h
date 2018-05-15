#ifndef AI_BaseNode_h__
#define AI_BaseNode_h__

#include "cocos2d.h"
#include "NPC.h"

using cocos2d::Node;

using Condition = std::function<bool(NPC* npc)>;

//»ù´¡½Úµã
class AI_BaseNode : public Node {
	CC_SYNTHESIZE(Condition, m_condition, Condition);
public:
	AI_BaseNode();
	virtual void run(NPC* master) = 0;
	virtual bool init()override { if (!Node::init())return false; Node::onEnter(); Node::onEnterTransitionDidFinish(); return true; }
};


#endif // AI_BaseNode_h__
