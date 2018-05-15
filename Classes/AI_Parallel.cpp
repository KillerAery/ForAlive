#include "AI_Parallel.h"

AI_Parallel::AI_Parallel(){}

void AI_Parallel::run(NPC* npc) {
	for (auto node : getChildren()) {
		auto AInode = static_cast<AI_BaseNode*>(node);
		if (AInode->getCondition()(npc))
		AInode->run(npc);
	}
}