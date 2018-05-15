#include "AI_Seletor.h"

AI_Seletor::AI_Seletor(){}

void AI_Seletor::run(NPC* npc) {
	for (auto node : getChildren()) {
		auto AInode = static_cast<AI_BaseNode*>(node);
		if (AInode->getCondition()(npc))
		{AInode->run(npc); return;}
	}
}