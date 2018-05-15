#ifndef TriggerManager_h__
#define TriggerManager_h__


#include "cocos2d.h"
#include "Singleton.h"

using TriggerMap = std::multimap<int,int>;

enum class BiologyTpye;

//触发器管理  目前仅对任务触发负责
class TriggerManager : public cocos2d::Ref, public Singleton<TriggerManager>{
	CC_SYNTHESIZE_PASS_BY_REF(TriggerMap,m_killTriggers,KillTriggers);
	CC_SYNTHESIZE_PASS_BY_REF(TriggerMap,m_getTriggers, GetTriggers);
	CC_SYNTHESIZE_PASS_BY_REF(TriggerMap,m_talkTriggers,TalkTriggers);
public:
	bool init();
	void registerKillTrigger(BiologyTpye requireTpye,int MissionID);//注册击杀触发
	void registerGetTrigger(int requireID,int MissionID);//注册物品获取触发
	void registerTalkTrigger(int requireID,int MissionID);//注册说话触发

	void unregisterKillTrigger(BiologyTpye requireTpye, int MissionID);//注销击杀触发
	void unregisterGetTrigger(int requireID, int MissionID);//注销物品获取触发
	void unregisterTalkTrigger(int requireID, int MissionID);//注销说话触发

	void checkKillTrigger(BiologyTpye tpye);//检测击杀触发
	void checkGetTrigger(int id,int num);//检测物品获取触发
	void checkTalkTrigger(int id);//检测说话触发
};

#endif // TriggerManager_h__