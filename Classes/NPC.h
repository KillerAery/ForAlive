#pragma once
#ifndef _NPC_H_
#define _NPC_H_

#include "Biology.h"


class NPC :public Biology {
public:
	//≥ı ºªØ
	NPC();
	virtual bool init(ValueMap& obj_valuemap);
	static NPC* create(ValueMap& obj_valuemap);
};


#endif // !_NPC_H_
