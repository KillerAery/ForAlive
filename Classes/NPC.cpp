#pragma once
#include "NPC.h"

NPC::NPC(){}

bool NPC::init(ValueMap& valuemap){
	if (!Biology::init(valuemap))return false;

	return true;
}

NPC* NPC::create(ValueMap& valuemap) {
	valuemap.insert(ValueMap::value_type("entitytpye", Value(int(EntityTpye::biology))));
	auto npc = new (std::nothrow)NPC();
	if (npc&&npc->init(valuemap)) { npc->autorelease(); }
	else { CC_SAFE_DELETE(npc); }
	return npc;
}



