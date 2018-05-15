#include "AI_BaseNode.h"

namespace {
	bool default_condition(NPC* master) { return true; }
}

AI_BaseNode::AI_BaseNode():m_condition(default_condition){}