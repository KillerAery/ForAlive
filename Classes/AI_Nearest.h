#ifndef AI_Nearest_h__
#define AI_Nearest_h__

#include "AI_Target.h"

class AI_Nearest: public AI_Target{
	CC_SYNTHESIZE(Attitude, m_targetAttitude, Attitude);
public:
	AI_Nearest(Attitude attitude = Attitude::neutral) :m_targetAttitude(attitude) {}

	static Target create(Attitude attitude) { return Target(new AI_Nearest(attitude)); }
	static Target create(int attitude) { return Target(new AI_Nearest(Attitude(attitude))); }
	static Target create(){ return Target(new AI_Nearest()); }

	void setTargetAttitude(Attitude attitude) { m_targetAttitude = attitude; }

	virtual Biology* getBiologyTarget(NPC* master)override {
		Biology* enemy = master->getPerception()->getNearest(m_targetAttitude);
		return enemy;
	}
};

#endif // AI_Nearest_h__
